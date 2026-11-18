#include "node.hh"
#include "my_helpers.hh"

#include "atom.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC

#include "scope_logger.hh"
#include "color_esc.hh"

using namespace std;
namespace Loosh 
{




Node::Set& Node::_get_set_ref() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->_get_set_ref(); }
  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->_get_set_ref(); }
  case Type::SimpleObject:
  case Type::Set:  {
    return get<Set>(m_value);}
  default: {}}

  auto msg =  "Not a Node::Set, Node::m_type " + _to_str(m_type) + ", Node::m_value " +  _to_str() ;
  spdlog::error(clean_function_name() + ": " +  msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();
  

}



}