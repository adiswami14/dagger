#include <cstdlib>
#include <catch2/catch.hpp>
#include <core/textparser.h>
#include <vector>

// These tests cover that the textparser can deal with spaces in between the #include and name,
// quotes, brackets, and include statements in the middle of the file and files with different extensions

TEST_CASE("TextParser with simple file with .cpp file", "[t]") {
    // Just a regular file with good formatting
    TextParser parser;
    std::vector<std::string> output = parser.ParseText("../tests/test-repo/src/source_file.cpp");
    std::vector<std::string> expected = {"header.h", "naming-collisions/cool.h", "naming-collisions/cool.hpp"};
    REQUIRE(output == expected);
}

TEST_CASE("TextParser with difficult formatting with .cc file", "[t]") {
    TextParser parser;
    std::vector<std::string> output = parser.ParseText("../tests/test-repo/src/random_cc_file.cc");
    std::vector<std::string> expected = {"string", "blank/hello/actions.h", "game_state.h", "game_state.h", "test.cc", "test3.cpp"};
    REQUIRE(output == expected);
}

TEST_CASE("TextParser with .h file", "[t]") {
    TextParser parser;
    std::vector<std::string> output = parser.ParseText("../tests/test-repo/src/another_header.h");
    std::vector<std::string> expected = {"header.h","header_pp.hpp"};
    REQUIRE(output == expected);
}

