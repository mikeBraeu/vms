#define MEMSIZE 65536 // 16 bit
#define MEMSIZETWO 16777216 //24 bit
#define MEMSIZETHREE 4294967296

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

char mem [MEMSIZETWO];
int sp = 0;
bool done = false;
map<string,void (*) ()> bigdic;



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





void makedic() {
  bigdic.insert(pair<string, void (*) ()>("pop", pop));
  bigdic.insert(pair<string, void (*) ()>("dup", dup));
  bigdic.insert(pair<string, void (*) ()>("pull", pull));
  bigdic.insert(pair<string, void (*) ()>("print", print));
  bigdic.insert(pair<string, void (*) ()>("term", term));
  bigdic.insert(pair<string, void (*) ()>("add", add));
  bigdic.insert(pair<string, void (*) ()>("mul", mul));
  bigdic.insert(pair<string, void (*) ()>("push0", push0));
  bigdic.insert(pair<string, void (*) ()>("push1", push1));
  bigdic.insert(pair<string, void (*) ()>("push2", push2));
  bigdic.insert(pair<string, void (*) ()>("push3", push3));
  bigdic.insert(pair<string, void (*) ()>("push4", push4));
  bigdic.insert(pair<string, void (*) ()>("push5", push5));
  bigdic.insert(pair<string, void (*) ()>("push6", push6));
  bigdic.insert(pair<string, void (*) ()>("push7", push7));
  bigdic.insert(pair<string, void (*) ()>("push8", push8));
  bigdic.insert(pair<string, void (*) ()>("push9", push9));
}


void run(std::vector<string> prog) {

  for (int progcount = 0; !done ;progcount++){
    if (progcount == prog.size()) progcount = 0;
    //decode(prog[progcount])();
      bigdic[prog[progcount]]();
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
