#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include "environment.hh"
#include "lisp_reader.hh"
#include <iostream>



namespace Loosh 
{

Lisp::Lisp(Environment&env, LispReader&r)
  : Lang(env.universal.get_root()), reader(r) {

  auto lisp = m_root->create_meta();
  auto ops = lisp->create(Node::Type::Map);
  m_ops = ops.get();

  m_lang->obj_data_add(LOOSH_LISP, move(lisp));
  lisp->add(LOOSH_LISP_OPS, move(ops));
}

};