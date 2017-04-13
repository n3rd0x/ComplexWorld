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
#include "BubbleSort.h"
#include "Controller.h"

// ndxLib includes
#include "ndxNumberGenerator.h"

// POCO includes
#include <Poco/Stopwatch.h>

// Qt includes
#include <QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
BubbleSort::BubbleSort() : Plugin(), mVisualLayout(nullptr) {
    mRowSpan = 5;
}


BubbleSort::~BubbleSort() {
}


void BubbleSort::clearDataSet(ViewDataSet& data, QGridLayout* layout) {
    for(auto& itr : data) {
        layout->removeWidget(itr);
        delete itr;
    }
    data.clear();
}


void BubbleSort::clearViewDataSet() {
    clearDataSet(mViewDataSet, mVisualLayout);
}


void BubbleSort::clearRealtimeDataSet() {
    clearDataSet(mRealtimeDataSet, mRealtimeLayout);
}


void BubbleSort::generateData(
    ViewDataSet& data, QGridLayout* layout, qint32 nums) {
    // Get number to generate.
    int num = nums;
    int col = 0;
    int row = 0;

    // Generate the data set.
    clearDataSet(data, layout);
    QFont font;
    font.setPointSize(14);
    for(int i = 0; i < num; i++) {
        QString value = QString::number((int)mNumGenerator->generate());
        QLabel* label = new QLabel(value);
        label->setFont(font);
        data.push_back(label);

        layout->addWidget(label, row, col, 1, 1, Qt::AlignCenter);
        nextInteration(row, col);
    }
}


void BubbleSort::generateRealtimeData() {
    mRealtimeNumsValue->setText(QString::number(mNumsRealtimeData->value()));
    mRealtimeElapseValue->setText("0");

    mRealtimeDataSet2.clear();
    if(!mRealtimeVisualised->isChecked() || mNumsRealtimeData->value() > 300) {
        mRealtimeVisualisation = false;
        clearRealtimeDataSet();
        for(int i = 0; i < mNumsRealtimeData->value(); i++) {
            mRealtimeDataSet2.push_back((int)mNumGenerator->generate());
        }
    }
    else {
        mRealtimeVisualisation = true;
        generateData(
            mRealtimeDataSet, mRealtimeLayout, mNumsRealtimeData->value());
    }
    mRealtimeSort->setEnabled(true);
    mRealtimeAsc->setEnabled(true);
    mRealtimeDesc->setEnabled(true);
}


void BubbleSort::generateViewData() {
    // Stop timer.
    mViewController->stopClicked();
    mViewAsc->setEnabled(true);
    mViewDesc->setEnabled(true);

    generateData(mViewDataSet, mVisualLayout, mNumsViewData->value());

    mIterator.started  = false;
    mIterator.finished = false;
}


void BubbleSort::getDataSetIndex(const int idx, int& row, int& col) {
    // Temporary calculate the row for calculating the column.
    double ratio = (double)(idx + 1) / mRowSpan;
    double tRow  = ceil(ratio);

    // Decrease the row, since our index start from 0.
    row = (int)tRow - 1.0;

    // Calculate column.
    col = mRowSpan - ((tRow * mRowSpan) - idx);
}


QLabel* BubbleSort::getItem(const int idx, QGridLayout* layout) {
    int row = 0;
    int col = 0;
    getDataSetIndex(idx, row, col);
    return dynamic_cast<QLabel*>(layout->itemAtPosition(row, col)->widget());
}


int BubbleSort::getValue(const int idx, QGridLayout* layout) {
    return getValue(getItem(idx, layout));
}


int BubbleSort::getValue(QLabel* widget) {
    return widget->text().toInt();
}


void BubbleSort::nextInteration(int& row, int& col) {
    if((col % (int)(mRowSpan - 1)) == 0 && (col != 0)) {
        row++;
        col = 0;
    }
    else {
        col++;
    }
}


void BubbleSort::sortRealtime() {
    mRealtimeSort->setEnabled(false);
    mRealtimeAsc->setEnabled(false);
    mRealtimeDesc->setEnabled(false);
    Poco::Stopwatch swe;

    // Don't visualize if size of the data set is to large.
    swe.start();
    if(!mRealtimeVisualisation) {
        for(int i = mRealtimeDataSet2.size() - 1; i >= 0; i--) {
            for(int j = 0; j < i; j++) {
                auto valA = mRealtimeDataSet2[j];
                auto valB = mRealtimeDataSet2[j + 1];
                auto swapData = false;
                if(mRealtimeAsc->isChecked()) {
                    swapData = (valA > valB);
                }
                else {
                    swapData = (valA < valB);
                }
                if(swapData) {
                    auto tmp                 = valA;
                    mRealtimeDataSet2[j]     = valB;
                    mRealtimeDataSet2[j + 1] = tmp;
                }
            }
        }
    }
    else {
        for(int i = mRealtimeDataSet.size() - 1; i >= 0; i--) {
            for(int j = 0; j < i; j++) {
                swe.stop();
                auto itemA = getItem(j, mRealtimeLayout);
                auto itemB = getItem(j + 1, mRealtimeLayout);
                auto valA  = getValue(itemA);
                auto valB  = getValue(itemB);
                auto swapData = false;
                if(mRealtimeAsc->isChecked()) {
                    swapData = (valA > valB);
                }
                else {
                    swapData = (valA < valB);
                }
                swe.start();
                if(swapData) {
                    swe.stop();
                    switchData(itemA, j, itemB, j + 1, mRealtimeLayout);
                    swe.start();
                }
            }
        }
    }
    swe.stop();
    auto elapse = swe.elapsed();
    auto sec    = elapse * 0.000001;
    mRealtimeElapseValue->setText(QString::number(sec) + " s");
}


void BubbleSort::sortVisual() {
    // Skip if no data exist.
    if(mViewDataSet.size() == 0) {
        mIterator.finished = true;
    }

    // Skip when we want to delay.
    if(mIterator.state == HL_COMPARE_DELAY || mIterator.state == HL_SWITCH_PRE
       || mIterator.state == HL_SWITCH_POST) {
        if(mIterator.state == HL_COMPARE_DELAY) {
            mIterator.state = HL_COMPARE_CONTINUE;
        }
        else if(mIterator.state == HL_SWITCH_POST) {
            mIterator.state = HL_SWITCH;
        }
        else if(mIterator.state == HL_SWITCH_PRE) {
            mIterator.state = HL_SWITCH_CONTINUE;
        }
        return;
    }

    // Initialise if not has started.
    if(!mIterator.started) {
        mIterator.started = true;
        mIterator.si      = mViewDataSet.size() - 1;
        mIterator.ei      = 0;
        mIterator.i       = mIterator.si;
        mIterator.sj      = 0;
        mIterator.j       = 0;
        mIterator.state   = HL_COMPARE;
        mViewAsc->setEnabled(false);
        mViewDesc->setEnabled(false);
    }

    // Bubble sort.
    // Ref:
    // Algoritmer og datastrukturer
    // 3.4 Boblesortering
    //
    if(!mIterator.finished) {

        // First loop, iterate through the whole data set.
        if(mIterator.i > mIterator.ei) {

            // Second loop, iterate for comparing the values.
            if(mIterator.j < mIterator.i) {

                QLabel* itemA = getItem(mIterator.j, mVisualLayout);
                QLabel* itemB = getItem(mIterator.j + 1, mVisualLayout);

                // Highlight current items.
                if(mIterator.state == HL_COMPARE) {
                    visualize(itemA, itemB, HL_COMPARE);
                }

                // Compare values, then switch if necessary.
                if(mIterator.state == HL_COMPARE_CONTINUE
                   || mIterator.state == HL_SWITCH_CONTINUE
                   || mIterator.state == HL_SWITCH) {
                    int valA = getValue(itemA);
                    int valB = getValue(itemB);
                    
                    bool swapData = false;
                    if(mViewAsc->isChecked()) {
                        swapData = (valA > valB);
                    }
                    else {
                        swapData = (valA < valB);
                    }
                    if(swapData) {
                        if(mIterator.state != HL_SWITCH
                           && mIterator.state != HL_SWITCH_CONTINUE) {
                            visualize(itemA, itemB, HL_SWITCH);
                        }
                        else if(mIterator.state == HL_SWITCH_CONTINUE) {
                            switchData(
                                itemA,
                                mIterator.j,
                                itemB,
                                mIterator.j + 1,
                                mVisualLayout);
                            mIterator.state = HL_SWITCH_POST;
                        }
                    }

                    if(mIterator.state != HL_SWITCH_PRE
                       && mIterator.state != HL_SWITCH_POST) {
                        visualize(itemA, itemB, HL_DEFAULT);

                        // Next iterator.
                        mIterator.j++;

                        // End of second loop.
                        if(mIterator.j >= mIterator.i) {
                            // Reset second loop and decrease first loop.
                            mIterator.j = 0;
                            mIterator.i--;
                        }
                    }
                }
            }

            // End first loop.
            if(mIterator.i <= mIterator.ei) {
                mIterator.finished = true;
            }
        }
    }

    // Stop when finished.
    if(mIterator.finished || !mIterator.started) {
        mViewController->stopClicked();
    }
}


void BubbleSort::shutDown() {
    if(mNumGenerator) {
        delete mNumGenerator;
    }
    clearRealtimeDataSet();
    clearViewDataSet();
    if(mVisualLayout) {
        auto parent = mVisualLayout->parentWidget();
        if(parent) {
            delete parent;
        }
        mVisualLayout = nullptr;
    }
    if(mRealtimeLayout) {
        auto parent = mRealtimeLayout->parentWidget();
        if(parent) {
            delete parent;
        }
        mRealtimeLayout = nullptr;
    }

    Plugin::shutDown();
}


bool BubbleSort::startUp(QWidget* parent) {
    // ----------------------------------------
    // UI Setup
    // ----------------------------------------
    Plugin::startUp(parent);
    setupUi(this);

    QTime time      = QTime::currentTime();
    QWidget* widget = new QWidget();
    mVisualLayout   = new QGridLayout(widget);
    mViewArea->setWidget(widget);

    widget          = new QWidget();
    mRealtimeLayout = new QGridLayout(widget);
    mRealtimeArea->setWidget(widget);

    mIterator.finished = false;
    mIterator.started  = false;
    mNumGenerator      = new NumberGenerator();
    mNumGenerator->setRange(0, 50);
    mTabWidget->setCurrentIndex(0);


    // ----------------------------------------
    // Connections
    // ----------------------------------------
    connect(
        mViewGenerate,
        &QPushButton::clicked,
        this,
        &BubbleSort::generateViewData);
    connect(
        mViewController->mButtonForward,
        &QPushButton::clicked,
        this,
        &BubbleSort::sortVisual);
    connect(
        mViewController->mTimer,
        &QTimer::timeout,
        this,
        &BubbleSort::sortVisual);
    connect(
        mTabWidget, &QTabWidget::currentChanged, this, &BubbleSort::tabChanged);
    connect(
        mRealtimeGenerate,
        &QPushButton::clicked,
        this,
        &BubbleSort::generateRealtimeData);
    connect(
        mRealtimeSort, &QPushButton::clicked, this, &BubbleSort::sortRealtime);

    return true;
}


void BubbleSort::switchData(
    const int idxA, const int idxB, QGridLayout* layout) {
    switchData(
        getItem(idxA, layout), idxA, getItem(idxB, layout), idxB, layout);
}


void BubbleSort::switchData(
    QLabel* itemA,
    const int idxA,
    QLabel* itemB,
    const int idxB,
    QGridLayout* layout) {
    // Retrieve indices.
    int rowA, colA, rowB, colB;
    getDataSetIndex(idxA, rowA, colA);
    getDataSetIndex(idxB, rowB, colB);

    // Switch "data".
    layout->removeWidget(itemA);
    layout->removeWidget(itemB);
    layout->addWidget(itemB, rowA, colA, 1, 1, Qt::AlignCenter);
    layout->addWidget(itemA, rowB, colB, 1, 1, Qt::AlignCenter);
}


void BubbleSort::tabChanged(int idx) {
    mViewController->stopClicked();
}


void BubbleSort::visualize(QLabel* iA, QLabel* iB, const Highlights state) {
    switch(state) {
    // ----------------------------------------
    // Compare State
    // ----------------------------------------
    case HL_COMPARE:
        iA->setStyleSheet("font-weight: bold; color: red;");
        iB->setStyleSheet("font-weight: bold; color: blue;");
        mIterator.state = HL_COMPARE_DELAY;
        break;
    case HL_SWITCH:
        // iA->setStyleSheet("font-weight: bold; background-color: red; color:
        // white;");
        // iB->setStyleSheet("font-weight: bold; background-color: blue; color:
        // white;");
        iA->setStyleSheet(
            "font-weight: bold; font-style: italic; text-decoration: "
            "underline; color: red;");
        iB->setStyleSheet(
            "font-weight: bold; font-style: italic; text-decoration: "
            "underline; color: blue;");
        mIterator.state = HL_SWITCH_PRE;
        break;
    default:
        iA->setStyleSheet("");
        iB->setStyleSheet("");
        mIterator.state = HL_COMPARE;
    }
}


}  // End namespace ndx
