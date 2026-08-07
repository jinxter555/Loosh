#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh {


//------------------------------ meta add,set 
Node::OpStatus Node::obj_meta_add(const string&meta_key, const string&key, unique_ptr<Node> child) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(type_ != Type::ObjectMeta) 
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
  if(type_ != Type::ObjectMeta) 
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
  if(type_ != Type::ObjectMeta)  {
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







}