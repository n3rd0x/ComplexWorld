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


#ifndef _ndxPrerequisites_h_
#define _ndxPrerequisites_h_


// clang-format off
// ************************************************************
// Plugin Export Declarations
// ************************************************************
#if _WIN32
    // If we're not including this from a client build, specify that the stuff
    // should get exported. Otherwise, import it.
    #if defined(NDXLIB_STATIC_LIB)
        #define _ndxLibExport
    #else
        #if defined(NDXLIB_NONCLIENT_BUILD)
            #define _ndxLibExport __declspec(dllexport)
        #else
            #define _ndxLibExport __declspec(dllimport)
        #endif
    #endif
#else
    // Linux compilers don't have symbol import/export directives.
    #define _ndxLibExport
#endif




// ************************************************************
// Debug Mode Declarations
// ************************************************************
#if _WIN32
    #if defined(_DEBUG) || defined(DEBUG)
        #define NDX_DEBUG_MODE 1
    #else
        #define NDX_DEBUG_MODE 0
    #endif
// Assume Unix.
#else
    #ifndef NDEBUG
        // Since on Linux, this is not defined. So for consistent
        // we also define this.
        #define _DEBUG 1
        #define NDX_DEBUG_MODE 1
    #else
        #define NDX_DEBUG_MODE 0
    #endif
#endif




// ************************************************************
// Class Forward Declarations
// ************************************************************
namespace ndx {
    class LogManager;
    class NumberGenerator;

    template<typename T> class Singleton;
}
// clang-format on


#endif  // _ndxPrerequisites_h_

