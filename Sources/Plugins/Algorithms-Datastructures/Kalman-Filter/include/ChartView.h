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


#ifndef _ChartView_h_
#define _ChartView_h_


// ndxLibrary includes
#include <ndxPrerequisites.h>

// Qt includes
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QScopedPointer>

// STL includes
#include <string>


namespace ndx {

// ************************************************************
// Namespaces
// ************************************************************
QT_CHARTS_USE_NAMESPACE


/**
 * Chart view.
 */
class ChartView : public QChartView {
    Q_OBJECT

public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    ChartView(QWidget* parent = nullptr);


    /**
     * Default destructor.
     */
    ~ChartView();


    /**
     * @brief Add plot.
     * @param vMea Measurement value.
     * @param vEst Estimate value.
     * @param index Current index.
     */
    void add(const double vMea, const double vEst, const int index);


    /**
     * @brief Clean.
     */
    void clean();


    /**
     * @brief Clear the chart.
     */
    void clear();


    /**
     * @brief Set range.
     * @param low Lowest value.
     * @param high Highest value.
     * @param size Size of range.
     */
    void setRange(const double low, const double high, const int size);


public slots:
    /**
     * @brief Show measurement.
     * @param state State to set.
     */
    void showMeasurement(bool state);


protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * @brief References.
     */
    QLineSeries* mSeriesEst;
    QScatterSeries* mSeriesMea;


    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @brief Logging tag.
     */
    static const std::string TAG;


};  // End class ChartView


}  // End namespace ndx


#endif  // _ChartView_h_
