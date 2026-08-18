#include <cassert>
#include <catch2/catch_all.hpp>


#include "spdlog/sinks/basic_file_sink.h"

#include "../environment.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
using namespace Loosh;
  



TEST_CASE("check scope 1") {


    auto file_logger = spdlog::basic_logger_mt("lisp_logger", "logs/nested_trace.log", true);
    spdlog::set_default_logger(file_logger);
    spdlog::set_level(spdlog::level::trace);
    //spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v");
    spdlog::set_pattern("[thread %t] [%l] %v");
    Node::Error::init();



  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  Scope s1_node_obj;
  s1_node_obj.var_add("k1", Node::create("hello, world"));
  cout << "scope s1_node_obj: " << s1_node_obj << "\n";
  cout << "scope s1_node_obj  k1: " << s1_node_obj.lookup("k1") << "\n\n";
  //cout << "scope s1_node_obj get_type: " << s1_node_obj._get_type() << "\n\n";
  cout << "scope s1_node_obj _get_type:\n" ;
  auto scope_atom_value = Node::_get_meta_type(&s1_node_obj);
  CHECK(scope_atom_value == Lang::Atom::scope);


  Scope s2_node_obj;
  s2_node_obj.var_add("k2", Node::create("hola, mundo"));
  cout << "scope s2_node_obj  : " << s2_node_obj << "\n\n";
  auto s2_obj_ptr_status = s2_node_obj.move_obj();
  cout << "scope s2_obj_ptr  : " << s2_obj_ptr_status << "\n\n";
  REQUIRE_THROWS( s2_node_obj.move_obj());


  /*
  auto s3_ptr_u = Scope::create();
  cout << "scope s3_ptr_u: " << s3_ptr_u->_to_str() << "\n\n";

  //Scope s4(s3_ptr_u.get(), true);
  Scope s4(&s1_node_obj, true);
  cout << "scope s4._to_str(): " << s4._to_str() << "\n\n";

*/

//  s1_node_obj.print();


  





//  tm2.extend(p, true);
}
