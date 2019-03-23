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
#include <QMessageBox>

// STL includes
#include <sstream>


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


double KalmanFilter::calculateErrorEstimate(const double KG, const double eEstP) {
    return (1.0 - KG) * eEstP;
}


double KalmanFilter::calculateEstimate(const double KG, const double vMea, const double vEstP) {
    return vEstP + (KG * (vMea - vEstP));
}


double KalmanFilter::calculateKalmanGain(const double eEst, const double eMea) {
    return eEst / (eEst + eMea);
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
    if(mRangeLow->value() > mRangeHigh->value()) {
        QMessageBox::warning(this, tr("Warning!"), tr("Range (low) must be less than range (high)."));
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
    mChartView->showMeasurement(mShowMea->isChecked());
}


void KalmanFilter::itemDoubleClicked(QListWidgetItem* item) {
    if(mDataList.count() <= 1) {
        return;
    }

    auto idx  = mMeaList->currentRow();
    auto data = mDataList[idx];

    mValue_eEstP->setValue(data.eEstP);
    mValue_eMea->setValue(data.eMea);
    mValue_vEstP->setValue(data.vEstP);
    mValue_vMea->setValue(data.vMea);
    auto KG   = calculateKalmanGain(data.eEstP, data.eMea);
    auto vEst = calculateEstimate(KG, data.vMea, data.vEstP);
    auto eEst = calculateErrorEstimate(KG, data.eEstP);
    mValue_eEst->setValue(eEst);
    mValue_vEst->setValue(vEst);
    mValue_KG->setValue(KG);

    // Verify, it should be the same.
    if(KG != data.KG) {
        LOG_CRITICAL_LEVEL_PREFIX("ERROR: Mismatch kalman gain.", TAG);
        LOG_CRITICAL_LEVEL_PREFIX("Calc: " + std::to_string(KG) + " Data: " + std::to_string(data.KG), TAG);
    }
    if(vEst != data.vEst) {
        LOG_CRITICAL_LEVEL_PREFIX("ERROR: Mismatch estimate value.", TAG);
        LOG_CRITICAL_LEVEL_PREFIX("Calc: " + std::to_string(vEst) + " Data: " + std::to_string(data.vEst), TAG);
    }
    if(eEst != data.eEst) {
        LOG_CRITICAL_LEVEL_PREFIX("ERROR: Mismatch error estimate value.", TAG);
        LOG_CRITICAL_LEVEL_PREFIX("Calc: " + std::to_string(eEst) + " Data: " + std::to_string(data.eEst), TAG);
    }
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
    connect(mShowMea, &QCheckBox::toggled, mChartView, &ChartView::showMeasurement);
    connect(mViewController->mButtonForward, &QPushButton::clicked, this, &KalmanFilter::proceedCalcualtion);
    connect(mViewController->mTimer, &QTimer::timeout, this, &KalmanFilter::proceedCalcualtion);
    connect(mTabWidget, &QTabWidget::currentChanged, this, &KalmanFilter::tabChanged);
    connect(mMeaList, &QListWidget::itemDoubleClicked, this, &KalmanFilter::itemDoubleClicked);
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
    data.KG = calculateKalmanGain(data.eEst, data.eMea);

    // Estimate value.
    data.vEst = calculateEstimate(data.KG, data.vMea, data.vEstP);

    // Error estimate value.
    data.eEst = calculateErrorEstimate(data.KG, data.eEstP);

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
