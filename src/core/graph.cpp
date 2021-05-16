#include "core/graph.h"
#include "core/cycle_detector.h"

Graph::Node::Node(const Node &node) {
    name_ = node.name_;
    max_dist = node.max_dist;
}

Graph::Node::Node(const std::string& name) : name_(name){
}

Graph::Graph() {
    gvc_ = gvContext();
}

Graph::Graph(const std::string& root) {
    gvc_ = gvContext();
    root_ = root;
}


void Graph::AddNode(const std::string & name) {
    Node n = Node(name);
    graph_[n] = std::vector<Node>(); //Adds node to graph with empty vector 
}

void Graph::AddEdge(const Node& node_1, const Node& node_2) {
    try {
        //access element in graph and push back into vector
        graph_.at(node_1).push_back(node_2);
    } catch (std::out_of_range& e) {
        throw std::invalid_argument("Node 1 does not exist in graph");
    }
}

std::vector<Graph::Node> Graph::FindAdjacents(const std::string& name) {
    Node n;
    n.name_ = name;
    return graph_.at(n);
}

Agraph_t * Graph::GenerateGraph() {
    // Detect cycle on the current graph itself
    CycleDetector cycleDetector (*this);
    auto cycles = cycleDetector.FindCycle();
    SetCycleEdges(cycleDetector.GetCycleEdges());
    CalculateNodePositions();




    Agraph_t* G;
    
    G = agopen(utils::makeCharPointer("Dependency Graph"), Agstrictdirected, NULL);
    agattr(G,AGNODE, "pos","0,0!");
    agattr(G,AGNODE, "color","black");

    for(auto it = graph_.begin(); it != graph_.end(); ++it){

        // Write nodes, as well as their position, to dot file
        Agnode_t * node = agnode(G, utils::makeCharPointer(it->first.name_), TRUE);
        char* position = utils::makeCharPointer(std::to_string(max_distances_.at(it->first).first * 200)+","+std::to_string(max_distances_.at(it->first).second * 70)+"!");
        agset(node, "pos", position);

        auto cycle_index = cycleIndex(it->first, cycles);
        if(!cycle_index.empty()){ // If there is a cycle present, then color the nodes in that cycle to indicate that
            agset(node, "color", utils::getColorCode(cycle_index.back(), cycles.size()));
        }
        
        // Write edges of current node to its children to dot file
        for(Node & dest_node : it->second){
            Agnode_t * dest = agnode(G, utils::makeCharPointer(dest_node.name_), true);
            Agedge_s * edge = agedge(G, node, dest,utils::makeCharPointer(""),true);

        }
    }

    return G;
}

void Graph::RenderGraph(std::FILE * file) {
    RenderGraph(GenerateGraph(), file);
}

void Graph::RenderGraph(Agraph_t *graph, std::FILE * file) {
    gvLayout(gvc_, graph, "nop"); // neato engine with pre-defined positions
    gvRender(gvc_, graph, "dot", file);
    gvFreeLayout(gvc_, graph);
    gvFreeContext(gvc_);
    agclose(graph);
}

std::vector<Graph::Node> Graph::DFS() {
    Node root = Node(root_);
    std::vector<Node> dfs_tree;
    visited_.clear();           // Clears visited nodes so that we can use it for DFS
    _DFS(root, dfs_tree); // send root to helper recursive function
    return dfs_tree;
}

void Graph::_DFS(const Node& sub_root, std::vector<Node>& curr_tree) {
    visited_.insert(sub_root);
    curr_tree.push_back(sub_root);
    
    auto it = graph_.find(sub_root);
    if (it != graph_.end()) {
        for(const Node & child : it->second) {
            // Only recurses down if the child hasn't been visited before
            if (visited_.find(child) == visited_.end()) {
                _DFS(child, curr_tree);
            }
        }
    }
}

std::unordered_map<Graph::Node, std::vector<Graph::Node>, Graph::Hasher> Graph::GetGraphMap() const {
    return graph_;
}

std::unordered_map<Graph::Node, std::pair<int, int>, Graph::Hasher> Graph::CalculateNodePositions() {
    Node root = Node(root_);
    visited_.clear(); // Clears visited nodes so that we can use it again (may have been filled from DFS)
    node_positions.insert(max_distances_[root]);
    _CalculateNodePositions(root); // send root to helper recursive function
    return max_distances_;
}

void Graph::_CalculateNodePositions(Node& sub_root) {
    visited_.insert(sub_root); // Mark current node as visited
    
    auto it = graph_.find(sub_root);
    if (it != graph_.end()) {           // Check if node is within the graph
        int count = 0;
        for(Node & child : it->second) {
            std::pair<Node, Node> curr_edge = {sub_root, child};
            // If the edge we are on isn't an edge that causes a cycle 
            // then increments the y depth and finds x value of the node
            if (cycle_edges_.find(curr_edge) == cycle_edges_.end()) {
                auto & child_max = max_distances_[child];
                max_distances_[child].second = std::max(max_distances_[sub_root].second+1, max_distances_[child].second);
                max_distances_[child].first = count;
                while  (node_positions.find(max_distances_[child]) != node_positions.end()) {
                    max_distances_[child].first++;
                    max_distances_[child].second++;
                }
                
                node_positions.insert(max_distances_[child]);
            }

            if (visited_.find(child) == visited_.end()) {
                _CalculateNodePositions(child);
            }

            count++;
        }
    }
}

void Graph::SetCycleEdges(const std::set<std::pair<Graph::Node, Graph::Node>>& cycle_edges) {
    cycle_edges_ = cycle_edges;
}

std::list<int> Graph::cycleIndex(const Graph::Node &node, const vector<std::set<Graph::Node>> &cycles_list) {
    std::list<int> cycle_index;

    int index_count = 0;
    for(auto cycle : cycles_list){
        if(cycle.find(node) != cycle.end()){
            cycle_index.push_back(index_count);
        };
        ++index_count;
    }
    return cycle_index;

}

bool Graph::IsDescendant(const Node& parent, const Node& descendant)  {
    //if(!visited_desc_.empty()) visited_desc_.clear();
    visited_.clear();

    return _IsDescendant(parent, descendant);
}

bool Graph::_IsDescendant(const Node& parent, const Node& descendant)  {
    std::vector<Graph::Node> v = FindAdjacents(parent.name_);
    if (std::find(v.begin(), v.end(), descendant) != v.end()) return true;
    visited_.insert({parent});
    std::vector<Graph::Node> children = graph_.at(parent);

    for(auto& it: children) {
        if (visited_.find(it) == visited_.end()) {
            return _IsDescendant(it, descendant);
        } 
    }
    return false;
}

