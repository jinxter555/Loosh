#include "node.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"


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
  //auto &obj_info = obj[ObjectIndex::Info]->get_node();
  auto &obj_info = obj[ObjectIndex::Info]->unwrap_value<Node>();

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
  auto &obj_data = obj[ObjectIndex::StringMap]->get_node();

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
  auto &obj_data = obj[ObjectIndex::StringMap]->get_node();

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
  auto &obj_data = obj[ObjectIndex::StringMap]->get_node();
  return obj_data.get_node(key);
}

//------------------------------------------------------------------------ 
bool Node::set_parent(ptr_R parent) {
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
    return false;
  }}
  auto &obj = get<VecObject>(m_value);
  obj[ObjectIndex::Parent] = create(parent);
  return true;
  
}


//------------------------------------------------------------------------ 
Node::ptr_U Node::create_meta(ptr_R parent) {
  auto meta = make_unique<Node>(Type::MetaObject);

  if(parent != nullptr && parent->m_type != Type::MetaObject){
    string msg = "Parent Type: " + Node::_to_str(parent->m_type) + " , is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::bad_typeid();
  }
  meta->set_parent(parent);
  return meta;
}

Node::OpStatus Node::create_meta(const string& key) {
  if(m_type != Type::MetaObject){
    string msg = "this is not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, create(false)};
  }

  auto meta = make_unique<Node>(Type::MetaObject);
  meta->set_parent(this);

  obj_data_add(key, move(meta));

  return {true, create(true)};
}


Node::OpStatus Node::create_meta() {
  auto meta = make_unique<Node>(Type::MetaObject);
  meta->set_parent(this);
  return {true, create(true)};

}

//------------------------------------------------------------------------ 
Node::OpStatus Node::get_parent() {
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
    return {false, create(false)};
  }}
  auto &obj = get<VecObject>(m_value);
  auto ptr = obj[ObjectIndex::Parent].get();
  return {true, Node::create(ptr)};

}

//------------------------------------------------------------------------ 

//------------------------------ 
Node::MetaObject Node::create_meta_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  //MetaObject cc_vec(ObjectIndex::count);
  MetaObject cc_vec(ObjectIndex::count);

  auto info_ptr_u = Node::create(Node::Type::IMap);
  auto imap_ptr_u = Node::create(Node::Type::IMap);
  auto vector_ptr_u = Node::create(Node::Type::Vector);

  cc_vec[ObjectIndex::Info] = Node::create(info_ptr_u.get()); // create pointer to object information
  cc_vec[ObjectIndex::IntegerMap] = Node::create(imap_ptr_u.get()); // create pointer to object vector
  cc_vec[ObjectIndex::VectorArray] = Node::create(vector_ptr_u.get()); // create pointer to object vector

  auto data_ptr_u = Node::create(Node::Type::Map);
  data_ptr_u->add(LOOSH_D_OBJ_INFO,  move(info_ptr_u));
  data_ptr_u->add(LOOSH_D_OBJ_IMAP,  move(imap_ptr_u));
  data_ptr_u->add(LOOSH_D_OBJ_VECTOR,  move(vector_ptr_u));

  cc_vec[ObjectIndex::Parent] = nullptr;
  cc_vec[ObjectIndex::StringMap] = move(data_ptr_u);
  cc_vec[ObjectIndex::MetaLock] = Node::create(Node::Type::Lock);
  cc_vec[ObjectIndex::WalkerCount] = Node::create(Node::Type::AtomicInteger);

  return cc_vec;
}
//------------------------------ 

Node::SimpleObject Node::create_simple_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  MetaObject cc_vec(LOOSH_D_SIMPLE_OBJECT_COUNT);

  auto info_ptr_u = Node::create(Node::Type::Map);
  cc_vec[ObjectIndex::Info] = Node::create(info_ptr_u.get()); // create pointer to object information

  auto data_ptr_u = Node::create(Node::Type::Map);
  data_ptr_u->add(LOOSH_D_OBJ_INFO,  move(info_ptr_u));

  cc_vec[ObjectIndex::StringMap] = move(data_ptr_u);

  cout << clean_function_name() <<   ": cc_vec: " <<  _to_str( cc_vec) << "\n";

  return cc_vec;
}

Node::OpStatus Node::obj_array_push_back(ptr_U v) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::MetaObject) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, create(false)};
  }

  auto &obj = get<VecObject>(m_value);
  auto &vec_array = obj[ObjectIndex::VectorArray]->get_node();
  vec_array.push_back(move(v));


}


}
