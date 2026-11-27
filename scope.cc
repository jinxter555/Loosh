#include "defs.hh"
#include "atom.hh"
#include "scope.hh"

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"




using namespace  std;
namespace Loosh 
{

Scope::Scope() : Environment() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  auto arg = Node::create(Node::Type::Set);
  auto immute = Node::create(Node::Type::Set);
  auto table = Node::create(Node::Type::Set);

  auto symbols = Symbols::create();

  m_arg = arg.get();
  m_immute = immute.get();
  m_table = table.get();

  atom_add(Atom::arg, move(arg));
  atom_add(Atom::immute, move(immute));
  atom_add(Atom::table, move(table));

  if(symbols->_size() > LOOSH_SYMBOLS_RESERVE_COUNT) {
    m_vector_array->resize(symbols->_size());
  }else {
    m_vector_array->resize(LOOSH_SYMBOLS_RESERVE_COUNT);
  }
  m_symbols = symbols.get();
  m_vector_array[0] = move(symbols);

}

Scope::Scope(Symbols *symbols) : Environment(), m_symbols(symbols) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  if(symbols->_size() > LOOSH_SYMBOLS_RESERVE_COUNT) {
    m_vector_array->resize(symbols->_size());
  }else {
    m_vector_array->resize(LOOSH_SYMBOLS_RESERVE_COUNT);
  }
  m_vector_array[0] = symbols;
}

unique_ptr<Scope> Scope::create(ptr_R parent_node)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  auto ptr = make_unique<Scope>();
  ptr->set_parent(parent_node);
  return ptr;
}

unique_ptr<Scope> Scope::create_child()  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  return create(this);
}

Node::OpStatus Scope::table_add(const string&name, Node::ptr_U value)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();

  return table_add(Atom::str_to_atom(name), move(value));
}
Node::OpStatus Scope::table_add(UnsignedInteger atom_name, Node::ptr_U value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();

  m_table->set(atom_name, move(value));
  return {true, Node::create()};
}

//------------------------------------------------------------------------ 
void Scope::add(const string& name, Node::ptr_U value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)

  auto idx_status = m_symbols->add_or_lookup(name);

  auto index_sym = idx_status.second->_get_unsigned_integer();
  if(index_sym > m_vector_array->_size()) {
    m_vector_array->push_back(move(value));
  } else {
    m_vector_array->set(index_sym, move(value));
  }
}
Node::OpStatus Scope::lookup(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  auto idx_status = m_symbols->lookup(name);
  if(idx_status.first) {
    auto vptr = (*m_vector_array)[idx_status.second->_get_unsigned_integer()];
    return {true, Node::create(&vptr.second)}; //return {true, vptr.second.clone()};
  }
  return  {false, Node::create()};

}

//------------------------------------------------------------------------ 

Symbols* Scope::get_symbols() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)

  auto symbols_ref_status = (*m_vector_array)[0];
  if(!symbols_ref_status.first) {
    throw runtime_error("scope symbols");
  }
  //auto symbols = dynamic_cast<Symbols*>(symbols_ref_status.second._get_ptr_r());
  //return symbols;
  return dynamic_cast<Symbols*>(symbols_ref_status.second._get_ptr_r());

}



}
