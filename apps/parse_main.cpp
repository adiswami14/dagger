#include <vector>
#include <string>
#include <iostream>
// #include "core/textparser.h"
#include "core/fileexplorer.h"

using std::vector;
using std::string;

int main(int argc, char* argv[]) {
    TextParser parser;

    string path = "../";  //works for the current directory setup
    if(argc == 1) path.append("data/test_parser.txt");
    else path.append(std::string(argv[1]));
    
    std::cout << "------------------------------------------------------\n" << std::endl;
    std::cout << "Reading file structure..... \n\n" << std::endl;
    FileExplorer fe;
    fe.ReadAllFiles("../example_projs/final-project-RavyuS");
    std::cout << fe << std::endl;
    std::cout << "------------------------------------------------------\n" << std::endl;

    std::cout << "Parsing \"inventory_manager\"..... \n\n" << std::endl;

    string path2 = fe.GetPathToFile("actions.h");
    
    std::cout << "PATH: " << path2 << "\n" << std::endl;
    std::cout << "INCLUDE FILES: " << std::endl;
    vector<string> returnvec2 = parser.ParseText(path2);
    
    for (const auto& str : returnvec2) {
        std::cout << str << std::endl;
    }

    string path3 = fe.GetAbsPathFromRelative("core/game_engine/actions/move_to.h");
    std::cout << path3 << std::endl;
    vector<string> returnvec3 = parser.ParseText(path3);
    
    for (const auto& str : returnvec3) {
        std::cout << str << std::endl;
    }

    return 0;
}

