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


#ifndef _Application_h_
#define _Application_h_


// ndxLib includes
#include <ndxLogManager.h>

// STL includes
#include <memory>

// Qt includes
#include <QApplication>


namespace ndx {


// ************************************************************
// Class Forward Declarations
// ************************************************************
class MainWindow;


/**
 * Main Qt application.
 */
class Application : public QApplication {
    Q_OBJECT

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
  * @param argc Number of arguments.
  * @param argv List of arguments.
     */
    Application(int& argc, char** argv);


    /**
     * Default destructor.
     */
    ~Application();


    /**
     * Shutdown the application.
     */
    void shutDown();


    /**
     * Start up the application.
     * @return True on success.
     */
    bool startUp();




public slots:
    /**
     * Close the application.
     */
    void close();




protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Setup connections.
     * @return True on success.
     */
    bool setupConnections();


    /**
     * Setup final step.
     * @param True on success.
     */
    bool setupFinalSteps();


    /**
     * Setup GUI.
     * @param True on success.
     */
    bool setupGuis();


    /**
     * The logging manager.
     */
    std::shared_ptr<LogManager> mLogManager;


    /**
     * The main window.
     */
    MainWindow* mMainWindow;


};  // End class Application


}  // End namespace ndx


#endif  // _Application_h_
