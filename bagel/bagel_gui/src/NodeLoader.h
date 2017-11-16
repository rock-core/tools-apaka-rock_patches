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
 * \file NodeLoader.h
 * \author Malte (malte.langosz@dfki.de)
 * \brief Base class for node loader
 *
 * Version 0.1
 */

#ifndef BAGEL_GUI_NODE_LOADER_H
#define BAGEL_GUI_NODE_LOADER_H

namespace configmaps {
  class ConfigMap;
}

namespace bagel_gui {

  class OsgBG;
  
  class NodeLoader {
  public:
    NodeLoader(OsgBG *bagelGui) : bagelGui(bagelGui) {}
    virtual ~NodeLoader() {}

    // load file or directory
    virtual void loadNodeInfo(const std::string &filename) = 0;
    virtual void load(const std::string &filename) = 0;
    virtual void load(configmaps::ConfigMap &map, std::string loadPath,
                      bool reload = false) = 0;
    virtual void save(const configmaps::ConfigMap &map,
                      const std::string &filename) = 0;
    virtual void exportCnd(const configmaps::ConfigMap &map,
			   const std::string &filename) = 0;
  protected:
    OsgBG *bagelGui;
  };
} // end of namespace bagel_bui

#endif // BAGEL_GUI_NODE_LOADER_H
