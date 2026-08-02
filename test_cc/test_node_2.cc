#include <spdlog/spdlog.h>
#include <cassert>
#include <catch2/catch_all.hpp>



#include "../node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"



using namespace  std;
using namespace Loosh;
  



TEST_CASE("node") {
  Node::Error::init();
  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  spdlog::set_pattern("%^[%l]%$ %v");

  SECTION("simple node test") {

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
    CHECK( (n2_ptr.get_node() == n3_ptr.get_node())._get_bool() ); 
  
  
  
  
  
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
  
  
  
    Node tm2(Node::Type::Map);
    tm2.add("hello", Node::create("world"));
    tm2.add("value", Node::create(555l));
    CHECK(tm2["hello"].second._to_str() =="world"); 
    CHECK(tm2["value"].second._get_integer() ==555l); 
    cout << "\ntm2: " <<  tm2 << "\n";
  
    Node tm3(Node::Type::Map);
    vector<string> br3_key = {"branch1", "branch2"};
    tm3.set(br3_key, Node::create(777l), true);
    auto tm3_node_status_ref = tm3.get_node(br3_key);
    CHECK(tm3_node_status_ref.first);
    cout << "tm3_node_status_ref: " << tm3_node_status_ref << "\n";
  }
  
  
  
  
  SECTION("tm4.pushfront() throw::bad_type_id") {
    Node tm3(Node::Type::Map);
    vector<string> br3_key = {"branch3", "branch3b"};
    tm3.set(br3_key, Node::create(777l), true);
    auto tm3_node_status_ref = tm3.get_node(br3_key);
    CHECK(tm3_node_status_ref.first);
    cout << "tm3_node_status_ref: " << tm3_node_status_ref << "\n";
    REQUIRE_THROWS_AS(tm3.push_front(Node::create(5555l)), std::bad_typeid);
  }
}

TEST_CASE("list") {
  Node::Error::init();
  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  Node l1(Node::Type::List);
  l1.add(Node::create(123l));
  l1.add(Node::create("hello"));
  l1.add(Node::create("world"));
  cout << "l1: " << l1._to_str() << "\n";


  SECTION("l1._get_map_ref() throw::bad_type_id") {
    REQUIRE_THROWS_AS(l1._get_map_ref(), std::bad_typeid);
  }
}

TEST_CASE("map") {
  Node::Error::init();
  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);


  Node tm4(Node::Type::Map);
  vector<string> br4_key = {"branch4", "branch4b"};

  tm4.set(br4_key, Node::create(777l), true);
  Node::Map &m4 = tm4._get_map_ref();
  cout << "m4: " << Node::_to_str( m4) << "\n";

  SECTION("tm4.add(Integer) throw::bad_type_id") {
    REQUIRE_THROWS_AS(tm4.add(Node::create(1234l)), bad_typeid);
  }
  SECTION("tm4.add(String) throw::bad_type_id") {
    REQUIRE_THROWS_AS(tm4.add(Node::create("hello")), bad_typeid);
  }
  REQUIRE_THROWS_AS(tm4.push_front(Node::create(5555l)), std::bad_typeid);

}