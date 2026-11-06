#include <iostream>
#include "lisp.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

namespace Loosh 
{

Node::OpStatus Lisp::add(Node& process, const Vector& cc_vec, UnsignedInteger start) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  unique_ptr<Node> result = make_unique<Node>(0);
  UnsignedInteger s = cc_vec.size();


  for(UnsignedInteger i=start; i <s; i++) {
    auto& element = cc_vec[i];
    auto ev_status = eval(process, *element);
    if(!ev_status.first) {
      cerr << "builtin_add eval() error: " << ev_status.second->_to_str() << "\n";
      return ev_status;
    }
    auto t2 = *result + *ev_status.second;
    result->m_value  = move(t2.m_value);
  }
  return {true, move(result)};
}

Node::OpStatus Lisp::mul(Node& process, const Vector& cc_vec, UnsignedInteger start) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  unique_ptr<Node> result = make_unique<Node>(1);
  UnsignedInteger s = cc_vec.size();


  for(UnsignedInteger i=start; i <s; i++) {
    auto& element = cc_vec[i];
    auto ev_status = eval(process, *element);
    if(!ev_status.first) {
      cerr << "builtin_add eval() error: " << ev_status.second->_to_str() << "\n";
      return ev_status;
    }
    auto t2 = *result * *ev_status.second;
    result->m_value  = move(t2.m_value);
  }
  return {true, move(result)};
}

}