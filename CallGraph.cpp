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
	// first edge/child of parentFunction
	if (itChildFunctions == childFunctions.end()) {
		childrenSet.insert(childFunctionName);
		childFunctions[parentFunction] = childrenSet;
	} else {
		if ((childFunctions[parentFunction]).find(childFunctionName) != childFunctions[parentFunction].end()){
			return; // if it is in the set already
		}
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
		(itChildFunctions->second).insert(childFunctionName);

		if (supportMap.find(childFunctionName) == supportMap.end()) {
			supportMap[childFunctionName] = 1;
		} else {
			supportMap[childFunctionName] += 1;
		}
	}	
}

/*
void CallGraph::calculateConfidence(int confidence, int support) {
	for (map<pair<string,string>,int>::iterator it=supportPairs.begin(); it!=supportPairs.end(); ++it) {
		pair<string,string> currPair = it->first;
		int supportPairVal = it->second;
		int supportVal = supportMap.find(currPair.first)->second;
		int currConfidence = ((double)supportPairVal/(double)supportVal)*100 ;
		if (currConfidence >= confidence && supportPairVal >= support) {
			//bug: A in scope2, pair: (A, B), support: 3, confidence: 75.00%
			//cout << "bug: " << currPair.first << " in " << parentFunction
		}


	}
}
*/

void CallGraph::calculateConfidence(pair<string,string>& pairFunctions){

}

void CallGraph::findBugs(int confidence, int support){
	// iterate through each scope
	for(set<string>::iterator it = functionSet.begin(); it != functionSet.end(); it++){
		string scope = *it;
		// iterate through scope's use functions
		for(set<string>::iterator itChildren = childFunctions[scope].begin(); itChildren != childfunctions[scope].end(); itChildren++){
			set<string>::iterator itPair = itChildren
			itPair++;
			for(;itPair != childFunctions[scope].end(); itPair++){

			}
		}
	}
}


