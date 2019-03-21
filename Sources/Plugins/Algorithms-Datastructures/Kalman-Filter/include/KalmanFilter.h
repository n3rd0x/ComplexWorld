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


#ifndef _KalmanFilter_h_
#define _KalmanFilter_h_


// Local includes
#include "Plugin.h"
#include <ui_KalmanFilter.h>

// ndxLibrary includes
#include <ndxPrerequisites.h>

// STL includes
#include <string>


namespace ndx {


/**
 * Kalman filter sample.
 */
class KalmanFilter : public Plugin, public Ui::KalmanFilter {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ndx.Algorithms.KalmanFilter" FILE "KalmanFilter.json")
    Q_INTERFACES(ndx::Plugin);

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    KalmanFilter();


    /**
     * Default destructor.
     */
    ~KalmanFilter();


    /**
     * Shutdown the plug-in.
     */
    void shutDown();


    /**
     * Start up the plug-in.
     * @return True on success.
     */
    bool startUp(QWidget* parent);


protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * @brief Logging tag.
     */
    static const std::string TAG;


protected slots:
    /**
     * Widget changed in the tab.
     */
    void tabChanged(int idx);


};  // End class KalmanFilter


}  // End namespace ndx


#endif  // _KalmanFilter_h_
