#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <regex>
#include "CallGraph.cpp"

using namespace std;

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

CallGraph createCallGraph(vector<string> llvmOut) {
    CallGraph callGraph;
    string match1 = "Call graph node for function: '(.*)'<<0x[a-f0-9]+{7}>> #uses=[0-9]+";
    for (vector<string>::iterator it = llvmOut.begin(); it != llvmOut.end(); ++it) {
        // see if it matches to the things and call addNodes ....
        string currLine = (*it); //do we need to get rid of spaces?
        if ( regex_match (currLine, regex(match1)) ) {
            callGraph.addNodes(currLine);
        }
    }
    return callGraph;
}

int main(int argc, char* argv[]) {
	cout << argc << endl;
	cout << argv[0] << endl;
	vector<string> llvmOutp;
	int T_SUPPORT = 3 ;
	int T_CONFIDENCE = 65;

	// argc is 1 normally, arguments start at count 2 and argv[1]
	if (argc == 4) {
		// ./pipair <bitcode file> <T_SUPPORT> <T_CONFIDENCE>
		llvmOutp = exec("opt -print-callgraph " + argv[1]);
		T_SUPPORT = atoi(argv[2]);
		T_CONFIDENCE = atoi(argv[3]);
	} else if (argc == 2) {
		// ./pipair <bitcode file>
		// default support 3, confidence 65%
		llvmOutp = exec("opt -print-callgraph " + argv[1]);
	} else {
		// print an error message?
		cout << "Invalid Arguments" << endl;
	}

	CallGraph callGraph = createCallGraph(llvmOutp);

}

