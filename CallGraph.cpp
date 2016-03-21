#include "CallGraph.h"

using namespace std;

CallGraph::CallGraph() {}
CallGraph::~CallGraph() {}

void CallGraph::addNodes(string functionName) {
	// GraphNode currNode;
	// currNode.name = functionName;

	// if (functionSet.find(currNode) == functionSet.end())
	// 	functionSet.insert(currNode);

	if (functionSet.find(functionName) == functionSet.end()) 
		functionSet.insert(functionName);

}

void CallGraph::addEdges(string parentFunction, string childFunctionName) {
	// GraphNode childNode;
	// childNode.name = childFunctionName;
	set<string> childrenSet;
	if (childFunctions.find(parentFunction) == childFunctions.end()) {
		childFunctions[parentFunction] = childrenSet;
	} else {
		childrenSet = childFunctions.find(parentFunction)->second;
	}
	childrenSet.insert(childFunctionName);
	// childFunctions[parentFunction].insert(childFunctionName);
}

