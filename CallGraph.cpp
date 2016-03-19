#include "CallGraph.h"

using namespace std;

void CallGraph::addNodes(string functionName){
	graphNode currNode;
	currNode.name = functionName;
	std::set<graphNode>::iterator result = std::find_if(functionSet.begin(), functionSet.end(),
	                                                    find_by_name(functionName));
	if (result != functionSet.end()) {
		functionSet.insert(currNode);
	}
}

