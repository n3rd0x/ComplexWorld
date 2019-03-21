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
#include "ndxNumberGenerator.h"
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

    mTabWidget->setCurrentIndex(0);

    double eEst  = 2.0;
    double eEstP = 0.0;
    double eMea  = 4.0;
    double KG    = 0.5;
    double est   = 68.0;
    double estP  = 0.0;
    double mea   = 0.0;

    auto random = new NumberGenerator();
    random->setRange(50, 80);

    int num    = 10000;
    double avg = 0.0;

    std::vector<double> data;
    for(auto i = 0; i < num; i++) {
        data.push_back(random->generate());
        avg += data.back();
    }

    random->setRange(70, 90);
    for(auto i = 0; i < num; i++) {
        data.push_back(random->generate());
        avg += data.back();
    }
    est = data.front();

    for(unsigned int i = 0; i < data.size(); i++) {
        std::stringstream ss;

        mea   = data[i];
        eEstP = eEst;
        estP  = est;

        ss << "Calculation:" << std::endl;
        ss << "mea:   " << mea << std::endl;
        ss << "eMea:  " << eMea << std::endl;
        ss << "estP:  " << estP << std::endl;
        ss << "eEstP: " << eEstP << std::endl;
        ss << "----------" << std::endl;

        // Kalman gain.
        KG = eEst / (eEst + eMea);

        // Estimate.
        est = estP + KG * (mea - estP);

        // Error estimate.
        eEst = (1 - KG) * eEstP;

        ss << "KG:    " << KG << std::endl;
        ss << "est:   " << est << std::endl;
        ss << "eEst:  " << eEst << std::endl;
        LOG_DEBUG_LEVEL_PREFIX(ss.str(), TAG);
    }

    avg = avg / (num * 2);
    LOG_DEBUG_LEVEL_PREFIX("Avg: " + std::to_string(avg), TAG);


    // ----------------------------------------
    // Connections
    // ----------------------------------------
    connect(mTabWidget, &QTabWidget::currentChanged, this, &KalmanFilter::tabChanged);
    return true;
}


void KalmanFilter::tabChanged(int idx) {
}


}  // End namespace ndx
