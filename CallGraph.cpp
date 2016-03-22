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
	map<string,set<string> >::iterator itChildFunctions = childFunctions.find(parentFunction);
	if (itChildFunctions == childFunctions.end()) {
		childrenSet.insert(childFunctionName);
		childFunctions[parentFunction] = childrenSet;
	} else {
		if ((childFunctions[parentFunction]).find(childFunctionName) != childFunctions[parentFunction].end()){
			return; // if it is in the set already
		}
		(itChildFunctions->second).insert(childFunctionName);
	}
	// childFunctions[parentFunction].insert(childFunctionName);

	// Iterator through current edges for this parentFunction and add the pairs
	set<string>::iterator it;
	for(it = childFunctions[parentFunction].begin(); it != childFunctions[parentFunction].end(); it++){
		string cur = *it;
		pair<string,string> pair1 = make_pair(cur,childFunctionName);
		pair<string,string> pair2 = make_pair(childFunctionName,cur);
		if (supportPairs.find(pair1) == supportPairs.end()){
			supportPairs[pair1] = 1;
			supportPairs[pair2] = 1;
		} else {
			supportPairs[pair1] += 1;
			supportPairs[pair2] += 1;
		}
	}
}

