#include <cassert>
#include <catch2/catch_all.hpp>


#include "../node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
using namespace Loosh;
  



TEST_CASE("check node 2") {


  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  //ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);

  Node n1(10l);
  Node n1_b(10l);
  cout << "n1: " << n1 << "\n";
  CHECK(n1._get_integer() == 10l );

  CHECK((n1 == n1_b)._get_bool()); 

  Node::Vector v1;
  auto m1_ptr = make_unique<Node::Map>();
 // Node::Value vv=m1;
  Node n2(move(v1));
  auto n1_c = n1.clone();
  cout << "n1_c: " << *n1_c << "\n";

  //Node n2_ptr = n1.clone();
  Node n2_ptr ; 
  n2_ptr = n1.clone();
  cout << "n2_ptr: " << n2_ptr << "\n";

  Node n3_ptr(n1.clone());
  cout << "n3_ptr: " << n3_ptr << "\n";
  CHECK((n2_ptr.get_node() == n3_ptr.get_node())._get_bool()); 





  Node a(10l);
  Node b(20l);
  Node t(true);
  auto vptr = Node::create(true);
  cout << "b: " << b << "\n";
  
  Node c = a + b;
  CHECK(c._get_str() == "30"); 
  Node d = c + Node(123.33);
  CHECK(d._get_str() == "153.33"); 
  string vs1 = c._to_str();
  string vs2 = d._to_str();

  cout << "vs1: " << vs1  << "\n";
  cout << "vs2: " << vs2  << "\n";

  //cout << "v1: " << v1  << "\n";
  Node e;
  //e.set(d.clone());
  cout << "e: " << e._to_str() << "\n";

  Node t1(Node::Type::Map);
  t1.set("line", 123l);
  t1.set("col", 456l);
  t1.set("value", 555.666f);
  cout << "t1: " <<  t1 << "\n";
  cout << "t1.to_str: " <<  t1._to_str() << "\n";
  Node::print_value_recursive(t1, 0);

  Node::Map m1;
  m1["hello"]=Node::create(123l);
  Node t2(move(m1));
  cout << "\nt2: " <<  t2 << "\n";
  Node::print_value_recursive(t2, 0);

  cout << "\nList\n";
  Node list(Node::Type::List);
  /*
  list.add(Node::create(123l));
  list.add(Node::create("hello"));
  list.add(Node::create("world"));
  cout << "list: " << list._to_str() << "\n";


  Node tm2(Node::Type::Map);
  cout << "\ntm2: " <<  tm2 << "\n";
  vector<string> p = {"hello", "world"};
  tm2.extend(p, true);
  cout << "tm2: " <<  tm2 << "\n";
  */
}
