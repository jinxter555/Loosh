#include <cassert>
#include <catch2/catch_all.hpp>


#include "../node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

#include "../node_tmpl_cc.hh"



using namespace  std;
using namespace Loosh;
  



TEST_CASE("check node 2") {
    Node::Error::init();


  auto file_logger = spdlog::basic_logger_mt("lisp_logger", "logs/nested_trace.log", true);
  spdlog::set_default_logger(file_logger);

  trace_function.open("trace.log", std::ios::out);
  //ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  ScopeLogger::set_current_verbose_level(SLOG_NODE_OP);

  auto obj1 =  Node::create(Node::Type::SimpleObject);
  obj1->obj_info_add("type_cc_obj", Node::create(555l));
  obj1->obj_data_add("value1", Node::create(12345l));
  obj1->obj_data_add("value2", Node::create("this is the way"));
  cout << "obj1: " << *obj1 << "\n\n";

  auto obj2 =  Node::create(Node::Type::MetaObject);
  obj2->obj_info_add("type_cc_obj", Node::create(777));
  obj2->obj_data_add("value1", Node::create("Meta obj way"));
  obj2->obj_data_add("value2", Node::create(3.1415f));

  Node begin("begining"); obj2->set_parent(&begin);

  cout << "obj2: " << *obj2 << "\n";
  cout << "obj2.parent: " << obj2->get_parent().second->unwrap_value<Node>() << "\n";


  auto mt_n1 = Node(Node::Mutex(Node::create(123l), make_unique<mutex>() ));
  cout << "mt_n1: "  << mt_n1 << "\n";








}
