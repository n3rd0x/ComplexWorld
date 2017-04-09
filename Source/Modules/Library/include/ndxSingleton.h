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


#ifndef _ndxSingleton_h_
#define _ndxSingleton_h_


// STL includes
#include <cassert>


namespace ndx {


/**
 * A generic singleton.
 */
template <typename T>
class Singleton {
public:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default constructor.
     */
    Singleton() {
        mSingleton = static_cast<T*>(this);
    }


    /**
     * Default destructor.
     */
    virtual ~Singleton() {
        mSingleton = nullptr;
    }




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * @return Template singleton instance.
     */
    static T* getSingleton() {
        assert((mSingleton != nullptr) && "Instance hasn't been created.");
        return mSingleton;
    }




protected:
    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * Template single instance.
     */
    static T* mSingleton;




private:
    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Forbid copy constructor.
     */
    Singleton(const Singleton<T>&);


    /**
     * Forbid assignment operator.
     */
    Singleton& operator=(const Singleton<T>&);




};  // End class Singleton


}  // End namespace ndx


#endif  // _ndxSingleton_h_
