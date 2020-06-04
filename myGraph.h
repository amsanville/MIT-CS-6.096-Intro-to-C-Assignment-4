#ifndef MYGRAPH_H
#define MYGRAPH_H
#include<map>
#include<vector>

/* 5 Graphs

Simple graph that uses a map to represent the adjacency list. Keys in maps are
unique so we use a key for the node and the value is the list of outgoing
edges. This makes everything but the constructor trivial.
*/
class Graph {
private:
	// The adjacency matrix stored in a map
	std::map<int, std::vector<int>> adjacencyList;
public:
	// Constructor
	Graph(const std::vector<int>& starts, const std::vector<int>& ends);
	// Returns number of outgoing edges
	int numOutgoing(const int nodeID) const;
	// Returns a reference to the list of nodes with outgoing edges
	const std::vector<int>& adjacent(const int nodeID) const;
};
#endif