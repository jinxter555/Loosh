#include <cassert>
#include <catch2/catch_all.hpp>


#include "../environment.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
using namespace Loosh;
  



TEST_CASE("check scope 1") {
    Node::Error::init();


  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  Scope s1_node_obj;
  s1_node_obj.add("k1", Node::create("hello, world"));

  cout << "scope s1_node_obj: " << s1_node_obj << "\n";

//  s1_node_obj.print();


  





//  tm2.extend(p, true);
}
