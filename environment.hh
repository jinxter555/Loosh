#include "node.hh"

using namespace  std;
namespace Loosh 
{

class Environment {
public:
  virtual ~Environment() = default;
  virtual Node::OpStatusRef lookup(const string&name) = 0;
  virtual void define(const string&name, Node::ptr_U) = 0;

};

// this is an Scope interface to Node
class Scope : public Environment {
private:
  Node* scope;
  Node* table_ptr;
  Node* parent_env_ptr;
public:
  Scope(Node* parent);
  Scope(const Node& scope);
  Node::ptr_U create();
  Node::OpStatusRef lookup(const string&name) ;
  void add(const string&name, Node::ptr_U) ;
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