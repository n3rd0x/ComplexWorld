/**
 * Complex World - Research & Educational Project
 * Copyright (C) T.Sang Tran aka "n3rd0x" <nerdox.tranit@gmail.com>
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
#include "PluginMetaData.h"

// Qt includes
#include <QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
void MainWindow::checkPlugin(QListWidgetItem* item) {
    mStatusBar->showMessage(item->toolTip(), 2000);
}


void MainWindow::loadPlugin() {
    // Retrieve selected item.
    QListWidgetItem* item = mSampleList->currentItem();
    if(item) {
        loadPlugin(item);
    }
}


void MainWindow::loadPlugin(QListWidgetItem* item) {
    // Skip if we have already load the plug-in.
    if(mCurrentPlugin == item->text()) {
        return;
    }

    // Set color to blue if succeeded to load the plug-in.
    if(item) {
        // Find current loaded plug-in.
        auto curPlugin = mPluginManager->getCurrentLoaded();
        if(mPluginManager->load(mCentralWidget, item->text())) {
            // Set default color of the previous plug-in.
            auto items = mSampleList->findItems(curPlugin, Qt::MatchExactly);
            for(auto itr : items) {
                setFont(itr, false);
            }

            setFont(item, true);
            mCurrentPlugin = item->text();

            toggleLoadAndUnloadButtons(false);
            mStatusBar->showMessage(item->text() + " - " + item->toolTip(), 2000);
        }
    }
}


void MainWindow::populatePlugin(const PluginMetaData& meta) {
    QListWidgetItem* item = new QListWidgetItem(mSampleList);
    item->setText(meta.mName);
    item->setToolTip(meta.mDescription);
    item->setStatusTip(meta.mDescription);
    setFont(item, false);
}


void MainWindow::removePlugin(const QString& name) {
    auto items = mSampleList->findItems(name, Qt::MatchExactly);
    if(items.size() > 0) {
        mSampleList->removeItemWidget(items[0]);
    }
}


void MainWindow::sortSampleList(const bool state) {
    mSampleList->setSortingEnabled(state);
}


void MainWindow::toggleLoadAndUnloadButtons(const bool state) {
    if(mSampleList->count() > 0) {
        mSampleButtonLoad->setEnabled(state);
        mSampleButtonUnload->setEnabled(!state);
    }
    else {
        mSampleButtonLoad->setEnabled(false);
        mSampleButtonUnload->setEnabled(false);
    }
}


void MainWindow::unloadPlugin() {
    auto curPlugin = mPluginManager->getCurrentLoaded();
    auto items     = mSampleList->findItems(curPlugin, Qt::MatchExactly);
    for(auto itr : items) {
        setFont(itr, false);
    }

    mPluginManager->unload();
    toggleLoadAndUnloadButtons(true);

    mCurrentPlugin = "";
    mStatusBar->clearMessage();
}


}  // End namespace ndx
