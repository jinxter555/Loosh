#include "../tree.hh"
#include <iostream>

using namespace  std;
  
#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"


int main() {

  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_tree_1 main()", __func__, SLOG_FUNC_INFO);



  Tree tm2;
  vector<string> p = {"hello", "world"};
  vector<string> p2 = {"hello", "mundo"};
  vector<string> p3 = {"hola", "mundo"};
  tm2.set(p, Node::create(123), true);
  tm2.set(p2, Node::create(3.145), true);
  tm2.set(p3, Node::create(456), true);
  cout << "tm2:\n";
  tm2.print();

}