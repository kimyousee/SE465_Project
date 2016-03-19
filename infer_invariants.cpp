#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdio>
#include <memory>
#include <string>

using namespace std;

// for running command line and getting the output
string exec(const char* cmd) {
  FILE* command = popen(cmd, "r");
  char buffer[512];
  std::string result = "";
  while (fgets(buffer, sizeof(buffer), command) != NULL) {
    result += buffer;
  }
  pclose(command);
  return result;
}

int main(int argc, char* argv[]){
  cout << argc << endl;
  cout << argv[0] << endl;
  string llvmOutp;
  int confidence = 65;
  int support = 3;

  // argc is 1 normally, arguments start at count 2 and argv[1]
  if (argc == 4) {
    // ./pipair <bitcode file> <T_SUPPORT> <T_CONFIDENCE>
    llvmOutp = exec("opt -print-callgraph " + argv[1]);
    support = atoi(argv[2]);
    confidence = atoi(argv[3]);
  } else if (argc == 2) {
    // ./pipair <bitcode file>
    // default support 3, confidence 65%
    llvmOutp = exec("opt -print-callgraph " + argv[1]);
  }

  

}

