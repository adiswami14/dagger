#pragma once

#include "core/graph.h"

#include "core/fileexplorer.h"
#include <core/textparser.h>
#include "core/utils.h"
#include <string>
#include <vector>
#include <set>

using std::string;
using std::vector;

// Generates the graph with the help of FileExplorer and TextParser
class GraphGenerator {
    public:

        // Recursively generates graph with help of FileExplorer and TextParser
        // 1. Receives root folder, as well as the file to start at (typically will be the main file) 
        // 2. Sets up file_explorer_ so that we can get paths easily
        // 3. Call recursive helper function GenerateNode which will use a DFS to generate the graph
        void GenerateGraph(const string& root_folder, const string& file);
        
        // For testing that the graph was generated correctly
        void PrintGraph();
        
        Graph GetGraph();
    
    private:

        // Recursive helper function, will first get called on the root file
        // Then will recursively generate the graph
        // This function will get called in GenerateGraph (first called at step 3 in GenerateGraph documentation)
        void GenerateNode(const string& file_name);

        Graph graph_; // Graph to be generated
        FileExplorer file_explorer_; // Used to get full paths based on file names so that we can send those in to the TextParser
        TextParser parser_; // Parses a file and gives back a list of files that were included
        set<string> visited_; // All visited nodes - used for cycle detection
};