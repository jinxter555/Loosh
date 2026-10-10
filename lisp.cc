#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include "environment.hh"
#include <iostream>



namespace Loosh 
{

Lisp::Lisp(Environment&env): Lang(env.universal.get_root()), m_root(env.universal.get_root()) {
  m_root = env.universal.get_root();
  auto lisp = m_root->create_meta();
  m_lang->obj_data_add(LOOSH_LISP, move(lisp));
}

};