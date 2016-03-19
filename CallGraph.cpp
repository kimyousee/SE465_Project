#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>

using namespace std;

struct graphNode {
	string name;
};


class CallGraph {
private:
	set<graphNode> functionSet;
	map<graphNode, vector<graphNode> > childFunctions;
public:
	CallGraph();
	void addNodes(string functionName);
};

void CallGraph::addNodes(string functionName) {
	graphNode currNode;
	currNode.name = functionName;
	if (functionSet.find(currNode) != functionSet.end()) {
		functionSet.insert(currNode);
	}
}