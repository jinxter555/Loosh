#include <iostream>
#include "../node.hh"
#include "../interactive.hh"


using namespace  std;
  


bool is_complete_parenthesis(const string& input) {
  vector<char> plist;
  size_t s=input.size();
  for(size_t i=0; i<s; i++) {
    char c = input[i];
    if(input[i] == '(') {
      plist.push_back(c);
    }
    if(input[i] == ')') {
      if(plist.empty()) return false;
      plist.pop_back();
    }
  }
  if(plist.size() != 0)
    return false;
  return true;
}

int main() {
  string str;
  str = "(";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = ")";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "))";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "(1212";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "()1212";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = ")()1212(";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "(1212)";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "((1212))";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "abc(1212)";
  cout << str << " " << is_complete_parenthesis(str) << "\n";
  str = "abc((1212))";
  cout << str << " " << is_complete_parenthesis(str) << "\n";

}
