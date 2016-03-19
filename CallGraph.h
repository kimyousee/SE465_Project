#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>
#include <algorithm>

struct graphNode{
	std::string name;
};

struct find_by_name{
private:
	std::string name;
public:
	find_by_name(const std::string & name) : name(name) {}
	bool operator()(const graphNode & node) {
		return node.name == name;
	}
};

class CallGraph{
private:
	std::set<graphNode> functionSet;
	std::map<graphNode, std::vector<graphNode> > childFunctions;
public:
	CallGraph();
	void addNodes(std::string functionName);
};


