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

// Qt includes
#include <QAction>
#include <QTranslator>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
Application::Application(int& argc, char** argv) : QApplication(argc, argv) {
    mCurrentTranslator	= 0x0;
    mMainWindow			= 0x0;
    mPath.mLanguage		= "./languages";
	mPath.mPlugin		= "./plugins";
}


Application::~Application() {
    // Clean all translators objects.
	for(auto& itr : mTranslators) {
		delete itr;
	}
    mTranslators.clear();
}


void Application::close() {
    QApplication::quit();
}


void Application::loadTranslations(const QString& str) {
    loadTranslations(QDir(str));
}


void Application::loadTranslations(const QDir& dir) {
    // <language>_<country>
    // Get language files.
    QFileInfoList entries = dir.entryInfoList(QStringList() << "*_*.qm", QDir::Files | QDir::Readable, QDir::Name);

    // Create a translator for each language.
    for(int i = 0; i < entries.size(); i++) {
        QFileInfo file = entries.at(i);

        QTranslator* translator = new QTranslator(instance());
        if(translator->load(file.absoluteFilePath())) {
            mTranslators.insert(file.baseName(), translator);
        } else {
            delete translator;
        }
    }
}


void Application::setLanguage(QAction* action) {
    QTranslator* translator = mTranslators.value(action->data().toString(), 0x0);
    if(translator) {
        if(mCurrentTranslator) {
			removeTranslator(mCurrentTranslator);
		}

        mCurrentTranslator = translator;
        installTranslator(mCurrentTranslator);
    }
}


bool Application::setupConnections() {
    // Connect change language signal.
	//connect(mMainWindow, &MainWindow::signalToLanguageChanged, this, &Application::setLanguage);

    // Connect the close event.
    //connect(mMainWindow, SIGNAL(signClose()), this, SLOT(close()));
    return true;
}


bool Application::setupFinalSteps() {
    if(!mMainWindow->setup(mTranslators.keys(), mPath.mPlugin)) {
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
        mMainWindow = 0x0;
    }
}


bool Application::startUp() {
    // Load language files from the directory.
    loadTranslations(mPath.mLanguage);

    if(!setupGuis())		{ return false; }
    if(!setupConnections()) { return false; }
    if(!setupFinalSteps())	{ return false; }
        
    return true;
}


} // End namespace ndx
