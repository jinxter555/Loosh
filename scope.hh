#pragma once
#include "symbols.hh"
#include "environment.hh"
#include "defs.hh"



using namespace  std;
namespace Loosh 
{
class Scope : public Environment {
private:
public :
  Node *m_table, *m_immute, *m_arg, *m_retv ;
  Symbols* m_symbols;
  enum Index {Immute, Arg, Var, RetV, count};

  Scope();                        // kernel scope
  Scope(Symbols*);
  static unique_ptr<Scope> create(ptr_R parent_node=nullptr) ;
  unique_ptr<Scope> create_child() ;

  Node::OpStatus table_add(const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(const string&name, Node::ptr_U) ;

  Node::OpStatus table_add(UnsignedInteger atom_name, Node::ptr_U) ;
  Node::OpStatus immute_add(UnsignedInteger atom_name, Node::ptr_U) ;
  Node::OpStatus arg_add(UnsignedInteger atom_name, Node::ptr_U) ;
  
  void  add(const string&name, ptr_U value);
  Node::OpStatus lookup(const string&name);

  Symbols* get_symbols();
/*
  OpStatus add_or_lookup(const string&name) override;
  OpStatus lookup(const string&name) override;
  Lookup_t add(const string&name) override;
  Lookup_t set(const string&name) override;
*/


};

}