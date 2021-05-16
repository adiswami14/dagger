#include <cstdlib>
#include <catch2/catch.hpp>
#include <core/graph_generator.h>
#include <core/graph.h>
#include <vector>

//TEST GRAPHGEN
TEST_CASE("GenerateGraph tests (FindAdjecents)", "[g]") {
    GraphGenerator graph_gen;
    graph_gen.GenerateGraph("../tests/test-repo/src","another_header.h");

    Graph graph = graph_gen.GetGraph();

    std::vector<Graph::Node> adjacents = graph.FindAdjacents("another_header.h");
    REQUIRE(adjacents.size() == 2);
    
    Graph::Node node1("header.h");
    Graph::Node node2("header_pp.hpp");

    std::vector<Graph::Node> expected{node1,node2};
    REQUIRE(adjacents == expected);
}

TEST_CASE("GenerateGraph tests (GetGraphMap + FindAdjacents)", "[g]") {
    GraphGenerator graph_gen;
    graph_gen.GenerateGraph("../tests/test-repo/cyclical-folder","root.h");

    Graph graph = graph_gen.GetGraph();
    std::unordered_map<Graph::Node, std::vector<Graph::Node>, Graph::Hasher> graph_map = graph.GetGraphMap();

    REQUIRE(graph_map.size() == 6);
    
    std::vector<Graph::Node> adjacents1 = graph.FindAdjacents("root.h");
    Graph::Node node1("third.cpp");

    std::vector<Graph::Node> expected1{node1};
    REQUIRE(adjacents1 == expected1);

    std::vector<Graph::Node> adjacents2 = graph.FindAdjacents("second.cpp");
    Graph::Node node2("first.h");
    Graph::Node node3("fourth.hpp");

    std::vector<Graph::Node> expected2{node2,node3};
    REQUIRE(adjacents2 == expected2);
}

TEST_CASE("Graph Tests", "[g]") {
    GraphGenerator graph_gen;
    graph_gen.GenerateGraph("../tests/test-repo/src","another_header.h");

    Graph graph = graph_gen.GetGraph();
    Agraph_t* agraph = graph.GenerateGraph();

    std::vector<std::string> positions;
    for(auto n = agfstnode(agraph); n; n = agnxtnode(agraph,n)) {
        positions.push_back(agget(n, "pos"));
    }

    std::vector<std::string> expected{"200,70!","0,70!","0,0!"};

    REQUIRE(positions == expected);
}