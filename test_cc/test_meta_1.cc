//#include <cassert>
#include <catch2/catch_all.hpp>


#include "../node.hh"
#include "../atom.hh"


#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

#include "../node_tmpl_cc.hh"


#include "../interactive.hh"
std::fstream trace_function("trace.log", std::ios::out);
Loosh::Interactive *it_ptr;

using namespace  std;
using namespace Loosh;
  



TEST_CASE("check meta 1") {
  Node::Error::init();


  //ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  ScopeLogger::set_current_verbose_level(SLOG_NODE_OP);

  auto a1 = Node::create(Node::Type::IMap);
  
  
  a1->add(Atom::noop, Node::create("noop operation"));
  a1->add(Atom::line, Node::create(123));
  a1->add(Atom::col, Node::create(555));
  cout << "a1: " << a1->_to_str() << "\n\n";

  /*
  unique_ptr<Meta> m1 = Meta::create();
  cout << "m1: " << m1->_to_str() << "\n";

  m1->atom_add(Atom::noop, Node::create("noop operation"));
  m1->atom_add(Atom::line, Node::create(123));
  m1->atom_add(Atom::col, Node::create(555));
  cout << "m1: " << m1->_to_str() << "\n";
*/


}
