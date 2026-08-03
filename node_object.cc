#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"
using namespace std;
namespace Loosh {

NodeObject::NodeObject() :
  obj_ptr_u(make_unique<Node>(Node::Type::Map)) {

  obj_ptr_u->add(LOOSH_OBJ_INFO, Node::create(Node::Type::Map));
  obj_ptr_u->add(LOOSH_OBJ_DATA, Node::create(Node::Type::Map));

  obj_ptr_r = obj_ptr_u.get();
  info_ptr_r = &obj_ptr_u->_get_map_ref(LOOSH_OBJ_INFO);
  data_ptr_r = &obj_ptr_u->_get_map_ref(LOOSH_OBJ_INFO);

}

//------------------------------ ptr 
Node::OpStatus NodeObject::ptr_add(Node::Map *ptr, const string&key, unique_ptr<Node> child) {
  if(!ptr->try_emplace(key, move(child)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }
  return {true, Node::create(true)};
}
Node::OpStatus NodeObject::ptr_set(Node::Map *ptr, const string&key, unique_ptr<Node> child) {
  (*ptr)[key] = move(child);
  return {true, Node::create(true)};
}

//------------------------------ set
Node::OpStatus NodeObject::info_add(const string&key, unique_ptr<Node> child) { 
  return ptr_add(info_ptr_r, key, move(child)); }

Node::OpStatus NodeObject::info_set(const string&key, unique_ptr<Node> child) {
  return ptr_set(info_ptr_r, key, move(child)); }

string NodeObject::_to_str() const  {
  return obj_ptr_r->_to_str();
}







}