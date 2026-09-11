#include "node.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh {

//------------------------------------------------------------------------ obj info add, set, get
//------------------------------  add
Node::OpStatus Node::obj_info_add(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
  }}


  auto &obj = get<VecObject>(m_value);
  auto &obj_info = obj[ObjectIndex::Info]->get_node();

//  cout << "obj_info_add(), value: " << *value << "\n";

  if(!obj_info.add(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

//  cout << "obj_info_add(), obj_info->getnode(key): " << obj_info.get_node(key)  << "\n";
  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}

//------------------------------  set
Node::OpStatus Node::obj_info_set(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }}

  auto &obj = get<VecObject>(m_value);
  auto &obj_info = obj[ObjectIndex::Info]->get_node();

  if(!obj_info.set(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";

  return {true, Node::create(true)};
}


//------------------------------ get
Node::OpStatusRef Node::obj_info_get(const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return{false, 
      Error::ref(Error::Type::InvalidOperation, 
        "Unsupported types for addition! " + _to_str(m_type) + " : " + _to_str(m_type))
    };
  }}

  auto &obj = get<VecObject>(m_value);
  auto &obj_info = obj[ObjectIndex::Info]->get_node();
  return obj_info.get_node(key);
}

//------------------------------------------------------------------------ object data add, set, get
//------------------------------ 
Node::OpStatus Node::obj_data_add(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }}

  auto &obj = get<VecObject>(m_value);
  auto &obj_data = obj[ObjectIndex::Data]->get_node();

  if(!obj_data.add(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}


//------------------------------  set
Node::OpStatus Node::obj_data_set(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }}

  auto &obj = get<VecObject>(m_value);
  auto &obj_data = obj[ObjectIndex::Data]->get_node();

  if(!obj_data.set(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";

  return {true, Node::create(true)};
}

//------------------------------ 
Node::OpStatusRef Node::obj_data_get(const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch (m_type) {
  case Type::MetaObject:
  case Type::SimpleObject:
    break;
  default:{
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return{false, 
      Error::ref(Error::Type::InvalidOperation, 
        "Unsupported types for addition! " + _to_str(m_type) + " : " + _to_str(m_type))
    };
  }}

  auto &obj = get<VecObject>(m_value);
  auto &obj_data = obj[ObjectIndex::Data]->get_node();
  return obj_data.get_node(key);
}

//------------------------------------------------------------------------ 

//------------------------------ 
Node::MetaObject Node::create_meta_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  MetaObject cc_vec(ObjectIndex::count);

  auto info_ptr_u = Node::create(Node::Type::Map);
  cc_vec[ObjectIndex::Info] = Node::create(info_ptr_u.get()); // create pointer to object information

  auto data_ptr_u = Node::create(Node::Type::Map);
  data_ptr_u->add(LOOSH_D_OBJ_INFO,  move(info_ptr_u));

  cc_vec[ObjectIndex::Parent] = nullptr;
  cc_vec[ObjectIndex::Data] = move(data_ptr_u);
  cc_vec[ObjectIndex::Children] = Node::create(Node::Type::Vector);

  return cc_vec;
}
//------------------------------ 

Node::SimpleObject Node::create_simple_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  MetaObject cc_vec(LOOSH_D_SIMPLE_OBJECT_COUNT);

  auto info_ptr_u = Node::create(Node::Type::Map);
  cc_vec[ObjectIndex::Info] = Node::create(info_ptr_u.get()); // create pointer to object information

  //auto &info= cc_vec[ObjectIndex::Info]->unwrap_value<Node>();
  //auto &info= cc_vec[ObjectIndex::Info]->get_node();
  //info.add("hello", create("world"));

  auto data_ptr_u = Node::create(Node::Type::Map);
  data_ptr_u->add(LOOSH_D_OBJ_INFO,  move(info_ptr_u));

  cc_vec[ObjectIndex::Data] = move(data_ptr_u);

  cout << clean_function_name() <<   ": cc_vec: " <<  _to_str( cc_vec) << "\n";

  return cc_vec;
}
}
