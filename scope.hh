#pragma once
#include "environment.hh"
#include "defs.hh"



using namespace  std;
namespace Loosh 
{
class Scope : public Environment {
private:
public :
  Node *m_table, *m_immute, *m_arg, *m_retv ;
  enum Index {Immute, Arg, Var, RetV, count};

  Scope();
  static unique_ptr<Scope> create(ptr_R parent_node=nullptr) ;
  unique_ptr<Scope> create_child() ;

  Node::OpStatus table_add(const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(const string&name, Node::ptr_U) ;

  Node::OpStatus table_add(UnsignedInteger atom_name, Node::ptr_U) ;
  Node::OpStatus immute_add(UnsignedInteger atom_name, Node::ptr_U) ;
  Node::OpStatus arg_add(UnsignedInteger atom_name, Node::ptr_U) ;
  

};

}