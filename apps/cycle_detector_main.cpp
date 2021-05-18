#include <iostream>
#include "core/graph_generator.h"
#include "core/cycle_detector.h"

int main() {
    Graph g("root");
    Graph::Node root("root");
    Graph::Node root2("root2");
    Graph::Node root_child("child1");
    Graph::Node node0("node0");
    Graph::Node node1("node1");
    Graph::Node node2("node2");
    Graph::Node node3("node3");
    Graph::Node node4("node4");
    Graph::Node node5("node5");
    Graph::Node node6("node6");
    g.AddNode(root.name_);
    g.AddNode(root2.name_);
    g.AddNode(root_child.name_);
    g.AddNode(node0.name_);
    g.AddNode(node1.name_);
    g.AddNode(node2.name_);
    g.AddNode(node3.name_);
    g.AddNode(node4.name_);
    g.AddNode(node5.name_);
    g.AddNode(node6.name_);

    // g.AddEdge(node1, node3);
    // g.AddEdge(node1, node2);
    // g.AddEdge(node2, node3);
    // g.AddEdge(node3, node2);
    // g.AddEdge(node3, node4);
    // g.AddEdge(node4, node5);
    // g.AddEdge(node5, node6);
    // g.AddEdge(node6, node4);

    g.AddEdge(root, node0);
    g.AddEdge(root, root_child);
    g.AddEdge(root_child, node1);
    g.AddEdge(node0, node1);
    g.AddEdge(node1, node2);
    g.AddEdge(node2, node4);
    g.AddEdge(node4, node6);
    g.AddEdge(node1, node3);
    g.AddEdge(node3, node5);
    g.AddEdge(node5, node6);
    g.AddEdge(node6, root_child);
    g.AddEdge(node6, node1);
    g.AddEdge(root, root2);
    g.AddEdge(root2, root);

    CycleDetector cycle_detector(g);

    // cycle detection needs to happen before renderGraph
//    std::vector<std::set<Graph::Node>>  cycle = cycle_detector.FindCycle();
//
//    std::cout<<"PRINTING CYCLE NODES....."<<std::endl;
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
//
//    g.SetCycleEdges(cycle_edges);
    std::FILE* fpointer = fopen("newcycle.dot", "w");
    std::cout<<"\nPRINTING CYCLE EDGES..."<<std::endl;
//    for(const auto& it: cycle_edges) {
//        std::cout<<"EDGE FROM " << it.first.name_ << " TO " << it.second.name_ <<std::endl;
//    }

    g.RenderGraph(fpointer);

    return 0;
}