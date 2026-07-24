#include "node.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;
namespace Loosh 
{

// private has to be call from Map handling functions
// get and extend node by key
Node* Node::extend_map_by_key(Map& map,  const string&key, bool create) { 
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, string("key: ") + key, SLOG_NODE_OP+30);

  if (map.find(key) != map.end()) return map[key].get(); // key found
  if(!create) return nullptr; // don't create
  Map new_map={};
  map[key] = Node::create(move(new_map));
  return map[key].get();
}


Node::OpStatus Node::set(const vector<string>&path, unique_ptr<Node>child, bool override) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, "path: " + _to_str_ext(path), SLOG_FUNC_INFO+30);

  Node* node_ptr=this;
  for(auto key : path) {
    try { 
      auto &map = get<Map>(node_ptr->value_);
      node_ptr = extend_map_by_key(map, key, override);
    } catch (...) {
      if(!override) return {false, Node::create(false)};
    }
    if(node_ptr==nullptr) return {false, Node::create(false)};
  }
  /*
  auto status_empty = node_ptr->empty();
  if(!status_empty.first) { // operation success or not , not = not map
    if(!override) return status_empty;
  }*/
  // operation is good, current node_ptr is a map
  if(!override) return {false, create(false)};


  node_ptr->set(move(child));
  return {true, Node::create(true)};
}

Node::OpStatusRef Node::get_node(const string&key) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, string("key: ") + key, SLOG_NODE_OP+30)

  switch(type_) {
  case Type::Raw: {
    auto sptr = get<ptr_R>(value_);
    return sptr->get_node(key); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(value_);
    return sptr->get_node(key); }
  default: {}
  }


  if(type_ != Type::Map){
    return {false, Error::ref(Error::Type::IndexWrongType, 
    "get_node(string&key) only works Map nodes. Current type: " + _to_str(type_))};
  }
  Node::Map& map = get<Node::Map>(value_);
  auto it = map.find(key);
  if(it==map.end()) {
    string msg = "key '" + key + "' not found in map.";
    return {false, Error::ref(Error::Type::KeyNotFound, msg)};
  }

  return {true, *it->second.get()};
}



}


