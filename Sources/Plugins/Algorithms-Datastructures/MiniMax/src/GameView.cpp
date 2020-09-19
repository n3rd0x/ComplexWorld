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
#include <QRandomGenerator>


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
    mDebug       = false;
    mGameOver    = true;
    mPlayerX     = true;
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

    if(mCellMarked >= 9) {
        return 0;
    }
    return -1;
}


Cell::State GameView::currentState() const {
    if(mPlayerX) {
        return Cell::State::X;
    }
    return Cell::State::O;
}


void GameView::drawBoardState() {
    LOG_DEBUG_LEVEL_PREFIX("Board Layout:", TAG);
    auto is = 0;
    auto ii = 0;
    for(auto i = 0; i < 3; i++) {
        std::string str = "";

        // Print states.
        for(auto j = 0; j < 3; j++) {
            str += mCells.at(is++)->layout() + " ";
        }

        // Print indices.
        for(auto j = 0; j < 3; j++) {
            str += std::to_string(mCells.at(ii++)->id()) + " ";
        }
        LOG_DEBUG_LEVEL_PREFIX(str, TAG);
    }
}


QPair<qint32, qint32> GameView::minimax(const Cell::State state, const qint32 depth) {
    if(mDebug) {
        drawBoardState();
    }

    // Check winner conditions.
    auto res = checkWinner();
    if(res == 1) {
        if(mDebug) {
            LOG_DEBUG_LEVEL_PREFIX("Winner X (+1)", TAG);
        }
        return QPair<qint32, qint32>(0, 1);
    }
    else if(res == 2) {
        if(mDebug) {
            LOG_DEBUG_LEVEL_PREFIX("Winner O (+1)", TAG);
        }
        return QPair<qint32, qint32>(0, -1);
    }
    else if(res == 0) {
        if(mDebug) {
            LOG_DEBUG_LEVEL_PREFIX("Draw (0)", TAG);
        }
        return QPair<qint32, qint32>(0, 0);
    }

    if(mDebug) {
        LOG_DEBUG_LEVEL_PREFIX("Next State (" + Cell::parseState(state) + ")", TAG);
    }

    QList<QPair<qint32, qint32>> list;
    for(auto itr: mCells) {
        if(!itr->isOccupied()) {
            if(mDebug) {
                LOG_DEBUG_LEVEL_PREFIX(
                    "[" + Cell::parseState(state) + "] Processing next moves....(" + std::to_string(itr->id()) + ")",
                    TAG);
            }
            itr->setState(state);
            itr->setOccupied(true);
            itr->setMiniMaxEnabled(true);
            mCellMarked++;

            QPair<qint32, qint32> score;
            if(state == Cell::State::X) {
                score = minimax(Cell::State::O);
            }
            else {
                score = minimax(Cell::State::X);
            }
            list.push_back(QPair<qint32, qint32>(itr->id(), score.second));
            itr->setState(Cell::State::NONE);
            itr->setOccupied(false);
            mCellMarked--;
        }
    }

    QList<QPair<qint32, qint32>> bestWins;
    QList<QPair<qint32, qint32>> bestDraws;
    for(auto itr: list) {
        if(itr.second == 0) {
            bestDraws.push_back(itr);
        }
        if(state == Cell::State::X && itr.second == 1) {
            bestWins.push_back(itr);
        }
        if(state == Cell::State::O && itr.second == -1) {
            bestWins.push_back(itr);
        }

        if(depth == 0) {
            auto item = mCells.at(itr.first);
            item->setMiniMax(itr.second);
            if((state == Cell::State::O && itr.second == 1) || (state == Cell::State::X && itr.second == -1)) {
                item->setMiniMax(-1);
            }
            if((state == Cell::State::O && itr.second == -1)) {
                item->setMiniMax(1);
            }
            mScene->update(item->posRect());
        }
    }

    if(!bestWins.isEmpty()) {
        auto idx  = QRandomGenerator::global()->bounded(0, bestWins.size());
        auto item = bestWins.at(idx);

        if(mDebug) {
            LOG_DEBUG_LEVEL_PREFIX(
                "[" + Cell::parseState(state) + "] Best win move (" + std::to_string(item.first) + ")",
                TAG);
        }
        return item;
        // return bestWins.first();
    }
    if(!bestDraws.isEmpty()) {
        auto idx  = QRandomGenerator::global()->bounded(0, bestDraws.size());
        auto item = bestDraws.at(idx);

        if(mDebug) {
            LOG_DEBUG_LEVEL_PREFIX(
                "[" + Cell::parseState(state) + "] Best draw move (" + std::to_string(item.first) + ")",
                TAG);
        }
        return item;
        // return bestDraws.first();
    }


    // When it comes to this point, it doesn't matter which one to choose.
    // The current player will loose either way, in the mindset that the other
    // will play their best move.
    // So we return 0 for the best change to make a draw.
    if(mDebug) {
        LOG_DEBUG_LEVEL_PREFIX("----------------------------------------", TAG);
        LOG_DEBUG_LEVEL_PREFIX("[" + Cell::parseState(state) + "] Random move.", TAG);
        drawBoardState();
        for(auto itr: list) {
            LOG_DEBUG_LEVEL_PREFIX(
                "[" + Cell::parseState(state) + "] " + std::to_string(itr.first) + "::" + std::to_string(itr.second),
                TAG);
        }
        LOG_DEBUG_LEVEL_PREFIX("----------------------------------------", TAG);
    }

    auto idx  = QRandomGenerator::global()->bounded(0, list.size());
    auto item = list.at(idx);

    // return list.first();
    // return QPair<qint32, qint32>(0, 0);
    return QPair<qint32, qint32>(item.first, 0);
}


void GameView::mouseDoubleClickEvent(QMouseEvent* evt) {
    if(mGameOver) {
        return;
    }

    auto item = static_cast<Cell*>(mScene->itemAt(mapToScene(evt->pos()), QTransform()));
    if(item && !item->isOccupied()) {
        mCellMarking = nullptr;

        auto state = mPlayerX ? Cell::State::X : Cell::State::O;
        item->setState(state);
        item->setMiniMax(0);
        item->setMiniMaxEnabled(false);
        item->setMarking(false);
        item->setOccupied(true);

        mScene->update(item->posRect());
        mCellMarked++;
        mPlayerX = !mPlayerX;

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
            mCellMarking->setMarking(false);
            mScene->update(mCellMarking->posRect());
            mCellMarking = nullptr;
        }
    };


    auto item = static_cast<Cell*>(mScene->itemAt(mapToScene(evt->pos()), QTransform()));
    if(item && !item->isOccupied()) {
        item->setState(currentState());
        item->setMarking(true);

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
        auto item = static_cast<Cell*>(itr);
        item->reset();
        mScene->update(item->posRect());
    }
}


void GameView::runMiniMax() {
    auto state = currentState();
    auto move  = minimax(state);
    LOG_DEBUG_LEVEL_PREFIX("Best move: " + std::to_string(move.first), TAG);
}


void GameView::shutDown() {
    mScene->clear();
    mCells.clear();
}


bool GameView::startUp() {
    mScene.reset(new QGraphicsScene());
    this->setScene(mScene.data());

    // Setup the board.
    auto id = 0;
    for(auto i = 0; i < 3; i++) {
        for(auto j = 0; j < 3; j++) {
            auto cell = new Cell(id++);
            cell->setPos(Cell::SIZE * j, Cell::SIZE * i);

            mScene->addItem(cell);
            mCells.push_back(cell);
        }
    }
    return true;
}


}  // End namespace ndx
