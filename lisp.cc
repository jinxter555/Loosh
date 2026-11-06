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


Node::OpStatus Lisp::eval(Node* process, Node* node) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)

  Node *code= node;

  switch(code->m_type) {
  case Node::Type::Token: {
    code = code->value();
    auto ret_status = eval(process, code);
    if(!ret_status.first) {
      cerr << "eval token error:" << node->_to_str() << "\n";
      return ret_status;
    }
    return  ret_status;}
  case Node::Type::Vector: {
    auto &cc_vec = node->_get_vector_ref();
    eval(process, cc_vec);
  }
  case Node::Type::Integer: {
    cout << "integer: " <<  code->_get_integer() << "\n";
    return {true, Node::create(code->_get_integer())};
  }
  case Node::Type::Op: {
    cout << "123op: " <<  code->_to_str() << "\n";
    return {true, Node::create(true)};
  }
  default: {}}
  return {false, Node::create()};
}

Node::OpStatus Lisp::eval(Node* process, Node::Vector& cc_vec_code){
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  auto vptr =  cc_vec_code[0].get();
  auto op_node_result = eval(process, vptr);
  /*
  //auto op_node_status = eval(process, op_node);
  if(!op_node_status.first ) {
    cerr << "eval token error:" << op_node->_to_str() << "\n";
    return op_node_status;

  }
  //auto op = 
  //switch(op_node->)
*/
}




};