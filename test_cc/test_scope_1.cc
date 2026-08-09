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
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v");
    Node::Error::init();



  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  Scope s1_node_obj;
  s1_node_obj.var_add("k1", Node::create("hello, world"));

  cout << "scope s1_node_obj: " << s1_node_obj << "\n";
  cout << "scope s1_node_obj  k1: " << s1_node_obj.lookup("k1") << "\n";

  spdlog::info("hello, world!");

//  s1_node_obj.print();


  





//  tm2.extend(p, true);
}
