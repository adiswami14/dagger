#pragma once
#include "core/graph.h"
#include <unordered_map>
#include <set>
#include <vector>

using std::unordered_map;
using std::set;
using std::pair;
using std::vector;

class CycleDetector {
    public:

        // default constructor for CycleDetector class
        CycleDetector() = default;

        /**
        * Overloaded constructor for CycleDetector class
        * @param graph The instance of graph to detect the cycles in
        **/
        CycleDetector(const Graph& graph);

        /**
        * The main function used for detecting all cycles in the given graph
        * @return A vector of set of nodes, with each set in the vector representing a cycle in the graph
        **/
        vector<set<Graph::Node>> FindCycle();

        std::set<pair<Graph::Node, Graph::Node>> GetCycleEdges();

    private:

        /**
        * Helper function that recursively searches for a cycle given a parent to traverse down from
        * @param currnode The current node to start the recursion of checking the cycle at
        * @param visited_nodes Map marking the nodes that have been visited through checking for cycles
        * @param cycle_vec A vector that denotes the current cycle that has been detected through the recursive calls to the function
        * @return whether or not a cycle has been find by iterating down the current parent
        **/
        bool CycleHelper(const Graph::Node& currnode, unordered_map<Graph::Node, bool, Graph::Hasher>& visited_nodes, vector<Graph::Node>& cycle_vec);

        /**
        * Helper function that gets rid of extraneous nodes in the cycle
        * @param cycle_vec the vector containing the nodes in the cycle to be trimmed
        **/
        void TrimCycle(vector<Graph::Node>& cycle_vec);

        std::set<pair<Graph::Node, Graph::Node>> cycle_edges_;

        // The current instance of Graph for this class
        Graph graph_;

        // The current parent used for iterating through the Graph class's DFS method, so the class can safely recurse down without repeats
        Graph::Node current_parent_;
};