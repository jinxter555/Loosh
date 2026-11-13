#include "atom.hh"
#include "scope.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"




using namespace  std;
namespace Loosh 
{

Scope::Scope() : Environment() {
  auto arg = Node::create(Node::Type::IMap);
  auto immute = Node::create(Node::Type::IMap);
  auto var = Node::create(Node::Type::IMap);
  auto retv = Node::create();

  m_arg = arg.get();
  m_immute = immute.get();
  m_var = var.get();
  m_retv = retv.get();

  atom_add(Atom::arg, move(arg));
  atom_add(Atom::immute, move(immute));
  atom_add(Atom::var, move(var));
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

}
