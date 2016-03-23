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
	// std::set<GraphNode> functionSet;
	// std::map<GraphNode, std::set<GraphNode> > childFunctions;
	std::set<std::string> functionSet;
	std::map<std::string, std::set<std::string> > childFunctions;
	std::map<std::pair<std::string, std::string>, int> supportPairs;
	std::map<std::string, int> supportMap;
public:
	CallGraph();
	~CallGraph();
	void addNodes(std::string functionName);
	void addEdges(std::string parentFunction, std::string childFunctionName);
	// std::map<std::pair<std::string, std::string>, int> getSupportPairs();
	// std::map<std::string, int> getSupportMap;
	//void calculateConfidence(int confidence, int support);
	std::pair<double, double> calculateConfidence(std::pair<std::string, std::string>& pairFunctions);
	void findBugs(int confidence, int support);
};

#endif

