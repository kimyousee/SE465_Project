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

class CallGraph {
private:
	int level;
	std::set<std::string> functionSet;
	std::map<std::string, std::set<std::string> > childFunctions;
	std::map<std::string, std::set<std::string> > cloneChildFxs;
	std::map<std::pair<std::string, std::string>, int> supportPairs;
	std::map<std::string, int> supportMap;
	std::map<std::pair<std::string, std::string>, std::string > highConfPairs;
public:
	CallGraph();
	~CallGraph();
	void addNodes(std::string functionName);
	void addEdges(std::string parentFunction, std::string childFunctionName);
	std::pair<double, double> calculateConfidence(std::pair<std::string, std::string>& pairFunctions);
	void findBugs(int confidence, int support);
	void interproceduralAnalysis(int level);
	std::set<std::string> interprocedural(std::set<std::string> &s, std::string k, int level);
};

#endif

