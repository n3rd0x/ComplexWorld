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
#include "PluginWidget.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include <QtGui>


namespace ndx {


// ************************************************************
// Static Member Implementations
// ************************************************************
const std::string PluginWidget::TAG = "OgreRender";




// ************************************************************
// Class Implementations
// ************************************************************
PluginWidget::PluginWidget() : Plugin() {
}


PluginWidget::~PluginWidget() {
}


void PluginWidget::shutDown() {
    LOG_DEBUG_LEVEL_PREFIX("Shutdown up plug-in.", TAG);
    Plugin::shutDown();
}


bool PluginWidget::startUp(QWidget* parent) {
    LOG_DEBUG_LEVEL_PREFIX("Starting up plug-in.", TAG);
    Plugin::startUp(parent);

    // Setup objects from the UI form.
    setupUi(this);
    return true;
}


}  // End namespace ndx
