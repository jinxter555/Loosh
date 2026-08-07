#include "node.hh"

using namespace  std;
namespace Loosh 
{

class Environment : public Node {
public:
  Environment(Node::Type t) ;
  virtual ~Environment() = default;
  virtual Node::OpStatusRef lookup(const string&name) = 0;
  virtual Node::OpStatusRef add(const string&name, Node::ptr_U) = 0;

};

// this is an Scope interface to Node
class Scope : public Environment {
private:
  Node::Map* scope_map_ptr_r=nullptr;
  Node* table_ptr_r=nullptr;
  Node* parent_ptr_r=nullptr;
public:
  Scope(Node* parent);
  Scope();
  Node::OpStatusRef lookup(const string&name) ;
  Node::OpStatusRef add(const string&name, Node::ptr_U) ;
  void print();
};

class Frame : public Environment {
private:
  Node* fun;
  Node* local_scope;
public:


};

class Process : public Environment {
private:
  Node::Integer pid;
  Node* call_stack;

};

}