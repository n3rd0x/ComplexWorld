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
/**
 * @brief The compiler should auto generate copy, move, assign and destructor.
 */
class DefaultConstructor {
public:
    DefaultConstructor(const std::string& val = "DefaultConstructor") : val(val) {
    }


    void print(const std::string& tag) {
        std::cout << tag << ": " << val << std::endl;
    }


    std::string val;
};


/**
 * @brief Same as DefaultConstructor.
 */
class DerivedConstructor : public DefaultConstructor {};


/**
 * @brief Automatic generated of move constructor.
 */
class CopyConstructor : public DefaultConstructor {
public:
    CopyConstructor(const std::string& val = "CopyConstructor") : DefaultConstructor(val) {
    }


    CopyConstructor(const CopyConstructor& cpy) {
        val = cpy.val;
    }
};


/**
 * @brief No automatic generated of copy constructor.
 */
class MoveConstructor : public DefaultConstructor {
public:
    MoveConstructor(const std::string& val = "MoveConstructor") : DefaultConstructor(val) {
    }


    MoveConstructor(MoveConstructor&& mv) {
        val = mv.val;
    }
};


/**
 * @brief Automatic generated of default, copy, move or assign constructor.
 */
class Destructor : public DefaultConstructor {
public:
    ~Destructor() {
    }
};



// ************************************************************
// Main
// ************************************************************
int main(int argc, char** argv) {
    std::cout << "********************************" << std::endl;
    std::cout << "* C++ - Generated Constructors *" << std::endl;
    std::cout << "********************************" << std::endl;
    DefaultConstructor objA("DC");  // ok


    DefaultConstructor objB(objA);  // ok, copy
    std::cout << "Copy:" << std::endl;
    objA.print(" objA");
    objB.print(" objB");


    DefaultConstructor objC = objB;  // ok, copy
    std::cout << std::endl;
    std::cout << "Copy:" << std::endl;
    objB.print(" objB");
    objC.print(" objC");


    DefaultConstructor objD = std::move(objA);  // ok, move
    std::cout << std::endl;
    std::cout << "Move:" << std::endl;
    objA.print(" objA");
    objD.print(" objD");


    DefaultConstructor objE(std::move(objC));  // ok, move
    std::cout << std::endl;
    std::cout << "Move:" << std::endl;
    objC.print(" objC");
    objE.print(" objE");


    auto objF = new DefaultConstructor();
    delete objF;  // ok


    DerivedConstructor dobjA;                     // ok
    DerivedConstructor dobjB(dobjA);              // ok
    DerivedConstructor dobjC = dobjB;             // ok
    DerivedConstructor dobjD = std::move(dobjB);  // ok
    DerivedConstructor dobjE(std::move(dobjC));   // ok
    auto dobjF = new DerivedConstructor();
    delete dobjF;  // ok


    CopyConstructor cobjA;                     // ok
    CopyConstructor cobjB(cobjA);              // ok
    CopyConstructor cobjC = cobjB;             // ok
    CopyConstructor cobjD = std::move(cobjB);  // ok
    CopyConstructor cobjE(std::move(cobjC));   // ok
    auto cobjF = new CopyConstructor();
    delete cobjF;  // ok


    MoveConstructor mobjA;  // ok
    // MoveConstructor mobjB(mobjA);              // fails
    // MoveConstructor mobjC = dobjB;             // fails
    // MoveConstructor mobjD = std::move(dobjB);  // fails
    // MoveConstructor mobjE(std::move(dobjC));   // fails
    auto mobjF = new MoveConstructor();
    delete dobjF;  // ok


    Destructor xobjA;                     // ok
    Destructor xobjB(xobjA);              // ok
    Destructor xobjC = xobjB;             // ok
    Destructor xobjD = std::move(xobjB);  // ok
    Destructor xobjE(std::move(xobjC));   // ok
    auto xobjF = new Destructor();
    delete dobjF;  // ok


    std::cout << "Successfully terminated." << std::endl;
    return 0;
}
