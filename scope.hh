#pragma once
#include "environment.hh"
#include "defs.hh"



using namespace  std;
namespace Loosh 
{
class Scope : public Environment {
private:
  Node *m_var, *m_immute, *m_arg, *m_retv ;
public :
  enum Index {Immute, Arg, Var, RetV, count};

  Scope();
  static unique_ptr<Scope> create(ptr_R parent_node=nullptr) ;
  static unique_ptr<Scope> create(Node &frame) ;
  unique_ptr<Scope> create_child() ;

  Node::OpStatus var_add(Node& table, const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(Node& table, const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(Node& table, const string&name, Node::ptr_U) ;

};

}