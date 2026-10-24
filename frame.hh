
#pragma once
#include "defs.hh"
#include "environment.hh"
#include "scope.hh"


using namespace  std;
namespace Loosh 
{
class Frame : public Environment {
public :
  enum Index {Immute, Arg, Var, count};

  Frame();
  static unique_ptr<Node> create() ;



  //Node::OpStatus push_scope();
  ptr_R push_scope();
  void pop_scope();
  UnsignedInteger scope_size() const;

};

}