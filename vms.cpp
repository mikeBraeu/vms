/*
what is left to add?

branching/loops

subroutines, possibly implemented in a way that is compatible with recursion

better constant pushing

tail call optimization?

*/

#define MEMSIZE 65536 // 16 bit
#define MEMSIZETWO 16777216 //24 bit
#define MEMSIZETHREE 4294967296

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <variant>
using namespace std;

char mem [MEMSIZETWO];
int sp = 0;
bool done = false;
map<string,void (*) ()> bigdic;

map<string, vector<variant<string, void (*) ()>>> newdic;

/* 
comm = string | code
def = [com]
string -> [string | code] 
*/
void push(char x) {
  sp++;
  mem[sp] = x;
}

void push0(){ push(0); }
void push1(){ push(1); }
void push2(){ push(2); }
void push3(){ push(3); }
void push4(){ push(4); }
void push5(){ push(5); }
void push6(){ push(6); }
void push7(){ push(7); }
void push8(){ push(8); }
void push9(){ push(9); }


void pop() {
  sp--;
}

void pull() {
  char i = mem[sp];
  sp--;
  char temp = mem[sp-i];
  for (char j = 0; j<i ;j++){
      mem[sp-i+j] = mem[sp-i+j+1];
  }

  mem[sp] = temp;
}

void dup() {
  sp++;
  mem[sp] = mem[sp-1];
}

void print(){
  for (int i = 0 ; i < sp ; i++){
    cout << static_cast<unsigned>(mem[sp-i]) << endl;
  }
}

void term(){
  print();
  done = true;
}

void add(){
  mem[sp-1] = mem[sp-1] + mem[sp];
  sp--;
}

void mul(){
  mem[sp-1] = mem[sp-1] * mem[sp];
  sp--;
}








//map<string, vector<variant<string, void (*) ()>>> newdic;

void insertIntoDic(string name, void (* code) ()) {
  newdic.insert(pair<string, vector<variant<string, void (*) ()>>>(name, vector<variant<string, void (*) ()>> (1, variant<string, void (*) ()> (code))));
}

void makedic() {
  insertIntoDic("pop", pop);
  insertIntoDic("dup", dup);
  insertIntoDic("pull", pull);
  insertIntoDic("print", print);
  insertIntoDic("term", term);
  insertIntoDic("add", add);
  insertIntoDic("mul", mul);
  insertIntoDic("push0", push0);
  insertIntoDic("push1", push1);
  insertIntoDic("push2", push2);
  insertIntoDic("push3", push3);
  insertIntoDic("push4", push4);
  insertIntoDic("push5", push5);
  insertIntoDic("push6", push6);
  insertIntoDic("push7", push7);
  insertIntoDic("push8", push8);
  insertIntoDic("push9", push9);
}


void exec(string funcname) {
  for (int count = 0; (count < newdic[funcname].size()) && (!done) ; count++) {
    get<void (*) ()>(newdic[funcname][count])(); 
    std::visit([](auto& arg)){
      using T 
    };
  }
}



void run(std::vector<string> prog) {

  for (int progcount = 0; !done ;progcount++){
    if (progcount == prog.size()) progcount = 0;
    exec(prog[progcount]);
  }
} 



int main(int argc, char *argv[]) {

  vector<string> prog;

  if (argc != 2) exit(1);

  ifstream sourcefile(argv[1]);
  string str;

  while (getline(sourcefile, str)){
    prog.push_back(str);
  }

  makedic();
  run(prog);


}
