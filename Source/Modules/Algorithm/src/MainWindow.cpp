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
#include "MainWindow.h"
#include "PluginManager.h"
#include "MetaData.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    initValues();
    initPointers();
    setupObjects();
    setupConnections();
    setupDefaultSettings();
}


MainWindow::~MainWindow() {
	if(mPluginManager) {
		delete mPluginManager;
	}
}


//void MainWindow::changeEvent(QEvent* evt) {
//    // Retranslated if necessary.
//    if(evt->type() == QEvent::LanguageChange) {
//        retranslate();
//    }
//
//    QMainWindow::changeEvent(evt);
//}


void MainWindow::changeLanguage(QAction* language) {
    emit signalToLanguageChanged(language);
}


//void MainWindow::closeEvent(QCloseEvent* evt) {
//    // Close the window.
//    QMainWindow::closeEvent(evt);
//        
//    // Tells other that this window will be closed.
//}



void MainWindow::initPointers() {
    mLanguages		= 0x0;
	mPluginManager	= 0x0;
}


void MainWindow::initValues() { 
}


void MainWindow::retranslate() {
    // Retranslated UI.
    retranslateUi(this);
}


bool MainWindow::setup(const QStringList& aLangs, const QString& pDir) {
    //setupLanguages(aLangs, "no_NO");
	mPluginManager->scan(pDir);
    return true;
}


bool MainWindow::setupConnections() {
    // ************************************************************
    // MainWindow
    // ************************************************************
    // Change language.
    //connect(mLanguages, &QActionGroup::triggered, this, &MainWindow::changeLanguage);

    // Exit MainWindow.
    connect(mActionExit, &QAction::triggered, this, &MainWindow::close);

    // Load sample.
    connect(mSampleButtonLoad, SIGNAL(clicked()), this, SLOT(loadPlugin()));

    // Load sample by click on the list.
    connect(mSampleList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(loadPlugin(QListWidgetItem*)));

    // Unload sample.
    connect(mSampleButtonUnload, &QPushButton::clicked, this, &MainWindow::unloadPlugin);

    // Populate samples.
    connect(mPluginManager, &PluginManager::signalToPopulatePlugin, this, &MainWindow::populatePlugin);

    // Sort sample list.
    connect(mPluginManager, &PluginManager::signalToSort, this, &MainWindow::sortSampleList);

    // Remove plug-in from the list.
    connect(mPluginManager, &PluginManager::signalToRemovePlugin, this, &MainWindow::removePlugin);

    // Connect between dock widget.
    connect(mSampleDock, &QDockWidget::visibilityChanged, mActionShowSampleList, &QAction::setChecked);
    connect(mActionShowSampleList, &QAction::triggered, mSampleDock, &QDockWidget::setVisible);

    return true;
}


bool MainWindow::setupDefaultSettings() {        
    // Disable language menu by default, due there are no loaded language at the beginning.
    //mMenuLanguage->setEnabled(false);

    toggleLoadAndUnloadButtons(true);
    return true;
}


//bool MainWindow::setupLanguages(const QStringList& list, const QString& dLang) {
//    QAction* defaultLanguage = 0x0;
//    QAction* englishLanguage = 0x0;
//
//    // Fill in available languages.
//    for(int i = 0; i < list.size(); i++) {
//        QString current = list.at(i);
//        QLocale locale(current);
//        QString language	= QLocale::languageToString(locale.language());
//        QString country		= QLocale::countryToString(locale.country());
//        QString name		= language + " ( " + country + " )";
//
//        QAction* action = mMenuLanguage->addAction(name);
//        action->setData(current);
//        action->setCheckable(true);
//
//        mLanguages->addAction(action);
//
//        if(current == dLang) {
//            action->trigger();
//            defaultLanguage = action;
//        }
//        else if(language == "English") {
//            englishLanguage = action;
//        }
//    }
//
//    // If not find the desired language, when use English as default,
//    // otherwise use the first one.
//    if(list.size() > 0) {
//        if(!defaultLanguage) {
//            if(englishLanguage) {
//                englishLanguage->trigger();
//            } else {
//                mLanguages->actions().first()->trigger();
//            }
//        }
//        mMenuLanguage->setEnabled(true);
//    }
//
//    return true;
//}


bool MainWindow::setupObjects() {
    // Setup objects from the UI form.
    setupUi(this);

    mLanguages		= new QActionGroup(this);
	mPluginManager	= new PluginManager();
    return true;
}


QString MainWindow::translate(const QString& str) {
    return QApplication::translate("MainWindow", str.toStdString().c_str());
}


} // End namespace ndx
