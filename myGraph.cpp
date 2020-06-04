#include"myGraph.h"
#include<stdexcept>

// Constructor
Graph::Graph(const std::vector<int>& starts, const std::vector<int>& ends) {
	if (starts.size() != ends.size()) {
		throw std::invalid_argument("Error Constructing a Graph: starts and ends not same size");
	}
	else {
		for (unsigned int i = 0; i < starts.size(); i++ ){
			// Check if in adjacency list
			auto found = adjacencyList.find(starts[i]);
			if (found == adjacencyList.end()) {
				// If not, insert a new pair
				adjacencyList.insert(std::pair<int, std::vector<int>>(starts[i], std::vector<int>({ ends[i] })));
			}
			else {
				// If already in, add the end to the list stored at the key
				found->second.push_back(ends[i]);
			}
		}
	}
}

// Number Out-going
int Graph::numOutgoing(const int nodeID) const {
	return this->adjacent(nodeID).size();
}

// Adjacent
const std::vector<int>& Graph::adjacent(const int nodeID) const {
	// Map returns an iterator of some sort, just going to use auto
	auto temp = adjacencyList.find(nodeID);
	return temp->second;
}

// Note: note checking on ID. What happens if the id entered isn't found