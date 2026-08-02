#include "environment.hh"

using namespace  std;
namespace Loosh 
{

Scope::Scope(const Node& scope_node) : scope(scope_node._get_ptr_r()) {}


Scope::Scope(Node* parent) : parent_env_ptr(parent) {


}
Node::ptr_U Scope::create() {
  auto  scope_uptr  = make_unique<Node>(Node::Type::Map);
  scope_uptr->add("table", make_unique<Node>(Node::Type::Map));
  scope_uptr->add("parent", nullptr);
  return scope_uptr;

}

Node::OpStatusRef Scope::lookup(const string&name) {
  /*
  try {
    auto table = table_ptr->_get_map_ref();
    auto it = table.find(name);
  } catch(bad_typeid) {

  }*/
 return {false, node_null};

}

}