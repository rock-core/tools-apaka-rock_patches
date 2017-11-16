/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/Time.hpp>
#include "Debug.h"
#include <base/samples/Joints.hpp>
#include <stdlib.h>

using namespace head_demo_control;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;
    timeout = _timeout.get();
    homePos[0] = _home_pos_x.get();
    homePos[1] = _home_pos_y.get();
    openingAngle[0] = _opening_angle_x.get();
    openingAngle[1] = _opening_angle_y.get();
    imgDims[0] = _img_dim_x.get();
    imgDims[1] = _img_dim_y.get();
    servoing = _servoing.get();

    imgCenter[0] = imgDims[0] / 2;
    imgCenter[1] = imgDims[1] / 2;

    invertX = _invert_x.get();
    invertY = _invert_y.get();
    stopWorking = false;
    manipulationState = false;
    axisNames[0] = _name_X_axis.get();
    axisNames[1] = _name_Y_axis.get();
    targetDiff[0] = 0;
    targetDiff[1] = 0;
    smoothStep = 0;

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
    static int timeoutCounter = timeout;
    static int doNothing = 0;

    static const int NOTHING_DELAY = 6;

    if(manipulationState)
    {
      lookInteresting();
      return;
    }

    updateBody();

    if(!stopWorking)
    {
    

    base::Vector2d imCoord;

    if(doNothing != 0)
    {
      if(doNothing == 1)
      {
        _output_adios.write(false);
        _output_manipulation.write(false);
	_marker_information.clear();
      }
      --doNothing;
      return;
    }

    std::vector<aruco::DetectedMarker> vsmi;
    if(_marker_information.read(vsmi) == RTT::NewData)
    {
      // filter out the largest marker with one of the relevant ids
      aruco::DetectedMarker smi;
      for( size_t i=0; i<vsmi.size(); ++i )
      {
        if( vsmi[i].id == 236 || vsmi[i].id == 939 || vsmi[i].id == 666 )
        {
          if( vsmi[i].getBoundingRectArea() > smi.getBoundingRectArea() || !smi.isValid())
            smi = vsmi[i];
        }
      }

      if( smi.isValid() )
      {
      base::Vector2d center = smi.getCenter();

      timeoutCounter = timeout;
      SHOW_INT(smi.id, DEBUG_INFO);
      SHOW_INT((int)center.x(), DEBUG_TRACE);
      SHOW_INT((int)center.y(), DEBUG_TRACE);
      if(smi.id == 236)  // tracking marker
      {
        moveTo(center.x(), center.y());
      }
      else
        if(smi.id == 939) // adios marker
        {
          moveTo(center.x(), center.y(), false);
          doNothing = NOTHING_DELAY;
          stopWorking = true;
          DEBUG_MSG("Winken!", DEBUG_INFO);
          _output_adios.write(true);
        }
        else
          if(smi.id == 666) // manipulation marker
          {
            moveToManipulationPose();
            doNothing = NOTHING_DELAY;
            stopWorking  = true;
            manipulationState = true;
            DEBUG_MSG("Manipulation!", DEBUG_INFO);
            _output_manipulation.write(true);
          }
      }
    }
    else
    if(_image_coordinates.read(imCoord) == RTT::NewData)
    {
      timeoutCounter = timeout;
      
      SHOW_FLOAT(imCoord[0], DEBUG_TRACE);
      SHOW_FLOAT(imCoord[1], DEBUG_TRACE);

      moveTo(imCoord[0], imCoord[1]);
    }
    else
    {
      if(timeoutCounter != 0)
      {
        --timeoutCounter;
      }
      else
      {
        idleBehaviour();
      }
    }
    }
    doSmoothMoves();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}

void Task::idleBehaviour()
{
  DEBUG_MSG("Idle...", DEBUG_TRACE)
  calcSmoothMoves(homePos[0], homePos[1], false);
}

void Task::moveTo(const int x, const int y, bool const noSmooth)
{
      // convert to {-1 .. +1}
      double xAngle = (x - imgCenter[0]) / (double)imgCenter[0];
      double yAngle = (y - imgCenter[1]) / (double)imgCenter[1];
      xAngle *= openingAngle[0] / 2;
      yAngle *= openingAngle[1] / 2;

      if(invertX)
      {
        xAngle *= -1;
      }
      if(invertY)
      {
        yAngle *= -1;
      }

      SHOW_FLOAT(xAngle, DEBUG_TRACE);
      SHOW_FLOAT(yAngle, DEBUG_TRACE);

      if(servoing)
      {
        double headX, headY;
        base::samples::Joints joints;
        _joint_samples.read(joints);
        headX = joints.getElementByName(axisNames[0]).position;
        headY = joints.getElementByName(axisNames[1]).position;
        calcSmoothMoves(headX + xAngle, headY + yAngle, noSmooth);

      } // servoing
      else
      { // not servoing
        calcSmoothMoves(xAngle, yAngle, noSmooth);
      } // not servoing

}

void Task::continue_work()
{
  stopWorking = false;
  manipulationState = false;
  DEBUG_MSG("continue_work()", DEBUG_TRACE);
}

void Task::sendPositions(const double x, const double y)
{
  std::vector<double> positions;
  positions.push_back(x);
  positions.push_back(y);

  std::vector<std::string> names;
  names.push_back(axisNames[0]);
  names.push_back(axisNames[1]);

  base::samples::Joints joints = base::samples::Joints::Positions(positions, names);
  _joint_commands.write(joints);
}

void Task::calcSmoothMoves(const double targetX, const double targetY, const bool noSmooth)
{
  if( !_enable_smooth_moves.get())
  {
    sendPositions(targetX, targetY);
    return;
  }
  base::samples::Joints joints;
  _joint_samples.read(joints);
  double headX;
  double headY;
  try{
    headX = joints.getElementByName(axisNames[0]).position;
    headY = joints.getElementByName(axisNames[1]).position;
  }
  catch(base::NamedVector<base::JointState>::InvalidName in){
    DEBUG_MSG("Axis names not found in input data!", DEBUG_WARNING);
  }
  double diffX, diffY;

  int steps = _smooth_moves.get();

  diffX = targetX - headX;
  diffY = targetY - headY;

  if(noSmooth)
  {
    targetDiff[0] = 0;
    targetDiff[1] = 0;
  }
  else
  {
    targetDiff[0] = diffX / steps;
    targetDiff[1] = diffY / steps;
  }
  
  targets[0] = targetX;
  targets[1] = targetY;

  smoothStep = steps;
}

void Task::doSmoothMoves()
{
  if(!_enable_smooth_moves.get())
  {
    return;
  }
  if(smoothStep !=0 )
  {
    --smoothStep;
  }

  double x = targets[0] - (targetDiff[0] * smoothStep);
  double y = targets[1] - (targetDiff[1] * smoothStep);

  sendPositions(x,y);
}

void Task::updateBody()
{
  double headX, headY;
  base::samples::Joints joints;
  _joint_samples.read(joints);
  try{
  headX = joints.getElementByName(axisNames[0]).position;
  headY = joints.getElementByName(axisNames[1]).position;
  }
  catch(base::NamedVector<base::JointState>::InvalidName in){
    DEBUG_MSG("Axis names not found in input data!", DEBUG_WARNING);
  }
  double scale = _output_scale.get();
  double bodyX = headX * scale;
  double bodyY = headY * scale;
  double maxBody = 10 * M_PI / 180;
  if(bodyX > maxBody)
  {
    bodyX = maxBody;
  }
  else
  {
    if(bodyX < -maxBody)
    {
      bodyX = -maxBody;
    }
  }
  if(bodyY > maxBody)
  {
    bodyY = maxBody;
  }
  else
  {
    if(bodyY < -maxBody)
    {
      bodyY = - maxBody;
    }
  }
  _output_x.write(bodyX);
  _output_y.write(bodyY);
}

void Task::moveHomeFast()
{
  calcSmoothMoves(homePos[0], homePos[1], true);
  _output_x.write(homePos[0]);
  _output_y.write(homePos[1]);
  sendPositions(homePos[0], homePos[1]);
}

void Task::moveToManipulationPose()
{
  const double angle = 45 * M_PI / 180.0;
  calcSmoothMoves(0, angle, true);
  _output_x.write(0);
  _output_y.write(0);
  sendPositions(0, angle);
}

void Task::lookInteresting()
{
// zufaelliger x, regelmaessiger y
  double xl, xh, yl, yh;
  xl = _man_area_x_low.get();
  xh = _man_area_x_high.get();
  yl = _man_area_y_low.get();
  yh = _man_area_y_high.get();

  static int counter = 0;
  const static int delay = 90;

  base::samples::Joints joints;
  _joint_samples.read(joints);
  double headX;
  double headY;
  try{
    headX = joints.getElementByName(axisNames[0]).position;
    headY = joints.getElementByName(axisNames[1]).position;
  }
  catch(base::NamedVector<base::JointState>::InvalidName in){
    DEBUG_MSG("Axis names not found in input data!", DEBUG_WARNING);
  }
  static double targetY = yh;
  static double targetX = homePos[0];

  switch(counter){
  case 0:
  {
    counter = delay;
    calcSmoothMoves(targetX, yh);
    targetY = yh;

    break;
  }
  case delay / 2:
  {
    calcSmoothMoves(targetX, yl);
    targetY = yl;
    break;
  }
  case delay / 3:
  case (delay / 3) * 2:
  {
    if(random() > (RAND_MAX / 2))
    {
      targetX = headX + (xh - xl) / 3;
      if(targetX > xh)
      {
        targetX = xl;
      }
    }else{
      targetX = headX - (xh - xl) / 3;
      if(targetX < xl)
      {
        targetX = xh;
      }
    }
    calcSmoothMoves(targetX, targetY);
    break;
  }
  default:
    break;
  };
  --counter;
  doSmoothMoves();

  
}

