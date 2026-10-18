#include "scope.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



using namespace  std;
namespace Loosh 
{

Scope::Scope() {}

unique_ptr<Scope> Scope::create(Node& frame)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  Node::Vector cc_vec(Index::count); 

  auto scope = make_unique<Scope>();

  cc_vec[Index::Arg] = Node::create(Node::Type::IMap);
  cc_vec[Index::Immute] = Node::create(Node::Type::IMap);
  cc_vec[Index::Var] = Node::create(Node::Type::IMap);

  scope->m_arg =   cc_vec[Index::Arg].get();
  scope->m_immute =   cc_vec[Index::Immute].get();
  scope->m_var =   cc_vec[Index::Var].get();

  frame.push_back(Node::create(move(cc_vec)));
  return scope;
}

}
