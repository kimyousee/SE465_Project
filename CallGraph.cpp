#include "CallGraph.h"

using namespace std;

CallGraph::CallGraph() {}
CallGraph::~CallGraph() {}

void CallGraph::addNodes(string functionName){
	GraphNode currNode;
	currNode.name = functionName;

	// std::set<Node>::iterator result = std::find_if(functionSet.begin(), functionSet.end(),
	//                                                     find_by_name(functionName));
	if (functionSet.find(functionName) != functionSet.end()) {
		functionSet.insert(currNode);
	}
}

