#include "core/cycle_detector.h"

CycleDetector::CycleDetector(const Graph& graph) : graph_(graph) {}

vector<set<Graph::Node>> CycleDetector::FindCycle() {    
    unordered_map<Graph::Node, bool, Graph::Hasher> visited_nodes;
    vector<set<Graph::Node>> return_vec;


    for(auto& it : graph_.DFS()) {
        vector<Graph::Node> cycle_vec;

        current_parent_ = it;
        CycleHelper(it, visited_nodes, cycle_vec);
        TrimCycle(cycle_vec);
        if(cycle_vec.size() > 1) {  // A cycle must have multiple nodes, so we can eliminate cycles that are only a single node
            set<Graph::Node> s(cycle_vec.begin(), cycle_vec.end()); // We use a set here to eliminate repeat node calls within a cycle
            if(s.size() > 1) {
                return_vec.push_back(s);
            }
        }
        //std::cout << std::endl << std::endl;
    }


    size_t cycle_count = 1;
    for(const auto& it: return_vec) {
        cycle_edges_.insert({*(--(it.end())), *(it.begin())});
        cycle_count++;
    }
//    graph_.SetCycleEdges(cycle_edges);

    return return_vec; 
}

bool CycleDetector::CycleHelper(const Graph::Node& currnode, unordered_map<Graph::Node, bool, Graph::Hasher>& visited_nodes, vector<Graph::Node>& cycle_vec) {
    std::vector<Graph::Node> node_vec = graph_.GetGraphMap().at(currnode);
    if(visited_nodes[currnode]) {
        // Here we check if currnode is a leaf, giving us two options:
        // If currnode is a leaf, then no cycle has been found, as you have traversed all the way down the dependency graph
        // If currnode does have children, and this node has already been visited, then this is a cycle
        if(node_vec.empty()) return false;
        else return true;
    }

    visited_nodes[currnode] = true;

    // Iterating through the children of the currnode, recursively calling CycleHelper for each one
    for(size_t i = 0; i < node_vec.size(); i++) {
        Graph::Node next = node_vec[i];
        if(CycleHelper(next, visited_nodes, cycle_vec)) { // If this condition is true, we recursively add the nodes in the strongly connected component
            //std::cout << "Currnode: " << currnode.name_ << "to next: " << next.name_ << std::endl;
            cycle_vec.insert(cycle_vec.begin(), next);

            // If the current node that we are at is the current parent we have passed in, then insert the node into the cycle (we will remove it later if it is not part of a cycle)
            if(currnode == current_parent_) cycle_vec.insert(cycle_vec.begin(), currnode); 
            return true;
        } else {
            visited_nodes[next] = false; // If no cycle is found, mark the child node as not visited, as it could be part of another cycle yet to be discovered
        }
    }

    return false;
}

void CycleDetector::TrimCycle(vector<Graph::Node>& cycle_vec) {
    if(cycle_vec.empty()) return;

    Graph::Node last_node = *(cycle_vec.rbegin());
    vector<Graph::Node> last_node_children = graph_.GetGraphMap().at(last_node);
    bool cycle_found = false;
    for(auto& it : cycle_vec) {
        // If the children of the last node in the cycle contains the correct node, that means a cycle is present
        // Since we add the elements of the cycle recursively, that means each node in the cycle vector is a child of its predecessor
        // This means we can effectively weed out all the elements that do not belong to the cycle
        if(graph_.IsDescendant(last_node, it)) {  // std::find(last_node_children.begin(), last_node_children.end(), it) != last_node_children.end() || 
            cycle_vec.erase(cycle_vec.begin(), std::find(cycle_vec.begin(), cycle_vec.end(), it));
            cycle_found = true;
            break;
        }
    }

    // There is still a chance that we can have two cycles stemming from the same node, in which case a cycle won't be detected by the code above
    // A simple fix for this is realizing that the algorithm has already worked, so just need to find cases in which to erase an extra cycle
    // We only erase a cycle if a cycle has not been found in the given vector of nodes and the size is less than 2
    // If there is a cycle with a size of 2, then the above code will work, so this just gets rid of edge cases
    if(!cycle_found) cycle_vec.clear();
}

std::set<pair<Graph::Node, Graph::Node>> CycleDetector::GetCycleEdges() {
    return cycle_edges_;
}

