#include "../node.hh"
#include <iostream>

using namespace  std;
  
#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"


int main() {

  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_node_1 main()", __func__, SLOG_FUNC_INFO);

  Node a(123);
  unique_ptr<Node> a1 = make_unique<Node>(1234);
  unique_ptr<Node> a2 = make_unique<Node>( make_shared<Node>(222));

  cout << "a: " << a << "\n";
  cout << "a1: " << *a1 << "\n";
  cout << "a2: " << *a2 << "\n";
  a1->delete_();
  a2->delete_();

  unique_ptr<Node> a3 = make_unique<Node>(1234);
  unique_ptr<Node> a4 = make_unique<Node>( make_shared<Node>(444));
  unique_ptr<Node> a5 = make_unique<Node>( make_unique<Node>(555));
  a4->delete_();
  a5->delete_();

  cout << "a1: " << *a1 << "\n";
  cout << "a1.type: " << Node::_to_str(a1->_get_type()) << "\n";
  cout << "a2: " << *a2 << "\n";

  cout << "a4: " << *a4 << "\n";
  cout << "a5: " << *a5 << "\n";

}
