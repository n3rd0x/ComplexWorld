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
#include "EchoForm.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include<QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
EchoForm::EchoForm() : Plugin() {
}


EchoForm::~EchoForm() {
}


void EchoForm::displayMessage() {
	if(!mForm->text().isEmpty()) {
		QMessageBox::information(
			this,
			"Display Message",
			mForm->text()
		);
	}
}


void EchoForm::shutDown() {
    LOG_DEBUG_LEVEL_PREFIX("Shutdown up plug-in.", "EchoForm");
	Plugin::shutDown();
}


bool EchoForm::startUp(QWidget* parent) {
    LOG_DEBUG_LEVEL_PREFIX("Starting up plug-in.", "EchoForm");
	Plugin::startUp(parent);

	// Setup objects from the UI form.
	setupUi(this);

	// Setup connections.
	connect(mSend, &QPushButton::clicked, this, &EchoForm::displayMessage);
    return true;
}


} // End namespace ndx