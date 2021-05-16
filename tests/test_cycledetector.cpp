#include <cstdlib>
#include <vector>
#include <catch2/catch.hpp>
#include <core/cycle_detector.h>
#include <core/graph_generator.h>

TEST_CASE("FindCycle basic", "[c]") {
    //Setup simple graph with 2 nodes
    Graph graph("root");
    Graph::Node root("root");
    Graph::Node node0("node0");
    graph.AddNode(root.name_);
    graph.AddNode(node0.name_);

    graph.AddEdge(root, node0);
    graph.AddEdge(node0,root);

    CycleDetector cd(graph);

    std::vector<std::set<Graph::Node>> cycles = cd.FindCycle();
    REQUIRE(cycles.size() == 1);
    
    std::vector<std::string> node_names;
    for(const auto& it:cycles[0]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 2);
    std::vector<std::string> expected{"node0","root"};
    REQUIRE(node_names == expected);
}

TEST_CASE("FindCycle 3 nodes", "[c]") {
    //Setup simple graph with 3 nodes
    Graph graph("root");
    Graph::Node root("root");
    Graph::Node node0("node0");
    Graph::Node node1("node1");
    graph.AddNode(root.name_);
    graph.AddNode(node0.name_);
    graph.AddNode(node1.name_);

    graph.AddEdge(root, node0);
    graph.AddEdge(node0, node1);
    graph.AddEdge(node1, root);

    CycleDetector cd(graph);

    std::vector<std::set<Graph::Node>> cycles = cd.FindCycle();
    REQUIRE(cycles.size() == 1);
    
    std::vector<std::string> node_names;
    for(const auto& it:cycles[0]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 3);
    std::vector<std::string> expected{"node0","node1","root"};
    REQUIRE(node_names == expected);
}

TEST_CASE("FindCycle 2 cycles", "[c]") {
    //Setup simple graph with 3 nodes
    Graph graph("root");

    //First cycle
    Graph::Node root("root");
    Graph::Node node0("node0");
    Graph::Node node1("node1");
    graph.AddNode(root.name_);
    graph.AddNode(node0.name_);
    graph.AddNode(node1.name_);

    graph.AddEdge(root, node0);
    graph.AddEdge(node0, node1);
    graph.AddEdge(node1, root);

    //Second cycle
    Graph::Node node2("node2");
    Graph::Node node3("node3");
    graph.AddNode(node2.name_);
    graph.AddNode(node3.name_);

    graph.AddEdge(root, node2);
    graph.AddEdge(node2, node3);
    graph.AddEdge(node3, node2);


    CycleDetector cd(graph);

    std::vector<std::set<Graph::Node>> cycles = cd.FindCycle();
    REQUIRE(cycles.size() == 2);
    
    std::vector<std::string> node_names;
    
    for(const auto& it:cycles[0]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 3);
    std::vector<std::string> expected1{"node0","node1","root"};
    REQUIRE(node_names == expected1);

    node_names.clear();
    for(const auto& it:cycles[1]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 2);
    std::vector<std::string> expected2{"node2","node3"};
    REQUIRE(node_names == expected2);
}

TEST_CASE("FindCycle in repo", "[c]") {
    GraphGenerator graph_gen;
    graph_gen.GenerateGraph("../tests/test-repo/cyclical-folder", "root.h");

    Graph graph = graph_gen.GetGraph();

    CycleDetector cd(graph);
    std::vector<std::set<Graph::Node>>  cycles = cd.FindCycle();

    REQUIRE(cycles.size() == 2);

    std::vector<std::string> node_names;
    
    for(const auto& it:cycles[0]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 4);
    std::vector<std::string> expected1{"first.h","root.h","second.cpp","third.cpp"};
    REQUIRE(node_names == expected1);

    node_names.clear();
    for(const auto& it:cycles[1]) {
        node_names.push_back(it.name_);
    }
    REQUIRE(node_names.size() == 2);
    std::vector<std::string> expected2{"fifth.cc","fourth.hpp"};
    REQUIRE(node_names == expected2);
}