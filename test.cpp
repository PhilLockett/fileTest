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
    REQUIRE(output.write(test) == 0)

    TextFile<> input{fileName};
    REQUIRE(input.read() == 0)

    REQUIRE(input.equal(output))
    REQUIRE(output.equal(input))

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
    REQUIRE(output.write(test) == 0)

    TextFile<wchar_t> input{fileName};
    REQUIRE(input.read() == 0)

    REQUIRE(input.equal(output))
    REQUIRE(output.equal(input))

END_TEST

UNIT_TEST(test3, "Test standard binary generation for 'testStdBinary.dat'.")

    std::string fileName{rootDir + "/testStdBinary.dat"};
    std::vector<char> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<> output{fileName};
    REQUIRE(output.write(test) == 0)

    BinaryFile<> input{fileName};
    REQUIRE(input.read() == 0)

    REQUIRE(input.equal(output))
    REQUIRE(output.equal(input))

END_TEST

UNIT_TEST(test4, "Test wide binary generation for 'testWideBinary.dat'.")

    std::string fileName{rootDir + "/testWideBinary.dat"};
    std::vector<wchar_t> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<wchar_t> output{fileName};
    REQUIRE(output.write(test) == 0)

    BinaryFile<wchar_t> input{fileName};
    REQUIRE(input.read() == 0)

    REQUIRE(input.equal(output))
    REQUIRE(output.equal(input))

END_TEST

UNIT_TEST(test5, "Test limited compare of standard strings'.")

    std::string fileName{rootDir + "/testStdString.txt"};
    std::vector<std::string> test{ 
        "Standard Line 0",
        "Standard Line 1",
        "Standard Line 2",
        "Standard Line 3",
        "Standard Line 4"
    };

    TextFile<> output{fileName};
    output.setData(test);

    std::filesystem::path dummyFile{rootDir + "/dummy.txt"};
    std::vector<std::string> testSome{ 
        "Standard Line 0",
        "Standard Line 1",
        "Standard Line 2"
    };
    TextFile<> compare{dummyFile};
    compare.setData(testSome);
    REQUIRE(output.equal(compare, compare.size()))

END_TEST

UNIT_TEST(test6, "Test limited compare of standard binary.")

    std::string fileName{rootDir + "/testStdBinary.dat"};
    std::vector<char> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<> output{fileName};
    output.setData(test);

    std::filesystem::path dummyFile{rootDir + "/dummy.txt"};
    std::vector<char> testSome{ 1, 2, 3, 4, 5 };
    BinaryFile<> compare{dummyFile};
    compare.setData(testSome);
    REQUIRE(output.equal(compare, compare.size()))

END_TEST

UNIT_TEST(test7, "Test modifying standard string for 'testModifyString.txt'.")

    // Set up.
    std::string fileName{rootDir + "/testModifyString.txt"};
    std::vector<std::string> test{ 
        "Standard Line 0",
        "Standard Line 1",
        "Standard Line 2",
        "Standard Line 3",
        "Standard Line 4"
    };

    TextFile<> output{fileName};
    REQUIRE(output.write(test) == 0)

    // Test changing data.
    TextFile<> input{fileName};
    REQUIRE(input.read() == 0)
    auto data = input.getData();
    data[2] = "Replacement line";
    data.emplace_back("Appended line");

    input.setData(data);
    REQUIRE(input.write() == 0)

    // Check changed data.
    TextFile<> compare{fileName};
    REQUIRE(compare.read() == 0)

    REQUIRE(input.equal(compare))
    REQUIRE(compare.equal(input))

    std::vector<std::string> compareTest{ 
        "Standard Line 0",
        "Standard Line 1",
        "Replacement line",
        "Standard Line 3",
        "Standard Line 4",
        "Appended line"
    };
    auto compareData = compare.getData();
    REQUIRE(compareTest.size() == compareData.size())
    REQUIRE(std::equal(compareTest.begin(), compareTest.end(), compareData.begin()) == true)

END_TEST

UNIT_TEST(test8, "Test modifying standard binary for 'testModifyBinary.dat'.")

    // Set up.
    std::string fileName{rootDir + "/testModifyBinary.dat"};
    std::vector<char> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<> output{fileName};
    REQUIRE(output.write(test) == 0)

    // Test changing data.
    BinaryFile<> input{fileName};
    REQUIRE(input.read() == 0)
    auto data = input.getData();
    data[2] = 13;
    data.emplace_back(42);

    input.setData(data);
    REQUIRE(input.write() == 0)

    // Check changed data.
    BinaryFile<> compare{fileName};
    REQUIRE(compare.read() == 0)

    REQUIRE(input.equal(compare))
    REQUIRE(compare.equal(input))

    std::vector<char> compareTest{ 1, 2, 13, 4, 5, 6, 7, 8, 9, 10, 11, 12, 42 }; 
    auto compareData = compare.getData();
    REQUIRE(compareTest.size() == compareData.size())
    REQUIRE(std::equal(compareTest.begin(), compareTest.end(), compareData.begin()) == true)

END_TEST

std::vector<std::string> testMoveString(const std::string & fileName)
{
    TextFile<> input{fileName};
    REQUIRE(input.read() == 0)

    return input.moveData();
}
UNIT_TEST(test9, "Test moving standard string for 'testMoveString.txt'.")

    // Set up.
    std::string fileName{rootDir + "/testMoveString.txt"};
    std::vector<std::string> test{ 
        "Standard Line 0",
        "Standard Line 1",
        "Standard Line 2",
        "Standard Line 3",
        "Standard Line 4"
    };

    TextFile<> output{fileName};
    REQUIRE(output.write(test) == 0)

    // Test moving data out.
    auto data = testMoveString(fileName);
    REQUIRE(test.size() == data.size())
    REQUIRE(std::equal(test.begin(), test.end(), data.begin()) == true)

    // Test moving data in.
    TextFile<> compare{fileName};
    compare.moveData(std::move(data));
    REQUIRE(data.size() == 0)
    REQUIRE(output.equal(compare))

END_TEST

std::vector<char> testMoveBinary(const std::string & fileName)
{
    BinaryFile<> input{fileName};
    REQUIRE(input.read() == 0)

    return input.moveData();
}
UNIT_TEST(test10, "Test moving standard binary for 'testMoveBinary.dat'.")

    // Set up.
    std::string fileName{rootDir + "/testMoveBinary.dat"};
    std::vector<char> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    BinaryFile<> output{fileName};
    REQUIRE(output.write(test) == 0)

    // Test moving data out.
    auto data = testMoveBinary(fileName);
    REQUIRE(test.size() == data.size())
    REQUIRE(std::equal(test.begin(), test.end(), data.begin()) == true)

    // Test moving data in.
    BinaryFile<> compare{fileName};
    compare.moveData(std::move(data));
    REQUIRE(data.size() == 0)
    REQUIRE(output.equal(compare))

END_TEST


int runTests()
{
    std::cout << "\nExecuting all tests.\n";

    RUN_TEST(test1)
    RUN_TEST(test2)
    RUN_TEST(test3)
    RUN_TEST(test4)
    RUN_TEST(test5)
    RUN_TEST(test6)
    RUN_TEST(test7)
    RUN_TEST(test8)
    RUN_TEST(test9)
    RUN_TEST(test10)

    const int err{FINISHED};
    OUTPUT_SUMMARY;

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

