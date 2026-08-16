#include "node.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh {


//------------------------------ meta add,set 
Node::OpStatus Node::obj_meta_add(const string&meta_key, const string&key, unique_ptr<Node> child) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(type_ != Type::MetaObject) 
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, "Not a Type::ObjectMeta.")};

  auto map_ptr_r = &_get_map_ref();
  auto &meta_ptr_u  = (*map_ptr_r)[meta_key];


  if(!meta_ptr_u->add(key, move(child)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";

  return {true, Node::create(true)};
}

Node::OpStatus Node::obj_meta_set(const string&meta_key, const string&key, unique_ptr<Node> child) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(type_ != Type::MetaObject) 
    return {false, Node::create_error(Error::Type::IndexWrongType, "Not a Type::ObjectMeta.")};

  auto map_ptr_r = &_get_map_ref();
  auto &meta_ptr_u  = (*map_ptr_r)[meta_key];


  if(!meta_ptr_u->set(key, move(child)).second) {
    return {false, Node::create_error(Error::Type::Unknown, "Can't set in object info")};
  }
  return {true, Node::create(true)};
}

Node::OpStatus Node::obj_meta_get(const string&meta_key, const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(type_ != Type::MetaObject)  {
    return {false, Node::create_error(Error::Type::IndexWrongType, "Not a Type::ObjectMeta.")};
  }

  auto map_ptr_r = &_get_map_ref();
  auto &meta_ptr_u  = (*map_ptr_r)[meta_key];

  auto meta_val_ref_status =  meta_ptr_u->get_node(key);

  if(!meta_val_ref_status.first){
    cerr << "value_: " << _to_str() << "\n";
    auto msg = "meta: " + meta_key + ", key: "  + key + " not found!\n";
    spdlog::error(clean_function_name() + ": " +  msg);
    MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    return {false, Node::create_error(Error::Type::KeyNotFound, msg)};

  }

  auto ptr = &meta_val_ref_status.second;
  return {true, create(ptr)};

}


//------------------------------ info add,set 
Node::OpStatus Node::obj_info_add(const string&key, unique_ptr<Node> child) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_add(LOOSH_OBJ_INFO, key, move(child));
}

Node::OpStatus Node::obj_info_set(const string&key, unique_ptr<Node> child) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_set(LOOSH_OBJ_INFO, key, move(child));
}

Node::OpStatus Node::obj_info_get(const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_get(LOOSH_OBJ_INFO, key);
}

//------------------------------ data add,set 
Node::OpStatus Node::obj_data_add(const string&key, unique_ptr<Node> child) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_add(LOOSH_OBJ_DATA, key, move(child));

}

Node::OpStatus Node::obj_data_set(const string&key, unique_ptr<Node> child) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_set(LOOSH_OBJ_DATA, key, move(child));
}

Node::OpStatus Node::obj_data_get(const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return obj_meta_get(LOOSH_OBJ_DATA, key);
}

//------------------------------ meta object  info
Node::Atom Node::_get_meta_type(Node* env_ptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto &env_node = env_ptr->get_node();
  if(env_node.type_ != Node::Type::MetaObject) {
    string msg =  "Env: "  + env_ptr->_to_str() + "Not a Meta Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }
  auto meta_node_type = env_node.obj_info_get(LOOSH_CC_OBJ_TYPE);
  cout << clean_function_name() +  ": env_node " <<  env_node << "\n\n";
  cout << clean_function_name() +  ": meta node_type .second " <<  meta_node_type.second->get_node() << "\n";
  return meta_node_type.second->get_node()._get_atom();

  //cout << clean_function_name() +  ": obj info status second " <<  obj_info_status.second->get_node(LOOSH_CC_OBJ_TYPE).second._to_str() << "\n";

}


}