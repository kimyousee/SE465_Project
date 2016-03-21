#ifndef _CALL_GRAPH
#define _CALL_GRAPH

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>
#include <algorithm>

struct GraphNode {
	std::string name;

	GraphNode(const std::string& strName = "")
		: name(strName) {}

	bool operator<(const GraphNode& rhs) const {
		return name < rhs.name;
	}
};

// bool operator<(const GraphNode &a, const GraphNode &b) {
// 	return a.name < b.name;
// }

struct find_by_name {
private:
	std::string name;
public:
	find_by_name(const std::string & name) : name(name) {}
	bool operator()(const GraphNode & node) {
		return node.name == name;
	}
};

class CallGraph {
private:
	std::set<GraphNode> functionSet;
	std::map<GraphNode, std::vector<GraphNode> > childFunctions;
public:
	CallGraph();
	~CallGraph();
	void addNodes(std::string functionName);
};

#endif

