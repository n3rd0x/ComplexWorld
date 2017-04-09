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


#ifndef _ndxNumberGenerator_h_
#define _ndxNumberGenerator_h_


// Local includes
#include "ndxPrerequisites.h"

// STL includes
#include <random>


namespace ndx {


/**
 * A random number generator.
 */
class _ndxLibExport NumberGenerator {
public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
        * Constructor with initialisation of range number.
        * @param low Low range.
        * @param high High range.
     */
    NumberGenerator(const double low = 0.0, const double high = 100.0);


    /**
     * @return A random number.
     */
    double generate();


    /**
     * Set random range.
     * @param low Lower range.
     * @param high High range.
     */
    void setRange(const double low, const double high);




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @param low Low number.
     * @param high High number.
     * @return A random number.
     */
    static double generate(const double low, const double high);




protected:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Low number.
     */
    double mLow;


    /**
     * High number.
     */
    double mHigh;




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * Default random engine.
     */
    static std::default_random_engine mGenerator;




};  // End class NumberGenerator


}  // End namespace ndx


#endif  // _ndxNumberGenerator_h_
