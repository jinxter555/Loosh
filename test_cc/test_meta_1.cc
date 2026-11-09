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


  unique_ptr<Meta> m1 = Meta::create();
  cout << "m1:\n" << m1->_to_str() << "\n";

  m1->atom_add(Atom::noop, Node::create("noop operation atom"));
  m1->atom_add(Atom::line, Node::create(111));
  m1->atom_add(Atom::col, Node::create(777));
  cout << "m1:\n" << m1->_to_str() << "\n";

  m1->data_add("noop", Node::create("noop operation data"));
  m1->data_add("line", Node::create(112));
  m1->data_add("col", Node::create(778));
  cout << "m1:\n" << m1->_to_str() << "\n";

  m1->info_add(Atom::noop, Node::create("noop operation info"));
  m1->info_add(Atom::line, Node::create(113));
  m1->info_add(Atom::col, Node::create(779));
  cout << "m1:\n" << m1->_to_str() << "\n";

  m1->array_push_back(Node::create(3.14159));
  m1->array_push_back(Node::create("hello"));
  m1->array_push_back(Node::create("world"));
  m1->array_push_back(Node::create("axis"));
  cout << "m1:\n" << m1->_to_str() << "\n";

  m1->array_push_front(Node::create("mundi"));
  cout << "m1:\n" << m1->_to_str() << "\n";
  cout << "m1->array_back():\n" << m1->array_back() << "\n";
  cout << "m1->array_front():\n" << m1->array_front() << "\n";
  cout << "m1->array_get(1):\n" << m1->array_get(1) << "\n";
  auto m1_pf = m1->array_pop_front();
  cout << "m1->array_pop_front:\n" << m1->_to_str() << "\n";
  cout << "m1_pf: " << m1_pf << "\n\n";

  auto m2_pb = m1->array_pop_back();
  cout << "m1->array_pop_back:\n" << m1->_to_str() << "\n";
  cout << "m2_pb: " << m2_pb << "\n";

  /* -- this won't work since Meta obj use cc_vec to store Index::AtomMap
  auto m2 = Meta::create();
  m2->add(Atom::noop, Node::create("noop operation m2"));
  m2->add(Atom::line, Node::create(2345));
  m2->add(Atom::col, Node::create(888));
  cout << "meta: m2 add: " << m2->_to_str() << "\n\n";
  */
}
