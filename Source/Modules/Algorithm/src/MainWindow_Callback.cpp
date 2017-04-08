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
#include "MetaData.h"
#include "PluginManager.h"

// Qt includes
#include <QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
void MainWindow::loadPlugin() {
    // Retrieve selected item.
    QListWidgetItem* item = mSampleList->currentItem();
    loadPlugin(item);
}


void MainWindow::loadPlugin(QListWidgetItem* item) {
    // Skip if we have already load the plug-in.
    if(mCurrentPlugin == item->text()) {
        return;
    }

    // Set color to blue if succeeded to load the plug-in.
    if(item) {
        QBrush sBrush(QColor(0, 0, 255, 255));
        sBrush.setStyle(Qt::SolidPattern);
        if(mPluginManager->load(mCentralWidget, item->text())) {
            // Set default color of the previous plug-in.
            QList<QListWidgetItem*> items = mSampleList->findItems(mCurrentPlugin, Qt::MatchExactly);
            QBrush dBrush(QColor(0, 0, 0, 255));
            dBrush.setStyle(Qt::SolidPattern);
            item->setForeground(dBrush);
            for(auto itr : items) {
                itr->setForeground(dBrush);
            }

            item->setForeground(sBrush);
            mCurrentPlugin = item->text();

            toggleLoadAndUnloadButtons(false);
            mStatusBar->showMessage(item->text() + " - " + item->toolTip());
        }
    }
}

	
void MainWindow::populatePlugin(const MetaData& meta) {
    QListWidgetItem* item = new QListWidgetItem(mSampleList);
    item->setText(meta.mName);
    item->setToolTip(meta.mDescription);
    item->setStatusTip(meta.mDescription);
}


void MainWindow::removePlugin(const QString& name) {
    QList<QListWidgetItem*> items = mSampleList->findItems(name, Qt::MatchExactly);
    if(items.size() > 0) {
        mSampleList->removeItemWidget(items[0]);
    }
}


void MainWindow::sortSampleList(const bool state) {
    mSampleList->setSortingEnabled(state);
}


void MainWindow::toggleLoadAndUnloadButtons(const bool state) {
    mSampleButtonLoad->setEnabled(state);
    mSampleButtonUnload->setEnabled(!state);
}


void MainWindow::unloadPlugin() {
    // Retrieve selected item.
    QListWidgetItem* item = mSampleList->currentItem();

    // Set to default color.
    if(item) {
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        item->setForeground(brush);

        mPluginManager->unload();
        toggleLoadAndUnloadButtons(true);

        mCurrentPlugin = "";
        mStatusBar->clearMessage();
    }
}


} // End namespace ndx
