#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include "lisp_reader.hh"
#include "tree.hh"
#include <iostream>
#include "atom.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


namespace Loosh 
{


Lisp::Lisp(Tree*t, LispReader&r)
  : Lang(t->get_root()), reader(r) {

  auto lisp = m_root->create_meta();
  m_lisp = lisp.get();

  auto ops = lisp->create(Node::Type::Map);
  m_ops = ops.get();

  m_lisp->obj_atom_add(Atom::ops, move(ops));

  m_lang->obj_atom_add(Atom::lisp, move(lisp));
  set_op_str() ;
}


Node::OpStatus Lisp::eval(Node& process, Node& code) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)


  switch(code.m_type) {
  case Node::Type::Token: {
    //cout << "eval token " <<  code._to_str() << "\n";
    auto value = code.value();
    auto ret_status = eval(process, *value);
    if(!ret_status.first) {
      cerr << "eval token error:" << code._to_str() << "\n";
      return ret_status;
    }
    return  ret_status;}
  case Node::Type::Vector: {
    auto &cc_vec = code._get_vector_ref();
    return eval(process, cc_vec, 0);
  }
  case Node::Type::Integer: {
    cout << "integer: " <<  code._get_integer() << "\n";
    //return {true, Node::create(code._get_integer())};
    break;
  }
  default: {}}
  
  return {true, code.clone()};
  //return {false, Node::create()};
}

Node::OpStatus Lisp::eval(Node& process, Node::Vector& cc_vec, UnsignedInteger start){
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  if(cc_vec.size() == 0) return {true, Node::create()};

  auto op_node_status = eval(process, *cc_vec[start]);

  if(op_node_status.second->m_type != Node::Type::Op) {
    string msg = "first element of list is not a lisp operator  " ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
  }

  switch(op_node_status.second->_get_op()) {
  case Node::Op::add: {
    cout << "op status add: " <<  op_node_status << "\n";
    auto add_result_status = add(process, cc_vec, start+1) ;
    cout << "add result status : " <<  add_result_status << "\n";
    return add_result_status;
  }
  case Node::Op::sub: {
    cout << "op status sub: " <<  op_node_status << "\n";
    //return {true, Node::create(true)};
    break;
  }
  default:{}}


  return {true, Node::create(true)};
}




};