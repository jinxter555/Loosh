#include "atom.hh"
#include "scope.hh"

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"




using namespace  std;
namespace Loosh 
{

Scope::Scope() : Environment() {
  auto arg = Node::create(Node::Type::IMap);
  auto immute = Node::create(Node::Type::IMap);
  auto table = Node::create(Node::Type::IMap);
  auto retv = Node::create();

  m_arg = arg.get();
  m_immute = immute.get();
  m_table = table.get();
  m_retv = retv.get();

  atom_add(Atom::arg, move(arg));
  atom_add(Atom::immute, move(immute));
  atom_add(Atom::table, move(table));
  atom_add(Atom::retv, move(retv));

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
  auto idx_status = symbols->add_or_lookup(name);
  //auto index =
  m_vector_array->set(idx_status.second->_get_unsigned_integer(), move(value));
}
Node::OpStatus Scope::lookup(const string&name) {
  auto idx_status = symbols->lookup(name);
  if(idx_status.first) {
  auto vptr = (*m_vector_array)[idx_status.second->_get_unsigned_integer()];

  //return {true, (*m_vector_array)[idx_status.second->_get_unsigned_integer()].get()};

  }

}

//------------------------------------------------------------------------ 

}
