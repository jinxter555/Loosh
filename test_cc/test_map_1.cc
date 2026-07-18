#include "../node.hh"
#include <iostream>

using namespace  std;
  
#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"


int main() {

  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_node_1 main()", __func__, SLOG_FUNC_INFO);

  Node tm2(Node::Type::Map);
  cout << "\ntm2: " <<  tm2 << "\n";
  vector<string> p = {"hello", "world"};
  vector<string> p2 = {"hello", "world", "mundo"};
  vector<string> p3 = {"hello", "world", "hola", "mundo"};
  tm2.extend(p, true);
  cout << "tm2: " <<  tm2 << "\n";
  tm2.set(p2, Node::create(123), true);
  cout << "tm2: " <<  tm2 << "\n";
  cout << "tm2 getnode p2: " << tm2.get_node(p2) << "\n";
  cout << "tm2 getnode p3: " << tm2.get_node(p3) << "\n";


  tm2.set(p2, Node::create(456), true);
  cout << "tm2: " <<  tm2 << "\n";
  cout << "tm2 getnode p2: " << tm2.get_node(p2) << "\n";

  tm2.set(p, Node::create(789), false);
  cout << "try 789 with no overrwide tm2: " <<  tm2 << "\n";

  tm2.set(p, Node::create(789), true);
  cout << "try 789 with override tm2: " <<  tm2 << "\n";

  tm2.set({"hello2", "world2"}, Node::create(5555), true);
  cout << "hello2 tm2: " <<  tm2 << "\n";

}