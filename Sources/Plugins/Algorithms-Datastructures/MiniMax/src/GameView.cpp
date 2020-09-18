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
#include "GameView.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include <QPainter>


namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const std::string GameView::TAG = "GameView";




// ************************************************************
// Class Implementations
// ************************************************************
GameView::GameView(QWidget* parent) : QGraphicsView(parent) {
    mCellMarking = nullptr;
    mCellMarked  = 0;
    mGameOver    = true;
    mPlayerA     = true;
    this->setMouseTracking(true);
}


GameView::~GameView() {
}


qint32 GameView::checkWinner() {
    auto checkPlayer = [](const Cell* item) -> qint32 {
        if(item->state() == Cell::State::X) {
            return 1;
        }
        else if(item->state() == Cell::State::O) {
            return 2;
        }
        return -1;
    };


    if(mCellMarked >= 9) {
        return 0;
    }


    // Horizontal.
    for(auto i = 0; i < 9; i += 3) {
        auto itemA = mCells.at(i);
        auto itemB = mCells.at(i + 1);
        auto itemC = mCells.at(i + 2);
        if(itemA->isEquals(itemB) && itemB->isEquals(itemC)) {
            return checkPlayer(itemA);
        }
    }


    // Vertical.
    for(auto i = 0; i < 3; i++) {
        auto itemA = mCells.at(i);
        auto itemB = mCells.at(i + 3);
        auto itemC = mCells.at(i + 6);
        if(itemA->isEquals(itemB) && itemB->isEquals(itemC)) {
            return checkPlayer(itemA);
        }
    }


    // Diagonal.
    {
        auto itemA = mCells.at(0);
        auto itemB = mCells.at(4);
        auto itemC = mCells.at(8);
        if(itemA->isEquals(itemB) && itemB->isEquals(itemC)) {
            return checkPlayer(itemA);
        }
    }

    {
        auto itemA = mCells.at(2);
        auto itemB = mCells.at(4);
        auto itemC = mCells.at(6);
        if(itemA->isEquals(itemB) && itemB->isEquals(itemC)) {
            return checkPlayer(itemA);
        }
    }

    return -1;
}


void GameView::mouseDoubleClickEvent(QMouseEvent* evt) {
    if(mGameOver) {
        return;
    }

    auto item = static_cast<Cell*>(mScene->itemAt(mapToScene(evt->pos()), QTransform()));
    if(item && !item->isOccupied()) {
        mCellMarking = nullptr;

        mPlayerA ? item->setState(Cell::State::X) : item->setState(Cell::State::O);

        mScene->update(item->posRect());
        mCellMarked++;
        mPlayerA = !mPlayerA;

        auto res = checkWinner();
        if(res >= 0) {
            mGameOver = true;
            Q_EMIT sWinner(res);
        }
    }
}


void GameView::mouseMoveEvent(QMouseEvent* evt) {
    if(mGameOver) {
        return;
    }

    auto processLastItem = [&]() {
        if(mCellMarking) {
            mCellMarking->setState(Cell::State::NONE);
            mScene->update(mCellMarking->posRect());
            mCellMarking = nullptr;
        }
    };


    auto item = static_cast<Cell*>(mScene->itemAt(mapToScene(evt->pos()), QTransform()));
    if(item && !item->isOccupied()) {
        item->setState(Cell::State::MARKED);
        if(item != mCellMarking) {
            processLastItem();

            mCellMarking = item;
            mScene->update(item->posRect());
        }
    }
    else {
        processLastItem();
    }
}


void GameView::newRound() {
    mCellMarked = 0;
    mGameOver   = false;
    for(auto itr: mCells) {
        itr->setState(Cell::State::NONE);
        mScene->update(itr->posRect());
    }
}


void GameView::shutDown() {
    mScene->clear();
    mCells.clear();
}


bool GameView::startUp() {
    mScene.reset(new QGraphicsScene());
    this->setScene(mScene.data());

    // Setup the board.
    for(auto i = 0; i < 3; i++) {
        for(auto j = 0; j < 3; j++) {
            auto name = QString::number(j) + ", " + QString::number(i);
            auto cell = new Cell(name);
            cell->setPos(Cell::SIZE * j, Cell::SIZE * i);

            mScene->addItem(cell);
            mCells.push_back(cell);
        }
    }
    return true;
}


}  // End namespace ndx
