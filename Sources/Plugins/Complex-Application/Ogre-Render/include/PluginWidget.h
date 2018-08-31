/**
 * Complex World - Research & Educational Project
 * Copyright (C) T.Sang Tran aka "Nerdox" <t.sang.tran@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _PluginWidget_h_
#define _PluginWidget_h_


// Local includes
#include "Plugin.h"
#include <ui_PluginWidget.h>


namespace ndx {


/**
 * Echo form sample.
 */
class PluginWidget : public Plugin, public Ui::PluginWidget {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ndx.ComplexWorld.OgreRender" FILE "PluginWidget.json")
    Q_INTERFACES(ndx::Plugin);

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    PluginWidget();


    /**
     * Default destructor.
     */
    ~PluginWidget();


    /**
     * Shutdown the plug-in.
     */
    void shutDown();


    /**
     * Start up the plug-in.
     * @return True on success.
     */
    bool startUp(QWidget* parent);



protected slots:



private:
    /**
     * Prefix logging tag.
     */
    static const std::string TAG;


};  // End class PluginWidget


}  // End namespace ndx


#endif  // _PluginWidget_h_
