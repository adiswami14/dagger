#include "core/graph_generator.h"

void GraphGenerator::GenerateGraph(const string& root_folder, const string& file) {
    file_explorer_.ReadAllFiles(root_folder);
    graph_.SetRoot(file);
    GenerateNode(file);
}

void GraphGenerator::GenerateNode(const string& file_name) {
    if (file_name == "") {
        return;
    }

    string path = file_explorer_.GetAbsPathFromRelative(file_name);
    // insert path into set for cycle detection (otherwise will get infinite recursion)
    visited_.insert(path);

    if (path == "") {
        return;
    }

    vector<string> results = parser_.ParseText(path);
    Graph::Node sub_root = Graph::Node();
    sub_root.name_ = utils::getFileName(path);
    graph_.AddNode(sub_root.name_);

    for (const string& file : results) {
        
        // Note: Still haven't accounted for files that 
        //       have the same name but are in different directories 
        //       (could happen in larger repos)
        string path2 = file_explorer_.GetAbsPathFromRelative(file);
        Graph::Node child = Graph::Node();

        child.name_ = utils::getFileName(path2);
  
        if (path2 != "") {
            graph_.AddEdge(sub_root, child);
        }
        
        if (visited_.find(path2) == visited_.end()) { // Only recurse if it is a unseen node
            GenerateNode(path2); // Recurse down 
        }
    }
}

Graph GraphGenerator::GetGraph() {
    return graph_;
}
