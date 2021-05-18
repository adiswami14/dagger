#include <iostream>
#include "core/graph_generator.h"
#include "core/cycle_detector.h"

int main(){
    
    GraphGenerator graph_gen;
    graph_gen.GenerateGraph("../example_projs/final-project-RavyuS", "main.cc");
    
    Graph gr = graph_gen.GetGraph();
    
    
    std::cout << "DFS DEMO...." << std::endl;
    vector<Graph::Node> dfs_tree = gr.DFS();
    
    for (Graph::Node& node : dfs_tree) { // Prints out each node that the dfs went through
        std::cout << node.name_ << std::endl;
    }

    CycleDetector cycle_detector(gr);

    // cycle detection needs to happen before renderGraph
    std::vector<std::set<Graph::Node>>  cycle = cycle_detector.FindCycle();

//    std::cout<<"\nPRINTING CYCLE NODES....."<<std::endl;
//    std::set<pair<Graph::Node, Graph::Node>> cycle_edges;
//    size_t cycle_count = 1;
//    for(const auto& it: cycle) {
//        std::cout<<"Cycle " << cycle_count << ": ";
//        for(const auto& it2 : it) {
//            std::cout<<it2.name_ << " ";
//        }
//        std::cout<<std::endl;
//        cycle_edges.insert({*(--(it.end())), *(it.begin())});
//        cycle_count++;
//    }

//    gr.SetCycleEdges(cycle_edges);
//    std::cout<<"\nPRINTING CYCLE EDGES..."<<std::endl;
    std::FILE* fpointer = fopen("graph.dot", "w");
//    for(const auto& it: cycle_edges) {
//        std::cout<<"EDGE FROM " << it.first.name_ << " TO " << it.second.name_ <<std::endl;
//    }

    gr.RenderGraph(fpointer);
    return 0;
}
