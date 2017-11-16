/**
 * \file BaseGraphModel.hpp
 * \author Malte Langosz
 * \brief 
 */

#ifndef BASE_GRAPH_MODEL_H
#define BASE_GRAPH_MODEL_H

#include <graph_analysis/BaseGraph.hpp>
#include <system_modelling/graph_basics/Base.hpp>
#include <bagel_gui/ModelInterface.hpp>
#include <vector>
#include <string>
#include <configmaps/ConfigData.h>
//#include <graph_analysis/gui/GraphAnalysisGui.hpp>

namespace gui_task_model {

  class BaseGraphModel : public bagel_gui::ModelInterface {
  public:
    BaseGraphModel(bagel_gui::OsgBG *bagelGui);
    BaseGraphModel(const BaseGraphModel *other);
    ~BaseGraphModel();

    virtual ModelInterface* clone() = 0;

    virtual bool addNode(unsigned long nodeId, configmaps::ConfigMap *node) = 0;
    virtual bool addEdge(unsigned long egdeId, configmaps::ConfigMap *edge) = 0;
    virtual bool addNode(unsigned long nodeId, const configmaps::ConfigMap &node) = 0;
    virtual bool addEdge(unsigned long egdeId, const configmaps::ConfigMap &edge) = 0;
    virtual bool updateNode(unsigned long nodeId, configmaps::ConfigMap node);
    virtual bool updateEdge(unsigned long egdeId,
                            configmaps::ConfigMap edge) {return true;}
    virtual bool removeNode(unsigned long nodeId);
    virtual bool removeEdge(unsigned long edgeId);
    std::map<unsigned long, std::vector<std::string> > getCompatiblePorts(unsigned long nodeId, std::string outPortName) {return std::map<unsigned long, std::vector<std::string> >();}
    virtual bool loadSubgraphInfo(const std::string &filename,
                                  const std::string &absPath) {return false;}
    virtual bool handlePortCompatibility() {return false;}
    const std::map<std::string, osg_graph_viz::NodeInfo>& getNodeInfoMap();
    virtual bool groupNodes(unsigned long groupNodeId, unsigned long nodeId) {
      return false;
    }
    virtual void displayWidget( QWidget *pParent );

  protected:
    //graph_analysis::gui::GraphAnalysisGui* mpGraphAnalysisGui;

    graph_analysis::BaseGraph::Ptr mpGraph;
    std::map<std::string, osg_graph_viz::NodeInfo> infoMap;
    std::map<unsigned long, std::string> nodeMap;
    std::string confDir, addName;
    bool ignoreNotify;
    bool handleProps;
    graph_analysis::Vertex::Ptr addNode(unsigned long id,
                                        const std::string &type);
    bool loadProperties(configmaps::ConfigMap *map_,
                        system_modelling::graph_basics::Base::Ptr v);
    bool updateProperties(configmaps::ConfigItem &map,
                          system_modelling::graph_basics::Base::Ptr v);
  };
} // end of namespace gui_task_model

#endif // BASE_GRAPH_MODEL_H
