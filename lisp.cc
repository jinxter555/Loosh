#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include "lisp_reader.hh"
#include "tree.hh"
#include <iostream>
#include "atom.hh"



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
  default: {}}
  return {false, Node::create()};
}

Node::OpStatus Lisp::eval(Node* process, Node::Vector& cc_vec_code){
  auto op_node = cc_vec_code[0].get();
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