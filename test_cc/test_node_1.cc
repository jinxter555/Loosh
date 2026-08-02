#include <cassert>
#include <catch2/catch_all.hpp>


#include "../node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
using namespace Loosh;
  



TEST_CASE("check node 2") {
    Node::Error::init();


  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);

  Node tm4(Node::Type::Map);

  Node::Map &m4 = tm4._get_map_ref();
  cout << "m4: " << Node::_to_str( m4) << "\n";


//  SECTION("l1._get_map_ref() throw::bad_type_id") {
//    REQUIRE_THROWS_AS(l1._get_map_ref(), std::bad_typeid);
//  }
  SECTION("tm4._add() throw::bad_type_id") {
    REQUIRE_THROWS_AS(tm4.add(Node::create(1234l)), std::bad_typeid);
  }

  NodeObject tm5;
  tm5.info_add("class_name", Node::create("MyClass"));
  tm5.info_add("class_ptr", Node::create());
  tm5.info_add("object_count", Node::create(555));
  cout << "tm5: " <<  tm5 << "\n";
  





//  tm2.extend(p, true);
}
