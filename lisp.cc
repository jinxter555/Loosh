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
    return  ret_status;
  }

  }
  return {false, Node::create()};

}

};