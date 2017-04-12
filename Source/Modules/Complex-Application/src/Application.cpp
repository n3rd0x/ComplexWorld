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


// Local includes
#include "Application.h"
#include "MainWindow.h"
#include "ndxLogManager.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
Application::Application(int& argc, char** argv) : QApplication(argc, argv) {
    QDir dir(QDir::current());
    if(!dir.exists("Logs")) {
        dir.mkdir("Logs");
    }

    mMainWindow = nullptr;

    // Setup logger system.
    mLogManager = std::make_shared<LogManager>(true);
    mLogManager->createLogger("", "Logs/ModuleAlgorithm.log", true, Poco::Message::PRIO_TRACE);
}


Application::~Application() {
    mLogManager.reset();
}


void Application::close() {
    QApplication::quit();
}


bool Application::setupConnections() {
    return true;
}


bool Application::setupFinalSteps() {
    if(!mMainWindow->setup("./Plugins")) {
        return false;
    }
    mMainWindow->show();

    return true;
}


bool Application::setupGuis() {
    mMainWindow = new MainWindow();
    return true;
}


void Application::shutDown() {
    if(mMainWindow) {
        delete mMainWindow;
        mMainWindow = nullptr;
    }
}


bool Application::startUp() {
    if(!setupGuis()) {
        return false;
    }
    if(!setupConnections()) {
        return false;
    }
    if(!setupFinalSteps()) {
        return false;
    }

    return true;
}


}  // End namespace ndx
