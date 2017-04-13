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


/**
 * Based on "Programming Game AI by Example".
 * @author Mat Buckland 2002 (fup@ai-junkie.com)
 */

// Local includes
#include "BaseGameEntity.h"


namespace ndx {


// ************************************************************
// Static Member Declarations
// ************************************************************
int BaseGameEntity::mNextId = 0;




// ************************************************************
// Class Implementations
// ************************************************************
BaseGameEntity::BaseGameEntity()
: mId(nextValidID()),
  mBoundingRadius(0.0),
  mPosition(glm::vec2(0.0, 0.0)),
  mScale(glm::vec2(1.0, 1.0)),
  mEntityType(DEFAULT_ENTITY_TYPE),
  mTag(false) {
}


BaseGameEntity::BaseGameEntity(const int entType)
: mId(nextValidID()),
  mBoundingRadius(0.0),
  mPosition(glm::vec2(0.0, 0.0)),
  mScale(glm::vec2(1.0, 1.0)),
  mEntityType(entType),
  mTag(false) {
}


BaseGameEntity::BaseGameEntity(
    const int entType, const glm::vec2& pos, const double r)
: mId(nextValidID()),
  mBoundingRadius(r),
  mPosition(pos),
  mScale(glm::vec2(1.0, 1.0)),
  mEntityType(entType),
  mTag(false) {
}


BaseGameEntity::BaseGameEntity(const int entType, const int forceID)
: mId(forceID),
  mBoundingRadius(0.0),
  mPosition(glm::vec2(0.0, 0.0)),
  mScale(glm::vec2(1.0, 1.0)),
  mEntityType(entType),
  mTag(false) {
}


BaseGameEntity::~BaseGameEntity() {
}


int BaseGameEntity::nextValidID() {
    mNextId++;
    return mNextId;
}


void BaseGameEntity::render() {
}


void BaseGameEntity::update(const double dt) {
}


}  // End namespace ndx
