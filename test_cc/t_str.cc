#include <string>
#include <iostream>
using namespace std;

int main() {
  string s1, s2;
  s1 = "hello";
  s2 = move(s1);
  cout << "s2: " << s2 << "\n";
  cout << "s1: " << s1 << "\n";
  s1 = "world";
  cout << "s1: " << s1 << "\n";


}
