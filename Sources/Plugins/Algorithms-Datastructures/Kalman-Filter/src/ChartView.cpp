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
#include "ChartView.h"

// ndxLib includes
#include "ndxLogManager.h"

#include <QtDebug>
namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const std::string ChartView::TAG = "ChartView";




// ************************************************************
// Class Implementations
// ************************************************************
ChartView::ChartView(QWidget* parent) : QChartView(new QChart(), parent) {
    mSeriesEst = nullptr;
    mSeriesMea = nullptr;
    setRenderHint(QPainter::Antialiasing);

    // TST 2019-03-23
    // TODO: Seems having series making the crash.
}


ChartView::~ChartView() {
    LOG_CRITICAL_LEVEL("Destructor (ChartView)");
}


void ChartView::add(const double vMea, const double vEst, const int index) {
    if(mSeriesEst) {
        mSeriesEst->append(static_cast<double>(index), vEst);
    }

    if(mSeriesMea) {
        mSeriesMea->append(static_cast<double>(index), vMea);
    }
}


void ChartView::clean() {
    chart()->removeAllSeries();
    mSeriesEst = nullptr;
    mSeriesMea = nullptr;
}


void ChartView::clear() {
    if(mSeriesEst) {
        mSeriesEst->clear();
    }

    if(mSeriesMea) {
        mSeriesMea->clear();
    }
}


void ChartView::setRange(const double low, const double high, const int size) {
    chart()->removeAllSeries();
    mSeriesEst = nullptr;
    mSeriesMea = nullptr;
    if(size <= 100) {
        mSeriesEst = new QLineSeries();
        mSeriesEst->setName("Estimate");

        mSeriesMea = new QScatterSeries();
        mSeriesMea->setName("Measurement");

        chart()->addSeries(mSeriesEst);
        chart()->addSeries(mSeriesMea);
    }
    else {
        mSeriesEst = new QLineSeries();
        mSeriesEst->setName("Estimate");
        chart()->addSeries(mSeriesEst);
    }

    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    chart()->axisY()->setRange(low - 2.0, high + 2.0);
    chart()->axisX()->setRange(-1, size + 1);
}


void ChartView::showMeasurement(bool state) {
    if(mSeriesMea) {
        state ? mSeriesMea->show() : mSeriesMea->hide();
    }
}


}  // End namespace ndx
