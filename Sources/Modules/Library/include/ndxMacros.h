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


#ifndef ndxMacros_h
#define ndxMacros_h


// ************************************************************
// Cleaning pointers
// ************************************************************
#ifndef SAFE_CLEAN_POINTER
    #define SAFE_CLEAN_POINTER(Var) \
        {                           \
            if(Var != nullptr) {    \
                delete Var;         \
                Var = nullptr;      \
            }                       \
        }
#endif


#endif  // ndxMacros_h
