#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <variant>
using namespace std;

int main (int argc, char *argv[]) {
  vector<string> prog;

  if (argc != 2) exit(1);

  ifstream sourcefile(argv[1]);
  string str;

  while (getline(sourcefile, str)){
    prog.push_back(str);
  }



}