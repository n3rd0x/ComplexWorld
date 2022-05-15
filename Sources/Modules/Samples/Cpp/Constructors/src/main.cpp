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


// STL includes
#include <iostream>


// ************************************************************
// Classes
// ************************************************************
class Constructor {
public:
    void delPtr() {
        if(ptr) {
            delete ptr;
        }
        ptr = nullptr;
    }

    void print(const std::string& prefix = "") {
        if(!prefix.empty()) {
            std::cout << "[" << prefix << "]: ";
        }

        if(ptr) {
            std::cout << "Ptr=" << ptr << "::" << *ptr << " ";
        }
        std::cout << "DNA=" << &dna << "::" << dna << " Number=" << &number << "::" << number;


        std::cout << std::endl;
        if(prefix.empty()) {
            std::cout << std::endl;
        }
    }


    int number{0};
    int* ptr{nullptr};
    std::string dna{""};
};


/**
 * @brief The compiler create constructors.
 */
class NoCopyNoMove : public Constructor {};


/**
 * @brief The compiler doesn't create any constructur when we have specified at lease one.
 */
class ManConstuctor {
public:
    ManConstuctor() : number(0), dna(""), ptr(nullptr) {
    }


    ~ManConstuctor() {
        if(ptr) {
            delete ptr;
        }
        ptr = nullptr;  // Unneccesary.
    }


    ManConstuctor(const ManConstuctor& cpy) : number(cpy.number), dna(cpy.dna), ptr(cpy.ptr) {
    }


    /**
     * @brief Move constructor prevent copy values to a new variable.
     */
    ManConstuctor(ManConstuctor&& cpy)
    : number(std::move(cpy.number)), dna(std::move(cpy.dna)), ptr(std::move(cpy.ptr)) {
        cpy.ptr = nullptr;
    }


    void print(const std::string& prefix = "") {
        if(!prefix.empty()) {
            std::cout << "[" << prefix << "]: ";
        }

        if(ptr) {
            std::cout << "Ptr=" << ptr << "::" << *ptr << " ";
        }
        std::cout << "DNA=" << &dna << "::" << dna << " Number=" << &number << "::" << number;


        std::cout << std::endl;
        if(prefix.empty()) {
            std::cout << std::endl;
        }
    }

    int number{0};
    int* ptr{nullptr};
    std::string dna{""};
};



// ************************************************************
// Main
// ************************************************************
int main(int argc, char** argv) {
    std::cout << "**********************" << std::endl;
    std::cout << "* C++ - Constructors *" << std::endl;
    std::cout << "**********************" << std::endl;
    {
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "No implementation of Copy or Move constructors:" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        NoCopyNoMove a;
        a.number = 20;
        a.ptr    = new int(14);
        a.dna    = "dna";


        std::cout << "Init a:" << std::endl;
        a.print("0a");
        std::cout << std::endl;

        NoCopyNoMove b(a);
        std::cout << "Copy of a (should have same values):" << std::endl;
        a.print("a ");
        b.print("b ");
        std::cout << std::endl;

        std::cout << "Modify a" << std::endl;
        a.number = 80;
        a.dna    = "mod";
        a.delPtr();
        a.print("a ");
        b.print("b ");


        std::cout << std::endl << std::endl;


        std::cout << "Move of a (before):" << std::endl;
        a.print("0a");
        std::cout << std::endl;

        std::cout << "Move of a (after):" << std::endl;
        NoCopyNoMove ma = std::move(a);
        a.print("1a");
        ma.print("ma");
        std::cout << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
    }


    std::cout << std::endl;
    {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Implementation of Move constructor:" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        ManConstuctor a;
        a.number = 10;
        a.dna    = "ibm";
        a.ptr    = new int(16);

        std::cout << "std::move of a (before):" << std::endl;
        a.print("0a");
        std::cout << std::endl;

        std::cout << "std::move of a (after):" << std::endl;

        ManConstuctor ma = std::move(a);
        a.print("1a");
        ma.print("ma");
        std::cout << std::endl;

        std::cout << "Move constructor of a (before):" << std::endl;
        a.number = 13;
        a.dna    = "sec";
        a.ptr    = new int(18);
        a.print("aa");
        std::cout << std::endl;

        std::cout << "Move constructor of a (after):" << std::endl;

        ManConstuctor mb(std::move(a));
        a.print("1a");
        mb.print("mb");
        std::cout << std::endl;

        std::cout << "-----------------------------------" << std::endl;
    }


    std::cout << "Successfully terminated." << std::endl;
    return 0;
}
