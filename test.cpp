/**
 * @file    test.cpp
 * @author  Phil Lockett <phillockett65@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Unit test code for the 'tfc' utility.
 *
 * Build using:
 *    g++ -std=c++20 -c -o test.o test.cpp
 *    g++ -std=c++20 -c -o gen.o gen.cpp
 *    g++ -std=c++20 -c -o unittest.o unittest.cpp
 *    g++ -std=c++20 -o test test.o gen.o unittest.o
 *
 * Test using:
 *    ./test
 *
 */

#include <iostream>
#include <vector>

#include "TextFile.h"
#include "BinaryFile.h"

#include "unittest.h"

/**
 * @section basic utility code.
 */

const std::string rootDir{"testdata"};

static bool createDirectory(const std::string & path)
{
    return std::filesystem::create_directories(path);
}

static void deleteDirectory(const std::string & path)
{
    std::filesystem::remove_all(path); // Delete directory and contents.
}


/**
 * @section tests.
 *
 */

UNIT_TEST(test1, "Test standard string generation for 'testStdString.txt'.")

    std::string fileName{rootDir + "/testStdString.txt"};
    std::vector<std::string> test{ 
        "Standard Line 0",
        "Standard Line 1",
        "Standard Line 2",
        "Standard Line 3",
        "Standard Line 4"
    };

    TextFile<> output{fileName};
    output.write(test);

    TextFile<> expected{fileName};
    expected.read();

    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2, "Test wide string generation for 'testWideString.txt'.")

    std::string fileName{rootDir + "/testWideString.txt"};
    std::vector<std::wstring> test{ 
        L"Wide Line 0",
        L"Wide Line 1",
        L"Wide Line 2",
        L"Wide Line 3",
        L"Wide Line 4"
    };

    TextFile<wchar_t> output{fileName};
    output.write(test);

    TextFile<wchar_t> expected{fileName};
    expected.read();

    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3, "Test standard binary generation for 'testStdBinary.txt'.")

    std::string fileName{rootDir + "/testStdBinary.txt"};
    std::vector<char> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<> output{fileName};
    output.write(test);

    BinaryFile<> expected{fileName};
    expected.read();

    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4, "Test wide string generation for 'testWideBinary.txt'.")

    std::string fileName{rootDir + "/testWideBinary.txt"};
    std::vector<wchar_t> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<wchar_t> output{fileName};
    output.write(test);

    BinaryFile<wchar_t> expected{fileName};
    expected.read();

    REQUIRE(expected.equal(output))

END_TEST


int runTests()
{
    std::cout << "\nExecuting all tests.\n";

    RUN_TEST(test1)
    RUN_TEST(test2)
    RUN_TEST(test3)
    RUN_TEST(test4)

    const int err = FINISHED;
    if (err)
        std::cerr << err << "\n\nERROR(S) encountered!.\n";
    else
    {
        std::cout << "\nAll tests passed.\n";
    }

    return err;
}


/**
 * Test system entry point.
 *
 * @param  argc - command line argument count.
 * @param  argv - command line argument vector.
 * @return error value or 0 if no errors.
 */
int main(int argc, char *argv[])
{
    deleteDirectory(rootDir);
    createDirectory(rootDir);

    return runTests();
}

