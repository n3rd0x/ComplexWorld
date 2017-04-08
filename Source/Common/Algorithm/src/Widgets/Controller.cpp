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
#include "Controller.h"

// Qt includes
#include<QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
Controller::Controller(QWidget* parent) : QWidget(parent) {
    // Setup UI.
    setupUi(this);
    mTimer = new QTimer();

    // Default milliseconds.
    mMinimumSpeed = 2000;

    // Make connections.
    connect(mButtonStart,   &QPushButton::clicked, this, &Controller::startClicked);
    connect(mButtonStop,    &QPushButton::clicked, this, &Controller::stopClicked);
    connect(mButtonForward, &QPushButton::clicked, this, &Controller::forwardClicked);
}


Controller::~Controller() {
    if(mTimer) { delete mTimer; }
}


void Controller::forwardClicked() {
    toggleButtons(true);
}


int Controller::getSpeedValue() {
    double ratio = (double)mSliderSpeed->value() / (double)mSliderSpeed->maximum();
    return mMinimumSpeed * ratio;
}


void Controller::setSpeedValue(const int ms) {
    ms < 0 ? mMinimumSpeed = 0 : mMinimumSpeed = ms;
}


void Controller::startClicked() {
    // Disable start and slider interaction.
    toggleButtons(false);

    // Start the timer based on the slider value.
    mTimer->setInterval(getSpeedValue());
    mTimer->start();
}


void Controller::stopClicked() {
    // Enable start and slider integration.
    toggleButtons(true);
    mTimer->stop();
}


void Controller::toggleButtons(const bool state) {
    mButtonStart->setEnabled(state);
    mSliderSpeed->setEnabled(state);
    mButtonStop->setEnabled(!state);
}


} // End namespace ndx
