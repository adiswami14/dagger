#pragma once
#include <graphviz/gvc.h>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "core/utils.h"
#include <graphviz/cgraph.h>
#include <set>
#include <functional>
#include <algorithm>
#include <list>

class Graph{
    public:
        struct Node {
            Node() = default;

            Node(const Node &node);

            Node(const std::string& name);

            std::string name_; 

            int max_dist = 0;

            //Make equals operator (the hasher checks this)
            bool operator==(const Node &rhs) const { return name_ == rhs.name_; }

            // A less that operator that is used by the set of Nodes in cycle detection to store their Nodes
            bool operator<(const Node &rhs) const { return (name_.compare(rhs.name_) < 0); }

        };

        struct Hasher {
            //Custom hashing function for map returns
            std::size_t operator()(const Node& node) const {
                return std::hash<std::string>()(node.name_);
            }
        };

        Graph();

        Graph(const std::string& root);
        
        // User defined root for proper DFS and calculation 
        // of node positions for layered graph drawing
        void SetRoot(const std::string& root) { root_ = root; }
        std::string GetRoot() { return root_; }

        //Creates new node and adds to graph_
        void AddNode(const std::string & name);

        //Dereferences node_1 and adds/appends to map with Node* node_2. 
        //Assumes node_1 already exists in graph_ and throws an exception if it doesn't
        void AddEdge(const Node& node_1, const Node& node_2);

        // Generates a graph using our layered graph drawing algorithm
        Agraph_t * GenerateGraph();

        // Writes graph output to a dot file, given a file to write to
        void RenderGraph(std::FILE * file);

        // Finds adjacent nodes to a node with the given name
        std::vector<Node> FindAdjacents(const std::string& name);

        std::unordered_map<Graph::Node, std::vector<Graph::Node>, Graph::Hasher> GetGraphMap() const;

        // Returns the nodes that the DFS traverses in the order in which it encounters them
        // Can use to the out.png file in order to confirm that the DFS is in fact traversing correctly
        std::vector<Node> DFS();

        // Cycles are calculated outside then graphviz and then sent in for use in the layered drawing algo
        void SetCycleEdges(const std::set<std::pair<Graph::Node, Graph::Node>>& cycle_edges);

        // Checks if a given node is the descendant of a particular parent node
        bool IsDescendant(const Node& parent, const Node& descendant);

    private:
        GVC_t * gvc_; // Used for graphviz rendering
        std::unordered_map<Node, std::vector<Node>, Hasher> graph_; // Adjacency list that contains all the Nodes and each node's children 
        std::string root_; // Arbitrary root of our graph that is set by the user
        std::unordered_map<Node, std::pair<int, int>, Hasher> max_distances_; // Contains node positions calculated such that the y value is based on the max distance from the root 
        std::set<Node> visited_; // All visited nodes - used for cycle detection
        std::set<std::pair<Graph::Node, Graph::Node>> cycle_edges_; // Contains all edges that cause a cycle to occur
        std::set<std::pair<int, int>> node_positions; // Used to determine if we have already used a certain position in order to prevent overlapping nodes
        
        void _DFS(const Node& sub_root, std::vector<Node>& curr_tree);
       
        // Wrapper method for calculating the positions of each node for the rendered graph
        std::unordered_map<Node, std::pair<int, int>, Graph::Hasher> CalculateNodePositions();
        
        // Calculates each node's position on the graph and stores those positions
        // in a map of nodes to pairs (max_distances_). 
        // The y value is calculated by finding the max distance from the root to each node
        // The x value starts at the leftmost column and shifts right based on the number of children nodes
        void _CalculateNodePositions(Node& sub_root);

        //Checks if a node exists in a cycle(s) and returns which index
        std::list<int> cycleIndex(const Node& node, const std::vector<std::set<Graph::Node>> & cycles_list );

        // renders a graph using a given Agraph
        void RenderGraph(Agraph_t * graph, std::FILE * file);

        bool _IsDescendant(const Node& parent, const Node& descendant);
};