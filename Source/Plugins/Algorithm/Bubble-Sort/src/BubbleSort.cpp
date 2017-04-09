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

// Qt includes
#include<QtGui>


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
BubbleSort::BubbleSort() : Plugin(), mViewGridLayout(0x0) {
    mRowSpan = 5;
}


BubbleSort::~BubbleSort() {
}


void BubbleSort::clearDataSet() {
    for(auto& itr : mViewDataSet) {
        mViewGridLayout->removeWidget(itr);
        delete itr;
    }
    mViewDataSet.clear();
}


void BubbleSort::generateData() {
    // Stop timer.
    mController->stopClicked();

    // Get number to generate.
    int num = mDataSpinBoxNumToGenerate->value();
    int col = 0;
    int row = 0;

    // Generate the data set.
    clearDataSet();
    QFont font;
    font.setPointSize(14);
    for(int i = 0; i < num; i++) {
        QString value = QString::number(mNumGenerator->generate());
        QLabel* label = new QLabel(value, mViewGroupBox);
        label->setFont(font);
        mViewDataSet.push_back(label);  

        mViewGridLayout->addWidget(label, row, col, 1, 1, Qt::AlignCenter);
        nextInteration(row, col);
    }

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


QLabel* BubbleSort::getItem(const int idx) {
    int row = 0;
    int col = 0;
    getDataSetIndex(idx, row, col);
    return dynamic_cast<QLabel*>(mViewGridLayout->itemAtPosition(row, col)->widget());
}


int BubbleSort::getValue(const int idx) {
    return getValue(getItem(idx));
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


void BubbleSort::sort() {
    // Skip if no data exist.
    if(mViewDataSet.size() == 0) {
        mIterator.finished = true;
    }

    // Skip when we want to delay.
    if(mIterator.state == HL_COMPARE_DELAY || mIterator.state == HL_SWITCH_PRE || mIterator.state == HL_SWITCH_POST) {
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
        mIterator.started   = true;
        mIterator.si        = mViewDataSet.size() - 1;
        mIterator.ei        = 0;
        mIterator.i         = mIterator.si;
        mIterator.sj        = 0;
        mIterator.j         = 0;
        mIterator.state     = HL_COMPARE;
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

                QLabel* itemA = getItem(mIterator.j);
                QLabel* itemB = getItem(mIterator.j + 1);
                
                // Highlight current items.
                if(mIterator.state == HL_COMPARE) {
                    visualize(itemA, itemB, HL_COMPARE);
                }

                // Compare values, then switch if necessary.
                if(mIterator.state == HL_COMPARE_CONTINUE || mIterator.state == HL_SWITCH_CONTINUE || mIterator.state == HL_SWITCH) {
                    int valA = getValue(itemA);
                    int valB = getValue(itemB);
                    if(valA > valB) {
                        if(mIterator.state != HL_SWITCH && mIterator.state != HL_SWITCH_CONTINUE) {
                            visualize(itemA, itemB, HL_SWITCH);
                        }
                        else if(mIterator.state == HL_SWITCH_CONTINUE) {
                            switchData(itemA, mIterator.j, itemB, mIterator.j + 1);
                            mIterator.state = HL_SWITCH_POST;
                        }
                    }

                    if(mIterator.state != HL_SWITCH_PRE && mIterator.state != HL_SWITCH_POST) {
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
        mController->stopClicked();
    }
}


void BubbleSort::shutDown() {
    if(mNumGenerator)   { delete mNumGenerator; }
    clearDataSet();
    if(mViewGridLayout) { delete mViewGridLayout; }
	Plugin::shutDown();
}


bool BubbleSort::startUp(QWidget* parent) {
    // ************************************************************
    // UI setup
    // ************************************************************
	Plugin::startUp(parent);
	setupUi(this);

    QTime time      = QTime::currentTime();
    mNumGenerator   = new NumberGenerator();
    mViewGridLayout = new QGridLayout(mViewGroupBox);
    mNumGenerator->setRange(0, 50);

    mIterator.finished  = false;
    mIterator.started   = false;


    // ************************************************************
    // Connect
    // ************************************************************
    connect(mDataButtonGenerate, &QPushButton::clicked, this, &BubbleSort::generateData);
    connect(mController->mButtonForward, &QPushButton::clicked, this, &BubbleSort::sort);
    connect(mController->mTimer, &QTimer::timeout, this, &BubbleSort::sort);

    return true;
}


void BubbleSort::switchData(const int idxA, const int idxB) {
    switchData(getItem(idxA), idxA, getItem(idxB), idxB);
}


void BubbleSort::switchData(QLabel* itemA, const int idxA, QLabel* itemB, const int idxB) {
    // Retrieve indices.
    int rowA, colA, rowB, colB;
    getDataSetIndex(idxA, rowA, colA);
    getDataSetIndex(idxB, rowB, colB);

    // Switch "data".
    mViewGridLayout->removeWidget(itemA);
    mViewGridLayout->removeWidget(itemB);
    mViewGridLayout->addWidget(itemB, rowA, colA, 1, 1, Qt::AlignCenter);
    mViewGridLayout->addWidget(itemA, rowB, colB, 1, 1, Qt::AlignCenter);
}


void BubbleSort::visualize(QLabel* iA, QLabel* iB, const Highlights state) {
    switch(state) {
    // ************************************************************
    // Compare State
    // ************************************************************
    case HL_COMPARE:
        iA->setStyleSheet("font-weight: bold; color: red;");
        iB->setStyleSheet("font-weight: bold; color: blue;");
        mIterator.state = HL_COMPARE_DELAY;
        break;
    case HL_SWITCH:
        //iA->setStyleSheet("font-weight: bold; background-color: red; color: white;");
        //iB->setStyleSheet("font-weight: bold; background-color: blue; color: white;");
        iA->setStyleSheet("font-weight: bold; font-style: italic; text-decoration: underline; color: red;");
        iB->setStyleSheet("font-weight: bold; font-style: italic; text-decoration: underline; color: blue;");
        mIterator.state = HL_SWITCH_PRE;
        break;
    default:
        iA->setStyleSheet("");
        iB->setStyleSheet("");
        mIterator.state = HL_COMPARE;
    }
}


} // End namespace ndx
