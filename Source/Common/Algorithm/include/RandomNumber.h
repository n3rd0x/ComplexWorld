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


#ifndef __RandomNumber_h__
#define __RandomNumber_h__


// Qt includes
#include <QtCore>


namespace ndx {


/**
 * Random generator.
 * Reference:
 *   - http://developer.nokia.com/Community/Wiki/Generating_random-value_integers_in_Qt
 */
class RandomNumber {
public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
	/**
	 * Default constructor with initialisation of range [0, 100]
     * @param seed Generate seed for the random number.
	 */
	RandomNumber(const uint seed = 0);


    /**
	 * Constructor with initialisation of range number.
     * @param low Low range.
     * @param high High range.
     * @param seed Generate seed for the random number.
	 */
	RandomNumber(const int low, const int high, const uint seed = 0);


    /**
     * @return A random number.
     */
    int generate();


    /**
     * @param low Low number.
     * @param high High number.
     * @return A random number.
     */
    int generate(const int low, const int high);


    /**
     * Set random range.
     * @param low Lower range.
     * @param high High range.
     */
    void setRange(const int low, const int high);


    /**
     * Set seed.
     * @param seed Seed for the random number.
     */
    void setSeed(const uint seed);


protected:
    /**
     * Low number.
     */
    int mLow;


    /**
     * High number.
     */
    int mHigh;


}; // End class RandomNumber


} // End namespace ndx


#endif // __RandomNumber_h__
