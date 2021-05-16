#include <cstdlib>
#include <vector>
#include <catch2/catch.hpp>
#include <core/fileexplorer.h>

using std::set;
using File = FileExplorer::File;

TEST_CASE("ReadAllFiles", "[f]") {
    FileExplorer file_exp;
    SECTION("Testing normal src directory") {
        //Read from test repo
        file_exp.ReadAllFiles("../tests/test-repo/src");
        set<File> files = file_exp.GetFileDirectories();

        //Expected soln
        File source_file("source_file.cpp", "../tests/test-repo/src/source_file.cpp");
        File header("header.h", "../tests/test-repo/src/header.h");
        File random_cc_file("random_cc_file.cc", "../tests/test-repo/src/random_cc_file.cc");
        File header_pp("header_pp.hpp", "../tests/test-repo/src/header_pp.hpp");
        File another_header("another_header.h", "../tests/test-repo/src/another_header.h");
        set<File> expected_file_system = {source_file, header, random_cc_file, header_pp, another_header};

        REQUIRE(files.size() == expected_file_system.size());
        for(File f : expected_file_system) {
            REQUIRE(files.find(f) != files.end());
        }
    }
    SECTION("Testing extraneous files directory") {
        file_exp.clear();
        file_exp.ReadAllFiles("../tests/test-repo/extraneous-files");
        File regular("regular.cpp", "../tests/test-repo/extraneous-files/regular.cpp");
        set<File> expected_file_system = {regular};
        set<File> files = file_exp.GetFileDirectories();
        REQUIRE(files.size() == expected_file_system.size());
        for(File f : files) {
            REQUIRE(expected_file_system.find(f) != expected_file_system.end());
        }
    }
    SECTION("Testing naming collisions directory") {
        
    }
}

TEST_CASE("GetPathToFiles", "[f]") {
    FileExplorer file_exp;

    //Read from test repo
    file_exp.ReadAllFiles("../tests/test-repo");
   
    SECTION("Test files within test-repo") {
        REQUIRE(file_exp.GetPathToFile("source_file.cpp") == "../tests/test-repo/src/source_file.cpp");
        REQUIRE(file_exp.GetPathToFile("header.h") == "../tests/test-repo/src/header.h");
        REQUIRE(file_exp.GetPathToFile("random_cc_file.cc") == "../tests/test-repo/src/random_cc_file.cc");
        REQUIRE(file_exp.GetPathToFile("header_pp.hpp") == "../tests/test-repo/src/header_pp.hpp");
    }
    SECTION("Test files not in test-repo (should return empty string") {
        REQUIRE(file_exp.GetPathToFile("this_file_does_not_exist.cpp") == "");
        REQUIRE(file_exp.GetPathToFile("neither_does_this.h") == "");
        REQUIRE(file_exp.GetPathToFile("blah.hpp") == "");
        REQUIRE(file_exp.GetPathToFile("blah_2.cc") == "");
    }
}

TEST_CASE("GetFileExt", "[f]") {
    FileExplorer file_exp;

    //Read from test repo
    file_exp.ReadAllFiles("../tests/test-repo");
   
    REQUIRE(file_exp.GetFileExt("main.cpp") == "cpp");
    REQUIRE(file_exp.GetFileExt("header.h") == "h");
    REQUIRE(file_exp.GetFileExt("random.hpp") == "hpp");
    REQUIRE(file_exp.GetFileExt("file.cc") == "cc");
    REQUIRE(file_exp.GetFileExt("text_file.txt") == "txt");
    REQUIRE(file_exp.GetFileExt("java_file.java") == "java");
}

TEST_CASE("PrintFileSys", "[f]") {
    FileExplorer file_exp;
    std::stringstream s;

    //Read from test repo (single file)
    file_exp.ReadAllFiles("../tests/test-repo/single_file");
    s << file_exp;

    std::string expected = "DIR PATH:     ../tests/test-repo/single_file/just_one.cpp\nNAME:     just_one.cpp\n";

    REQUIRE(s.str() == expected);
}
