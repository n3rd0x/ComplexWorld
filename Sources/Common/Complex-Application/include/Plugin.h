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


#ifndef _Plugin_h_
#define _Plugin_h_


// Local includes
#include "PluginMetaData.h"

// Qt includes
#include <QtCore>
#include <QtPlugin>
#include <QtWidgets>


namespace ndx {


/**
 * Generic plug-in.
 */
class Plugin : public QWidget {
    Q_OBJECT

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    Plugin();


    /**
     * Default destructor.
     */
    virtual ~Plugin();


    /**
     * @return Meta data.
     */
    const PluginMetaData& getMetaData() const;


    /**
     * Set meta data.
     * @param meta Meta data to set.
     */
    void setMetaData(const PluginMetaData& meta);


    /**
     * Shutdown the plug-in.
     */
    virtual void shutDown();


    /**
     * Start up the plug-in.
     * @param parent Widget to display into.
     * @return True on success.
     */
    virtual bool startUp(QWidget* parent);




protected:
    /**
     * Meta data.
     */
    PluginMetaData mMetaData;


};  // End class Plugin


}  // End namespace ndx


// ************************************************************
// Plug-in Declarations
// ************************************************************
Q_DECLARE_INTERFACE(ndx::Plugin, "ndx.Algorithms.Plugin")


#endif  // _Plugin_h_
