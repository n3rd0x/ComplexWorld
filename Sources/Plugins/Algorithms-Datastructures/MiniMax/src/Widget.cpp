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
#include "Widget.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include <QtGui>
#include <QRandomGenerator>


namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const std::string Widget::TAG = "Widget";




// ************************************************************
// Class Implementations
// ************************************************************
Widget::Widget() : Plugin() {
}


Widget::~Widget() {
    LOG_DEBUG_LEVEL_PREFIX("Destructor.", TAG);
}


void Widget::clear() {
    mGameNodes.clear();
}


void Widget::gameNewRound() {
    mGameView->newRound();
    mGameStatus->setText("GAME IN PROCESS!");
}


void Widget::gameReset() {
    mScoreA->setValue(0);
    mScoreB->setValue(0);
    mGameStatus->setText("CLICK ON NEW ROUND TO BEGIN!");
}


void Widget::gameWinner(qint32 winner) {
    if(winner == 1) {
        mScoreA->setValue(mScoreA->value() + 1);
        mGameStatus->setText("X WINS!");
    }
    else if(winner == 2) {
        mScoreB->setValue(mScoreB->value() + 1);
        mGameStatus->setText("O WINS!");
    }
    else {
        mGameStatus->setText("TIE GAME!");
    }
}


void Widget::generateDepth(const qint32 depth, Cell* parent) {
    // Generate random children.
    auto children = QRandomGenerator::global()->bounded(2, 4);
    auto width    = children * 30;
    for(auto c = 0; c < children; c++) {
        auto item = new Cell("", Cell::State::O, parent);


        // Assign final value in the last depth.
        if(depth == mDepth->value() - 1) {
            item->setMiniMaxValue(QRandomGenerator::global()->generate());
        }
        else {
            generateDepth(depth + 1, item);
        }
    }
}


void Widget::generateValues() {
    clear();

    // Create hierachy level based on depth value.
    // For each level random generate node between 2 and 4.
    // At the bottom level, random assign value.
    //    auto parent = new Cell();
    //    parent->setPos(10, 10);

    //    mGameNodes.push_front(parent);
    //    generateDepth(0, parent);

    //    mGameScene->addItem(parent);
}


void Widget::itemDoubleClicked(QListWidgetItem* item) {
    Q_UNUSED(item)
}


void Widget::shutDown() {
    mGameView->shutDown();
    Plugin::shutDown();
}


bool Widget::startUp(QWidget* parent) {
    // ----------------------------------------
    // UI Setup
    // ----------------------------------------
    Plugin::startUp(parent);
    setupUi(this);

    mGameView->startUp();

    clear();

    mTabWidget->setCurrentIndex(0);
    connect(mViewController->mButtonForward, &QPushButton::clicked, this, &Widget::proceedCalcualtion);
    connect(mViewController->mTimer, &QTimer::timeout, this, &Widget::proceedCalcualtion);
    connect(mBtnGenerate, &QPushButton::clicked, this, &Widget::generateValues);
    connect(mBtnGameReset, &QPushButton::clicked, this, &Widget::gameReset);
    connect(mBtnGameNewRound, &QPushButton::clicked, this, &Widget::gameNewRound);
    connect(mGameView, &GameView::sWinner, this, &Widget::gameWinner);
    return true;
}


void Widget::proceedCalcualtion() {
    bool proceed = true;
}


void Widget::restartCalculation() {
}


void Widget::tabChanged(int idx) {
    Q_UNUSED(idx)
}


}  // End namespace ndx
