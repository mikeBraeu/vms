#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <variant>
using namespace std;

bool pcolon = false;
vector<string> words;
map<string, variant<void (*) (), vector<string>>> defdic;
int sp = 0;
char mem [65536];

void insertIntoDic(string name, variant<void (*) (), vector<string>> code){
  defdic.insert(
    pair<string, variant<void (*) (), vector<string>>>(
      name,
      code
    )
  );
}

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

void add(){
  mem[sp-1] = mem[sp-1] + mem[sp];
  sp--;
}

void mul(){
  mem[sp-1] = mem[sp-1] * mem[sp];
  sp--;
}

void makedic() {
  insertIntoDic("pop", pop);
  insertIntoDic("dup", dup);
  insertIntoDic("pull", pull);
  insertIntoDic(".", print);
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


void exec(string name) {

  if (name == ":") {
    pcolon = true;
  } else if (name == ";") {
    pcolon = false;
    string newname = words[0];
    words.erase(words.begin());
    insertIntoDic(newname,  words);
    words.clear();
  } else if (pcolon){
    words.push_back(name);
  } else {
    std::visit([](auto arg){
      using T = std::decay_t<decltype(arg)>;
      if constexpr (std::is_same_v<T, void (*) ()>)
        arg();
      else
        for (int count = 0; count < arg.size() ; count++) {
          exec(arg[count]);
      }
    }, defdic[name]);
  }

}

int main(int argc, char *argv[]) {

  //char mem [16777216];
  //cout << "mem created" << endl;
  vector<string> progvec;

  makedic();

  if (argc != 2) exit(1);

  ifstream sourcefile (argv[1]);
  string str;
  cout << "input file stream created" << endl; 
  //while (get(sourcefile, str)){
  //  progvec.push_back(str);
  //}s
  while (sourcefile >> str) {
    //cout << str << endl;
    progvec.push_back(str);
    exec(str);
  }

  cout << "file finished executing" << endl;
  cout << "Program executed" << endl;
  for (int i = 0; i < progvec.size() ; i++) {
    cout << progvec[i] << endl;
  }

  cout << "Dictionary state" << endl;


  for (auto& t : defdic) {
    cout << t.first;
    std::visit([](auto arg){
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, vector<string>>)
      for (auto& s : arg) {
         cout << " " << s;
      }
      cout << endl;
    }, t.second);
  }
 
}
