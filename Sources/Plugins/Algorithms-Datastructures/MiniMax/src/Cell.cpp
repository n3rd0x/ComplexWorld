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

#include <QDebug>
namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
const qint32 Cell::SIZE     = 100;
const std::string Cell::TAG = "Cell";




// ************************************************************
// Class Implementations
// ************************************************************
Cell::Cell(const QString& name, const State state, QGraphicsItem* parent) :
    QGraphicsItem(parent), mName(name), mState(state) {
    mMiniMax = 0;
}


Cell::~Cell() {
}


QRectF Cell::boundingRect() const {
    return QRectF(0, 0, SIZE, SIZE);
}


bool Cell::isEquals(const Cell* other) const {
    if(mState == State::X || mState == State::O) {
        return mState == other->mState;
    }
    return false;
}


bool Cell::isOccupied() const {
    return (mState == State::X || mState == State::O);
}


QString Cell::name() const {
    QString name = mName;
    if(mState == State::X) {
        name += " -> X";
    }
    else if(mState == State::O) {
        name += " -> O";
    }
    return name;
}


void Cell::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    const qint32 margin = 4;
    if(mState == State::X) {
        painter->setPen(QPen(Qt::green, margin));
        painter->drawLine(margin, margin, SIZE - margin, SIZE - margin);
        painter->drawLine(SIZE - margin, margin, margin, SIZE - margin);
    }
    else if(mState == State::O) {
        painter->setPen(QPen(Qt::red, margin));
        painter->drawEllipse(margin, margin, SIZE - margin * 2, SIZE - margin * 2);
    }
    else if(mState == State::MARKED) {
        painter->setBrush(Qt::red);
        painter->drawRect(0, 0, SIZE, SIZE);
    }
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRect(0, 0, SIZE, SIZE);
}


QRectF Cell::posRect() {
    return QRectF(pos().rx(), pos().ry(), SIZE, SIZE);
}


void Cell::setMiniMaxValue(const qint32 value) {
    mMiniMax = value;
}


void Cell::setState(const State state) {
    mState = state;
}


Cell::State Cell::state() const {
    return mState;
}


}  // End namespace ndx
