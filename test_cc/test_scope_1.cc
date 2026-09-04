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
  //ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO);

  auto s1_obj = Scope::create();
  s1_obj->var_add("k1", Node::create("hello, world"));
  cout << "scope s1_obj: " << s1_obj->_to_str() << "\n";
  cout << "scope s1_obj  k1: " << s1_obj->lookup("k1") << "\n\n";

  auto s1b_obj = Scope::init_existing(s1_obj.get());
 // s1b_obj.var_add("k2", Node::create(55555l));
 // cout << "scope existing s1b_obj.get_node()  " << s1b_obj.get_node() << "\n\n";



  //auto s1_child_ptr  = s1b_obj.create_child();
  //auto s1_child_ptr  = s1_obj->create_child();
  s1_obj->create_child();
//  auto s1_child_ptr  = Scope::create(s1_obj.get());
  //s1_child_ptr->var_add("ck1", Node::create("hola mundo"));
  //cout << "s1_child.get_node()  " << s1_child_ptr->_to_str() << "\n\n";



  





}
