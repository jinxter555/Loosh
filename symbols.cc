#include "node.hh"
#include "defs.hh"
#include "symbols.hh"

//#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"
#include "atom.hh"


using namespace std;
namespace Loosh {

Symbols::Symbols() : Meta() {
  m_cc_class->set_value_type(Atom::symbols, Node::Type::Atom);
  add(LOOSH_SYMBOLS);
}

Node::Lookup_t Symbols::add(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  UnsignedInteger symbol_index = m_vector_array->_size();
  m_vector_array->push_back(Node::create(name));
  m_string_map->add(name, Node::create(symbol_index));
  return symbol_index;

}

Node::OpStatus Symbols::lookup(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_string_map->_has_key(name)) {
    auto idx = (*m_string_map)[name].second._get_unsigned_integer();
    return {true, Node::create(idx)};
  } else {
    return {false, Node::create()};
  }

}

Node::OpStatus Symbols::add_or_lookup(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_string_map->_has_key(name)) {
    auto idx = (*m_string_map)[name].second._get_unsigned_integer();
    return {true, Node::create(idx)};
  } else {
    UnsignedInteger symbol_index = m_vector_array->_size();
    m_string_map->add(name, Node::create(symbol_index));
    return {true,  Node::create(symbol_index)};
  }

}

unique_ptr<Symbols> Symbols::create() { return make_unique<Symbols>(); }

}
