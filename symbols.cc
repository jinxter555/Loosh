#include "node.hh"

//#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"
#include "atom.hh"


using namespace std;
namespace Loosh {

Symbols::Symbols() : Node(create_vec()) {
  m_type=Node::Type::Symbols;
}

/*
Meta::Meta(Node::Type t)  : Node(t) {
  if(t==Node::Type::Meta ) {
    m_value = create_vec();
    return;
  }
}
*/
Node::Vector Symbols::create_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  //MetaObject cc_vec(ObjectIndex::count);
  Vector cc_vec(Index::count);

//  cc_vec[Index::ValueArray] = Node::create(Node::Type::Vector);
//  cc_vec[Index::ValueArray]->reserve(SYMBOLS_RESERVE_COUNT);

  cc_vec[Index::NameArray] = Node::create(Node::Type::Vector);
  cc_vec[Index::NameArray]->reserve(SYMBOLS_RESERVE_COUNT);

  cc_vec[Index::NameMap] = Node::create(Node::Type::Map);

  return cc_vec;
}

Node::Lookup_t Symbols::add(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto &cc_vec = _get_vector_ref();
  auto &name_array = cc_vec[Index::NameArray];
  UnsignedInteger symbol_index = name_array->_size();

  auto &name_map = cc_vec[Index::NameMap];

  name_map->add(name, Node::create(symbol_index));
  return symbol_index;

}
Node::OpStatus Symbols::add_or_lookup(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto &cc_vec = _get_vector_ref();
  auto &name_array = cc_vec[Index::NameArray];
  auto &name_map = cc_vec[Index::NameMap];
  if(name_map->_has_key(name)) {
    auto idx = (*name_map)[name].second._get_unsigned_integer();
    return {true, Node::create(idx)};
  } else {
    UnsignedInteger symbol_index = name_array->_size();
    name_map->add(name, Node::create(symbol_index));
    return {true,  Node::create(symbol_index)};
  }

}

unique_ptr<Symbols> Symbols::create() {
  return make_unique<Symbols>();

}

}
