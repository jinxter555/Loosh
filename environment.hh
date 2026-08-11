#include "node.hh"

using namespace  std;
namespace Loosh 
{

class Environment : public Node {
public:
  Environment(Node::Type t) ;
  virtual ~Environment() = default;
  virtual Node::OpStatusRef lookup(const string&name) = 0;
//  virtual Node::OpStatusRef add(const string&name, Node::ptr_U) = 0;
  static OpStatusRef lookup(Map& table, const string& name);

  Node::OpStatus var_add(Map& table, const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(const string&name, Node::ptr_U) ;
  Node::OpStatus var_set(const string&name, Node::ptr_U) ;
  Node::OpStatus arg_set(const string&name, Node::ptr_U) ;

  virtual Environment& meta_map_obj(Node* meta_obj)=0;

  //virtual Node::OpStatus meta_obj_get();
};

// this is an Scope interface to Node
class Scope : public Environment {
private:
  Node::Map* scope_map_ptr_r=nullptr;
  Node* table_ptr_r=nullptr;
  Node* parent_ptr_r=nullptr;
  bool moved=false;
public:
  Scope(Node* parent);
  Scope();
  Scope(Node* meta_obj, bool use_meta);

  OpStatus move_ptr_u();

  ptr_U create_child();
  bool meta_map(Node* ptr); // map a meta object to a scope 

  Node::OpStatusRef lookup(const string&name) ;
  //Node::OpStatus add(const string&name, Node::ptr_U) ;
  Node::OpStatus var_add(const string&name, Node::ptr_U) ;
  Node::OpStatus immute_add(const string&name, Node::ptr_U) ;
  Node::OpStatus arg_add(const string&name, Node::ptr_U) ;
  Node::OpStatus meta_obj_get();

  static ptr_U meta_create(Node* parent=nullptr);
  //Scope& meta_map_obj(Node* meta_obj);
  void print();
};

class Frame : public Environment {
private:
  Node* fun;
  Node* scopes_ptr_r=nullptr; // vector of scopes
public:
  Frame(Node* parent);
  Frame();
  Frame& meta_map_obj(Node* meta_obj);


};

class Process : public Environment {
private:
  Node::Integer pid;
  Node* call_stack;

};

}