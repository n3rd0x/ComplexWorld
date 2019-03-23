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
#include "KalmanFilter.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include <QtGui>

// STL includes
#include <sstream>
#include <vector>


namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const std::string KalmanFilter::TAG = "KalmanFilter";




// ************************************************************
// Class Implementations
// ************************************************************
KalmanFilter::KalmanFilter() : Plugin() {
}


KalmanFilter::~KalmanFilter() {
    mNumberGenerator.reset();
    LOG_DEBUG_LEVEL_PREFIX("Destructor.", TAG);
}


void KalmanFilter::clear() {
    mDataList.clear();
    mMeaList->clear();
    mChartView->clear();
    mCurrentIndex    = 0;
    mGlobalRangeLow  = 10000;
    mGlobalRangeHigh = -10000;
    mGlobalSize      = 0;
}


void KalmanFilter::generateMeaValues() {
    if(mNum->value() == 0) {
        return;
    }
    restartCalculation();

    // Update values.
    mGlobalSize += mNum->value();
    if(mGlobalRangeLow > mRangeLow->value()) {
        mGlobalRangeLow = mRangeLow->value();
    }
    if(mGlobalRangeHigh < mRangeHigh->value()) {
        mGlobalRangeHigh = mRangeHigh->value();
    }

    // Generate random numbers.
    mNumberGenerator->setRange(mRangeLow->value(), mRangeHigh->value());
    for(auto i = 0; i < mNum->value(); i++) {
        auto value = QString::number(mNumberGenerator->generate(), 'g', 2);
        mMeaList->addItem(value);
    }

    // Set chart range and group title.
    mChartView->setRange(mGlobalRangeLow, mGlobalRangeHigh, mGlobalSize);
}


void KalmanFilter::shutDown() {
    Plugin::shutDown();
}


bool KalmanFilter::startUp(QWidget* parent) {
    // ----------------------------------------
    // UI Setup
    // ----------------------------------------
    Plugin::startUp(parent);
    setupUi(this);

    clear();
    mTabWidget->setCurrentIndex(0);
    mNumberGenerator.reset(new NumberGenerator());
    mChartView->setRange(mRangeLow->value(), mRangeHigh->value(), mNum->value());


    // ----------------------------------------
    // Connections
    // ----------------------------------------
    connect(mButtonClear, &QPushButton::clicked, this, &KalmanFilter::clear);
    connect(mButtonGenerate, &QPushButton::clicked, this, &KalmanFilter::generateMeaValues);
    connect(mButtonRestart, &QPushButton::clicked, this, &KalmanFilter::restartCalculation);
    connect(mViewController->mButtonForward, &QPushButton::clicked, this, &KalmanFilter::proceedCalcualtion);
    connect(mViewController->mTimer, &QTimer::timeout, this, &KalmanFilter::proceedCalcualtion);
    connect(mTabWidget, &QTabWidget::currentChanged, this, &KalmanFilter::tabChanged);
    return true;
}


void KalmanFilter::proceedCalcualtion() {
    bool proceed = true;
    if(mCurrentIndex < 0) {
        proceed = false;
    }
    if(mCurrentIndex >= mMeaList->count()) {
        proceed = false;
    }

    if(!proceed) {
        mViewController->stopClicked();
        return;
    }

    // Get current measurement value from the list.
    auto mea = mMeaList->item(mCurrentIndex)->data(Qt::DisplayRole).toDouble();

    // Store data.
    Data data;
    data.index = mCurrentIndex;
    data.eMea  = mInit_eMea->value();
    data.vMea  = mea;

    // Find previous data.
    if(mCurrentIndex > 0) {
        auto prev  = mDataList[mCurrentIndex - 1];
        data.eEst  = prev.eEst;
        data.eEstP = prev.eEst;
        data.vEst  = prev.vEst;
        data.vEstP = prev.vEst;
    }
    else {
        data.eEst  = data.eMea / 2.0;
        data.eEstP = data.eEst;
        data.vEst  = data.vMea;
        data.vEstP = data.vEst;
    }

    // ----------------------------------------
    // Kalman Filter Calculation
    // ----------------------------------------
    // Kalman gain.
    data.KG = data.eEst / (data.eEst + data.eMea);

    // Estimate value.
    data.vEst = data.vEstP + (data.KG * (data.vMea - data.vEstP));

    // Error estimate value.
    data.eEst = (1 - data.KG) * data.eEstP;

    // Process to next iteration.
    mChartView->add(data.vMea, data.vEst, mCurrentIndex);
    mDataList.append(data);
    mCurrentIndex++;
}


void KalmanFilter::restartCalculation() {
    mCurrentIndex = 0;
    mChartView->clear();
    mDataList.clear();
}


void KalmanFilter::tabChanged(int idx) {
}


}  // End namespace ndx
