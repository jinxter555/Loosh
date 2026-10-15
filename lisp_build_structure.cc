#include <iostream>
#include "node.hh"
#include "lisp.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


namespace Loosh 
{
//------------------------------------------------------------------------ build and parse interpreter 

// tokens: double linked list of tokens
Node::OpStatus Lisp::parse_build(Node& tokens) {
  MYLOGGER(trace_function, "Lisp::parse(Node&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + tokens._to_str(), SLOG_FUNC_INFO+30);
  //cout << "parse tokens: " <<  tokens << "\n\n";

  if(tokens.m_type != Node::Type::List) 
    return {true, tokens.clone()};
  if(tokens.empty_container())
    return {true, Node::create(Node::Type::Vector) };

  //cout << "tokens: " <<  tokens<< "\n";
  auto head_status = tokens.pop_front(); 
  //cout << "parse(token): head_status: " <<  head_status << "\n";
  //cout << "head_status.second value: " <<  *head_status.second << "\n";
  //cout << "tokens: " <<  tokens<< "\n";


  if(!head_status.first) {
    cerr << "head_status error from front(): " <<  head_status << "\n";
    return head_status;
  }
  // have to check m_type
  auto &list = get<Node::List>(tokens.m_value);


  if(head_status.second->m_type == Node::Type::LispOp) {

    Lisp::Op op_head = get<Lisp::Op>(head_status.second->m_value);
    MYLOGGER_MSG(trace_function, string("LispOp: ") + Lisp::_to_str(op_head), SLOG_FUNC_INFO+30);

    switch(op_head) {
    case Lisp::Op::use:  { return use_at_parse_build(list); }
    case Lisp::Op::cc_deque:  { return build_parsed_deque(list); }
    case Lisp::Op::cc_list:  { return build_parsed_list(list); }
    case Lisp::Op::cc_vector:  { return build_parsed_vector(list);}
    case Lisp::Op::pipe:  { return build_parsed_pipe(list); }
    case Lisp::Op::def: { return build_parsed_def(list); }
    case Lisp::Op::if_: { return build_parsed_if(list); }
    case Lisp::Op::defmacro: { return build_parsed_macro(list); }
    case Lisp::Op::module_: { return build_parsed_module(list); }
    case Lisp::Op::class_: { return build_parsed_class(list); }
    case Lisp::Op::alias: { return build_parsed_alias(list); }
 // case Lisp::Op::root: { return build_parsed_root(list); }
 // case Lisp::Op::defun: { return build_parsed_fun(list); }
    default: {}
    }
  } 
  // convert it to a vector and return it
  // if(head_status.second->m_type == Node::Type::Identifier) 

  list.push_front(move(head_status.second));
  return build_parsed_vector(list);

}

}