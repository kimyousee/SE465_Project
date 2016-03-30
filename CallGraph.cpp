#include <iomanip>
#include <sstream>
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
	map<string, set<string> >::iterator itChildFunctions = childFunctions.find(parentFunction);
	// first edge/child of parentFunction
	if (itChildFunctions == childFunctions.end()) {
		childrenSet.insert(childFunctionName);
		childFunctions[parentFunction] = childrenSet;
	} else {
		if ((childFunctions[parentFunction]).find(childFunctionName) != childFunctions[parentFunction].end()) {
			return; // if it is in the set already
		}
		// Iterator through current edges for this parentFunction and add the pairs
		set<string>::iterator it;
		for (it = childFunctions[parentFunction].begin(); it != childFunctions[parentFunction].end(); it++) {
			string cur = *it;
			pair<string, string> pair1 = make_pair(cur, childFunctionName);
			pair<string, string> pair2 = make_pair(childFunctionName, cur);
			if (supportPairs.find(pair1) == supportPairs.end()) {
				supportPairs[pair1] = 1;
				supportPairs[pair2] = 1;
			} else {
				supportPairs[pair1] += 1;
				supportPairs[pair2] += 1;
			}
		}
		(itChildFunctions->second).insert(childFunctionName);
	}
	if (supportMap.find(childFunctionName) == supportMap.end()) {
		supportMap[childFunctionName] = 1;
	} else {
		supportMap[childFunctionName] += 1;
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

pair<double, double> CallGraph::calculateConfidence(pair<string, string>& pairFunctions) {
	if (supportPairs.find(pairFunctions) != supportPairs.end()) {
		int supportPairVal = supportPairs.find(pairFunctions)->second;
		int supportA = supportMap.find(pairFunctions.first)->second;
		int supportB = supportMap.find(pairFunctions.second)->second;
		double confidenceA = ((double)supportPairVal / (double)supportA) * 100;
		double confidenceB = ((double)supportPairVal / (double)supportB) * 100;
		return make_pair(confidenceA, confidenceB);
	}
	return make_pair(-1.0, -1.0);
}

void CallGraph::findBugs(int confidence, int support) {
	// iterate through each scope
	for (set<string>::iterator it = functionSet.begin(); it != functionSet.end(); it++) {
		string scope = *it;
		// iterate through scope's use functions
		for (set<string>::iterator itChildren = childFunctions[scope].begin(); itChildren != childFunctions[scope].end(); itChildren++) {
			set<string>::iterator itPair = itChildren;
			itPair++;
			for (; itPair != childFunctions[scope].end(); itPair++) {
				pair<string, string> pairFuncs = make_pair(*itChildren, *itPair);
				pair<double, double> pairConf = calculateConfidence(pairFuncs);
				int supportPairVal = supportPairs[pairFuncs];
				if (supportPairVal >= support) {
					if (pairConf.first >= confidence) {
						stringstream ss;
						ss << ", pair: (" << pairFuncs.first << ", " << pairFuncs.second << "), support: "
						   << supportPairVal << ", confidence: " << setprecision(2) << fixed << pairConf.first << "\%";
						highConfPairs[make_pair(pairFuncs.first, pairFuncs.second)] = ss.str();
					}
					if (pairConf.second >= confidence) {
						stringstream ss;
						ss << ", pair: (" << pairFuncs.first << ", " << pairFuncs.second << "), support: "
						   << supportPairVal << ", confidence: " << setprecision(2) << fixed << pairConf.second << "\%";
						highConfPairs[make_pair(pairFuncs.second, pairFuncs.first)] = ss.str();
					}
				}
			}
		}
	}

	for (set<string>::iterator it = functionSet.begin(); it != functionSet.end(); it++) {
		string scope = *it;

		for (map<pair<string, string>, string>::iterator it2 = highConfPairs.begin(); it2 != highConfPairs.end(); it2++) {
			if ( childFunctions[*it].find(it2->first.first) != childFunctions[*it].end() && childFunctions[*it].find(it2->first.second) == childFunctions[*it].end() ) {
				cout << "bug: " << it2->first.first << " in " << *it <<  it2->second << endl;
			}
		}
	}
}

void CallGraph::interproceduralAnalysis() {
	for (map<string, set<string> >::iterator it = childFunctions.begin(); it != childFunctions.end(); it++) {
		string key = it->first;
		set<string> value = it->second;
		interprocedural(value, key);
		value.erase(key);
	}
}

void CallGraph::interprocedural(set<string> &s, string k) {
	set<string> tmpSet = childFunctions.find(k)->second;
	s.insert(tmpSet.begin(),tmpSet.end());
	for (set<string>::iterator it = tmpSet.begin(); it != tmpSet.end(); it++) {
		set<string> itChildren = childFunctions.find(*it)->second;
		s.insert(itChildren.begin(),itChildren.end());
	}
}
