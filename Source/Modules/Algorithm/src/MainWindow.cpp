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
#include "ndxMacros.h"


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
	SAFE_CLEAN_POINTER(mPluginManager);
}


void MainWindow::initPointers() {
	mPluginManager	= nullptr;
}


void MainWindow::initValues() { 
}


bool MainWindow::setup(const QString& pDir) {
	mPluginManager->scan(pDir);
    return true;
}


bool MainWindow::setupConnections() {
    // ----------------------------------------
    // MainWindow
    // ----------------------------------------
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
    toggleLoadAndUnloadButtons(true);
    return true;
}


bool MainWindow::setupObjects() {
    // Setup objects from the UI form.
    setupUi(this);

	mPluginManager	= new PluginManager();
    return true;
}


} // End namespace ndx

