#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include "CallGraph.h"

using namespace std;

// To compile into pipair, use 
// clang -emit-llvm -c infer_invariants.cpp CallGraph.cpp -o pipair

// for running command line and getting the output
vector<string> exec(const char* cmd) {
	FILE* command = popen(cmd, "r");
	char buffer[512];
	vector<string> result;
	while (fgets(buffer, sizeof(buffer), command) != NULL) {
		result.push_back(buffer);
	}
	pclose(command);
	return result;
}

void createCallGraph(vector<string> llvmOut, CallGraph& callGraph) {
	//CallGraph *callGraph = new CallGraph();
	// string match1 = "Call graph node for function: '(.*)'<<0x[a-f0-9]+{7}>> #uses=[0-9]+";
	string firstLine = "Call graph node for function: \'";
	string callsiteLine = "calls function \'";
	string functionName;
	string childFunctionName;
	for (vector<string>::iterator it = llvmOut.begin(); it != llvmOut.end(); ++it) {
		// see if it matches to the things and call addNodes ....
		string currLine = (*it); //do we need to get rid of spaces?
		// if ( regex_match (currLine, regex(match1)) ) {
		size_t findFirst = currLine.find(firstLine)+firstLine.length();
		size_t findCallsite = currLine.find(callsiteLine)+callsiteLine.length();
		if (findFirst < currLine.length()) {
			size_t findEndFunction = currLine.find('\'', findFirst+1);
			functionName = currLine.substr(findFirst,findEndFunction);
			cout << "Adding: " << functionName  << " to callGraph" << endl;
			callGraph.addNodes(functionName);
		} else if (findCallsite < currLine.length()) {
			size_t findCallsiteFunction = currLine.find('\'', findCallsite+1);
			childFunctionName = currLine.substr(findCallsite,findCallsiteFunction);
			cout << "Adding: " << childFunctionName  << " to callGraph" << endl;
			callGraph.addEdges(functionName, childFunctionName);
		}
	}
}

int main(int argc, char* argv[]) {
	cout << argc << endl;
	// cout << argv[0] << endl;
	cout << "WTF2" << endl;
	vector<string> llvmOutp;
	int T_SUPPORT = 3 ;
	int T_CONFIDENCE = 65;
	cout << "WTF" << endl;

	// argc is 1 normally, arguments start at count 2 and argv[1]
	if (argc == 4) {
		// ./pipair <bitcode file> <T_SUPPORT> <T_CONFIDENCE>
		string opt_command = string("opt -print-callgraph ") + string(argv[1]);
		llvmOutp = exec(opt_command.c_str());
		T_SUPPORT = atoi(argv[2]);
		T_CONFIDENCE = atoi(argv[3]);
	} else if (argc == 2) {
		// ./pipair <bitcode file>
		// default support 3, confidence 65%
		string opt_command = string("opt -print-callgraph ") + string(argv[1]);
		llvmOutp = exec(opt_command.c_str());
	} else {
		// print an error message?
		cout << "Invalid Arguments" << endl;
		return 0;
	}

	CallGraph* callGraph = new CallGraph();
	createCallGraph(llvmOutp, *callGraph);
	// delete callGraph;

}

