#pragma once
#include "dirent.h"
    
// May not need all of these just including for now
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
class TextParser{
    public:
        TextParser();

        // Returns a list of the filenames that the given file includes
        // Note: the returned filenames will be anything within the quotes or brackets 
        // (so it could be a relative path or just a file_name).
        vector<string> ParseText(const std::string& fp);
        friend std::istream& operator >> (std::istream& in, TextParser& parser);
    
    private:
        vector<string> include_paths_; // Contains all paths next to include statements
};