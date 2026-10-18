#pragma once
#include "defs.hh"
#include "environment.hh"


using namespace  std;
namespace Loosh 
{
class Scope : public Environment {
private:
  Node *m_var, *m_immute, *m_arg ;
public :
  enum Index {Immute, Arg, Var, count};

  Scope();
  static unique_ptr<Scope> create(Node &frame) ;

  Node::OpStatus var_add(Node& table, const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(Node& table, const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(Node& table, const string&name, Node::ptr_U) ;

};

}