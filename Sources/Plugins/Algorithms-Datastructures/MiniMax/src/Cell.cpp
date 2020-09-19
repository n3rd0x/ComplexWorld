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
#include "Cell.h"

// ndxLib includes
#include "ndxLogManager.h"

// Qt includes
#include <QPainter>


namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const qint32 Cell::SIZE     = 100;
const std::string Cell::TAG = "Cell";


std::string Cell::parseState(Cell::State state) {
    if(state == State::X) {
        return "X";
    }
    else if(state == State::O) {
        return "O";
    }
    return " ";
}




// ************************************************************
// Class Implementations
// ************************************************************
Cell::Cell(const qint32 id, const State state, QGraphicsItem* parent) : QGraphicsItem(parent), mID(id), mState(state) {
    mMarking        = false;
    mMiniMax        = 0;
    mMiniMaxEnabled = false;
    mOccupied       = false;
}


Cell::~Cell() {
    LOG_DEBUG_LEVEL_PREFIX("Destructor", TAG);
}


QRectF Cell::boundingRect() const {
    return QRectF(0, 0, SIZE, SIZE);
}


qint32 Cell::id() const {
    return mID;
}


bool Cell::isEquals(const Cell* other) const {
    if(mState == State::X || mState == State::O) {
        return mState == other->mState;
    }
    return false;
}


bool Cell::isOccupied() const {
    return mOccupied;
}


std::string Cell::layout() const {
    return parseState(mState);
}


qint32 Cell::minimax() const {
    return mMiniMax;
}


QString Cell::name() const {
    QString name = QString::number(mID);
    name += " (" + QString::fromStdString(layout()) + ")";
    return name;
}


void Cell::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    const qint32 margin = 4;
    if(mMarking) {
        painter->setBrush(Qt::yellow);
        painter->drawRect(0, 0, SIZE, SIZE);
    }
    painter->setBrush(Qt::NoBrush);

    if(mState == State::X) {
        painter->setPen(QPen(Qt::green, margin));
        painter->drawLine(margin, margin, SIZE - margin, SIZE - margin);
        painter->drawLine(SIZE - margin, margin, margin, SIZE - margin);
    }
    else if(mState == State::O) {
        painter->setPen(QPen(Qt::red, margin));
        painter->drawEllipse(margin, margin, SIZE - margin * 2, SIZE - margin * 2);
    }

    painter->setPen(QPen(Qt::black, 1));
    painter->drawRect(0, 0, SIZE, SIZE);

    if(mMiniMaxEnabled && !mOccupied) {
        QFontMetricsF fm(painter->font());
        QString txt = QString::number(mMiniMax);
        auto cx     = static_cast<qint32>((SIZE / 2.0) - (fm.width(txt) / 2.0));
        auto cy     = static_cast<qint32>((SIZE / 2.0) + (fm.height() / 2.0));
        painter->drawText(cx, cy, txt);
    }
}


QRectF Cell::posRect() {
    return QRectF(pos().rx(), pos().ry(), SIZE, SIZE);
}


void Cell::reset() {
    setMiniMax(0);
    setMiniMaxEnabled(false);
    setMarking(false);
    setOccupied(false);
    setState(Cell::State::NONE);
}


void Cell::setMarking(const bool state) {
    mMarking = state;
}


void Cell::setMiniMax(const qint32 value) {
    mMiniMax = value;
}


void Cell::setMiniMaxEnabled(const bool value) {
    mMiniMaxEnabled = value;
}


void Cell::setOccupied(const bool state) {
    mOccupied = state;
}


void Cell::setState(const State state) {
    mState = state;
}


Cell::State Cell::state() const {
    return mState;
}


}  // End namespace ndx
