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
#include "ndxNumberGenerator.h"

// STL includes
#include <chrono>


namespace ndx {


// ************************************************************
// Static Implementations
// ************************************************************
std::default_random_engine NumberGenerator::mGenerator(std::chrono::system_clock::now().time_since_epoch().count());


double NumberGenerator::generate(const double low, const double high) {
    std::uniform_real_distribution<double> distributor(low, high);
    return distributor(mGenerator);
}




// ************************************************************
// Class Implementations
// ************************************************************
NumberGenerator::NumberGenerator(const double low, const double high) {
    setRange(low, high);
}


double NumberGenerator::generate() {
    return generate(mLow, mHigh);
}


void NumberGenerator::setRange(const double low, const double high) {
    mLow  = low;
    mHigh = high;
}


} // End namespace ndx
