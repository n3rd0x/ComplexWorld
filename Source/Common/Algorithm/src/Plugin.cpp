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
#include "Plugin.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
Plugin::Plugin() : QWidget(0x0) {
}


Plugin::~Plugin() {
}


void Plugin::setMetaData(const MetaData& meta) {
	mMetaData = meta;
}


void Plugin::shutDown() {
	setParent(0x0);
}


bool Plugin::startUp(QWidget* parent) {
	setParent(parent);

	// Set default grid layout if exists.
	QGridLayout* layout = dynamic_cast<QGridLayout*>(parent->layout());
	if(layout) {
		layout->addWidget(this, 0, 0, 1, 1);
	}
    return true;
}


} // End namespace ndx
