#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"
using namespace std;
namespace Loosh {

NodeObject::NodeObject() : Node(Type::Map) {
  add(LOOSH_OBJ_INFO, Node::create(Node::Type::Map));
  add(LOOSH_OBJ_DATA, Node::create(Node::Type::Map));

//  auto v = map[OBJ_INFO];

}


//------------------------------ set
Node::OpStatus NodeObject::info_add(const string&key, unique_ptr<Node> child) {

  /*
  auto ref_status  = get_node(LOOSH_OBJ_INFO);
  if(!ref_status.first) {
    return {false, Node::create_error(Error::Type::KeyNotFound, "ObjInfo: "  LOOSH_OBJ_INFO  "not found")};
  }
  auto &obj_info_map = ref_status.second._get_map_ref();
  */ 
  auto &obj_info_map = _get_map_ref(key);
  if(!obj_info_map.try_emplace(key, move(child)).second) {
    return {false, create_error(Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }
  return {true, Node::create(true)};

}

//------------------------------ set
Node::OpStatus NodeObject::info_set(const string&key, unique_ptr<Node> child) {

  auto ref_status  = get_node(LOOSH_OBJ_INFO);
  if(!ref_status.first) {
    return {false, Node::create_error(Error::Type::KeyNotFound, "ObjInfo: "  LOOSH_OBJ_INFO  "not found")};
  }
  auto &obj_info_map = ref_status.second._get_map_ref();


  obj_info_map[key] = move(child);

  return {true, Node::create(true)};

}

string NodeObject::_to_str() const  {
  return Node::_to_str();
}







}