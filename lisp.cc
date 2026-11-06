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
    cout << "eval token " <<  code._to_str() << "\n";
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
    return {true, Node::create(code._get_integer())};
  }
  case Node::Type::Op: {
    cout << "op: " <<  code._to_str() << "\n";
    return {true, Node::create(true)};
  }
  default: {}}
  return {false, Node::create()};
}

Node::OpStatus Lisp::eval(Node& process, Node::Vector& cc_vec_code, UnsignedInteger start){
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  if(cc_vec_code.size() == 0) return {true, Node::create()};

  auto vptr =  cc_vec_code[start].get();
  auto op_node_status = eval(process, *vptr);
  switch(op_node_status.second->m_type) {

  }
  /*
  //auto op_node_status = eval(process, op_node);
  if(!op_node_status.first ) {
    cerr << "eval token error:" << op_node->_to_str() << "\n";
    return op_node_status;

  }
  //auto op = 
  //switch(op_node->)
*/
  return {true, Node::create(true)};
}




};