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


  trace_function.open("trace.log", std::ios::out);
  //ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  ScopeLogger::set_current_verbose_level(SLOG_NODE_OP);


  Node v1(123l);

  auto n1 = Node::create(&v1);
  cout << "n1->to_str()" <<  n1->_to_str()<< "\n";
  cout << "n1->unwrap_value<Node>()" <<  n1->unwrap_value<Node>()<< "\n";
  cout << "n1->unwrap_value<Int>()" <<  n1->unwrap_value<Node::Integer>()<< "\n";

/*
  Node tm4(Node::Type::Map);

  //tm4.extend({"hello", "world"});
  // tm4.add({"hello", "world"}, Node::create(555l));
  tm4.set({"hello", "world"}, Node::create(555l), true);

  //cout << "m4: " << Node::_to_str( m4) << "\n";
  cout << "tm4: " << tm4 << "\n";

  auto &m4 = tm4.get_value<Node::Map>();
  cout << "m4: " << Node::_to_str( m4) << "\n";

  Node &m4_n =  tm4.unwrap_value<Node>();
  m4_n.set({"hello", "world"}, Node::create(777l), true);
  cout << "m4_n: " << m4_n << "\n";
  cout << "tm4: " << tm4 << "\n\n";

  


//  SECTION("l1._get_map_ref() throw::bad_type_id") {
//    REQUIRE_THROWS_AS(l1._get_map_ref(), std::bad_typeid);
//  }
//  SECTION("tm4._add() throw::bad_type_id") {
//    REQUIRE_THROWS_AS(tm4.add(Node::create(1234l)), std::bad_typeid);

  Node tm5(Node::Type::Map);
  const auto &m5_n = tm5.unwrap_value<Node>();
  cout << "m5_node: " << m5_n << "\n\n";

  const auto &m5_m = tm5.unwrap_value<Node::Map>();
  cout << "m5_map: " << Node::_to_str( m5_m) << "\n\n";
  





//  tm2.extend(p, true);
*/


}
