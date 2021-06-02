# fileTest
Test code for checking TextFile and BinaryFile templates.

## Overview
A sequence of regression tests for checking TextFile and BinaryFile templates.

## TextFile and BinaryFile
TextFile and BinaryFile are template classes that provide light weight file
handling capabilities. They capture the entire file contents as vectors, so 
may not be appropriate for large files.

For TextFile the data is contained in a `std::vector<std::basic_string<CharT>>`
where each string represents a line of text and may contain whitespace. For 
BinaryFile the data is contained in a `std::vector<CharT>`. Note, although this
code compiles with a CharT other than char (e.g. wchar_t), on the systems
I've tested on it behaves as a single byte char type.

Only a limited interface is provided for iterating over the data or comparing
data between two instances. If data manipulation is required setDate() and
getData() methods are provided which copy the data. Alternatively, data can be
moved in and out of the instance using moveData(). Once the data is obtained
the data is a vector and can be modified as such.

## Cloning and Running
The test code is dependent on UnitTest. To compile and run the tfcTest code you
first need to clone the unit test code, then copy unittest.cpp and unittest.h 
into the tfcTest directory before executing make.

    git clone https://github.com/PhilLockett/UnitTest.git

To clone, build and run this code, execute the following unix/linux commands:

    git clone https://github.com/PhilLockett/fileTest.git
    cd fileTest/
    cp ../UnitTest/unittest.cpp .
    cp ../UnitTest/unittest.h .
    make
    ./test

## Points of interest
This code has the following points of interest:

  * The unit test code completely regenerates the required test files.
  * A light weight file reader and writer.
  * Easy comparison of file content between two files.
