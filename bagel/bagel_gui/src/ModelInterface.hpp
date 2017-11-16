/*
 *  Copyright 2016, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \file ModelInterface.h
 * \author Malte (malte.langosz@dfki.de)
 * \brief 
 *
 * Version 0.1
 */

#ifndef BAGEL_GUI_MODEL_INTERFACE_H
#define BAGEL_GUI_MODEL_INTERFACE_H

class QWidget;

namespace configmaps {
  class ConfigMap;
}

namespace osg_graph_viz {
  struct NodeInfo;
}

namespace bagel_gui {

  class OsgBG;

  class ModelInterface {
  public:
    ModelInterface(OsgBG *bagelGui) : bagelGui(bagelGui) {}
    virtual ~ModelInterface() {}

    virtual ModelInterface* clone() = 0;
    // load file or directory
    virtual bool addNode(unsigned long nodeId, configmaps::ConfigMap *node) = 0;
    virtual bool addEdge(unsigned long egdeId, configmaps::ConfigMap *edge) = 0;
    virtual bool addNode(unsigned long nodeId,
                         const configmaps::ConfigMap &node) = 0;
    virtual bool addEdge(unsigned long egdeId,
                         const configmaps::ConfigMap &edge) = 0;
    virtual bool updateNode(unsigned long nodeId,
                            configmaps::ConfigMap node) = 0;
    virtual bool updateEdge(unsigned long egdeId,
                            configmaps::ConfigMap edge) = 0;
    virtual void preAddNode(unsigned long nodeId) = 0;
    virtual bool removeNode(unsigned long nodeId) = 0;
    virtual bool removeEdge(unsigned long edgeId) = 0;
    virtual bool loadSubgraphInfo(const std::string &filename,
                                  const std::string &absPath) = 0;
    virtual std::map<unsigned long, std::vector<std::string> > getCompatiblePorts(unsigned long nodeId, std::string outPortName) = 0;
    virtual bool handlePortCompatibility() = 0;
    virtual const std::map<std::string, osg_graph_viz::NodeInfo>& getNodeInfoMap() = 0;
    virtual bool groupNodes(unsigned long groupNodeId, unsigned long nodeId) = 0;

    virtual void displayWidget( QWidget *pParent ) {};
  protected:
    OsgBG *bagelGui;
  };
} // end of namespace bagel_bui

#endif // BAGEL_GUI_MODEL_INTERFACE_H
