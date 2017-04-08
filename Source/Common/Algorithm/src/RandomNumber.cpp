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
#include "RandomNumber.h"


namespace ndx {


// ************************************************************
// Class Implementations
// ************************************************************
RandomNumber::RandomNumber(const uint seed) {
	setSeed(seed);
    mLow  = 0;
    mHigh = 100;
}


RandomNumber::RandomNumber(const int low, const int high, const uint seed) {
    setSeed(seed);
    mLow  = low;
    mHigh = high;
}


int RandomNumber::generate() {
    return generate(mLow, mHigh);
}


int RandomNumber::generate(const int low, const int high) {
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}


void RandomNumber::setRange(const int low, const int high) {
    mLow  = low;
    mHigh = high;
}


void RandomNumber::setSeed(const uint seed) {
    if(seed != 0) {
        qsrand(seed);
    }
}


} // End namespace ndx
