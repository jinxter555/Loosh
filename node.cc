#include "node.hh"


#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


//#include "node_tmpl_cc.hh"

using namespace std;
namespace Loosh 
{



Node node_null(Node::Type::Null);

  

Node::Node() : m_type(Type::Null) {
  m_value = {};
}

Node::Node(ptr_U ptr) : m_value(move(ptr)), m_type(Type::Unique) {};
Node::Node(ptr_R ptr) : m_value(ptr), m_type(Type::Raw) {};

Loosh::Node::Node(Value val) 
: m_value(move(val)) 
, m_type(value_variant_type())
{}

Loosh::Node::Node(Value v, Type t) 
: m_value(move(v))
, m_type(t) {}

//Node::Node(Map v, Type t)  { }

Node::Node(Type t)
  : m_type(t) {
  switch(t) {
  case Type::Null: m_value= {}; break;
  case Type::Bool: m_value=true; break;
  case Type::Size: m_value=0; break;
  case Type::Integer: m_value=0; break;
  case Type::Float: m_value=0.0; break;
  case Type::String: m_value=""; break;
  //case Type::Error: m_value = {} ; break;
  case Type::Error: m_value = Error{Error::Type::Unknown, "Unknown Init"} ; break;
  case Type::Map: { 
    Map nm={};
    m_value = move(nm);
    break;}

/*
  case Type::Info: {
    Map nm={};
    nm[LOOSH_OBJ_INFO] = Node::create(Node::Type::Map);
    nm[LOOSH_OBJ_DATA] = Node::create(Node::Type::Map);
    m_value = move(nm);
    cout << clean_function_name() << ": Node::Node(MetaObject)" << _to_str() << "\n";
    break;
  }
*/
  case Type::MetaObject: {
    /*
    Vector cc_vec(MetaIndex::count);

    auto obj_info_ptr_u = Node::create(Node::Type::Map);
    cc_vec[MetaIndex::Info] = Node::create(obj_info_ptr_u.get()); // create pointer to object information

    auto table_ptr_u = Node::create(Node::Type::Map);
    table_ptr_u->add(LOOSH_D_OBJ_INFO,  move(obj_info_ptr_u));

    cc_vec[MetaIndex::Parent] = nullptr;
    cc_vec[MetaIndex::Table] = move(table_ptr_u);
    cc_vec[MetaIndex::Children] = Node::create(Node::Type::Vector);
*/
    m_value = move(create_meta_vec());
    //cout << clean_function_name() << ": Node::Node(MetaObject)" << _to_str() << "\n";

    break;
  }

  case Type::IMap: { 
    IMap nm={};
    m_value = move(nm);
    break;}

  case Type::List: { 
    List l={};
    m_value = move(l);
    break;}
  case Type::Vector: { 
    Vector l={};
    m_value = move(l);
    break;}
  case Type::DeQue: { 
    DeQue l={};
    m_value = move(l);
    break;}
  default: {
    m_value = monostate{};
    m_type = Type::Null;

  }}
}




unique_ptr<Node> Node::create_error(Error::Type t, const string& msg) {
  return make_unique<Node>(Value(Error{t, msg}));
}

unique_ptr<Node> Node::create() { return make_unique<Node>(); }
unique_ptr<Node> Node::create(Value v) { return make_unique<Node>(move(v)); }
//unique_ptr<Node> Node::create(ValueSimple v) { return make_unique<Node>(move(v)); }
unique_ptr<Node> Node::create(Value v, Type t) { return make_unique<Node>(move(v), t); }
unique_ptr<Node> Node::create(Type t) { 
  switch(t) {

  case Type::IMap: {
    Node::IMap im;
    return make_unique<Node>(move(im));}
  case Type::MetaObject: {
    return make_unique<Node>(create_meta_vec()); }
  case Type::Map: {
    Node::Map m;
    return make_unique<Node>(move(m)); }
  case Type::List: {
    Node::List l;
    return make_unique<Node>(move(l)); }
  case Type::Vector: {
    Node::Vector v;
    v.reserve(10);
    return make_unique<Node>(move(v)); }

  case Type::DeQue: {
    Node::DeQue q;
    return make_unique<Node>(move(q)); 
  }

  default: return make_unique<Node>(); }

  return make_unique<Node>();
}



//------------------------------------------------------------------------

Node::Type Node::value_variant_type() {
  return visit([](auto&& inner_arg) -> Type {
    using T = decay_t<decltype(inner_arg)>;
    if constexpr (is_same_v<T, monostate>) return Type::Null;
    else if constexpr (is_same_v<T, bool>) return Type::Bool;
    else if constexpr (is_same_v<T, Error>) return Type::Error;
    else if constexpr (is_same_v<T, Integer>) return Type::Integer;
    else if constexpr (is_same_v<T, Float>) return Type::Float;
    else if constexpr (is_same_v<T, string>) return Type::String;
    else if constexpr (is_same_v<T, List>) return Type::List;
    else if constexpr (is_same_v<T, Vector>) return Type::Vector;
    else if constexpr (is_same_v<T, DeQue>) return Type::DeQue;
    else if constexpr (is_same_v<T, Map>) return Type::Map;
    else if constexpr (is_same_v<T, IMap>) return Type::IMap;
    else if constexpr (is_same_v<T, ptr_R>) return Type::Raw;
    else if constexpr (is_same_v<T, ptr_U>) return Type::Unique;
    else if constexpr (is_same_v<T, Fun>) return Type::Fun;
    return Type::Null;
  }, m_value);
}

//------------------------------------------------------------------------
Node::Type Node::_get_type() const { return m_type; }
Node::Type Node::_get_value_type() const { 
  switch(m_type) {
  case Node::Type::Unique: {
    auto& ptr = get<ptr_U>(m_value);
    return ptr->_get_value_type();}
  case Node::Type::Raw:  {
    auto& ptr = get<ptr_R>(m_value);
    return ptr->_get_value_type();}
  default:  {}}

  return m_type;
}
Node Node::get_type() const { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  //AUTO_TRACE();
  MYLOGGER_MSG(trace_function, "hello:get_type() ", SLOG_FUNC_INFO);
  cout << "Node::get_type()\n";
  return m_type; 
}


//------------------------------------------------------------------------ _get
//------------------------------ _get_map_ref()
Node::Map& Node::_get_map_ref() { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->_get_map_ref(); }
  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->_get_map_ref(); }
  case Type::SimpleObject:
  case Type::Map:  {
    return get<Map>(m_value);}
  default: {}}

  auto msg =  "Not a Node::Map, Node::m_type " + _to_str(m_type) + ", Node::m_value " +  _to_str() ;
  spdlog::error(clean_function_name() + ": " +  msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();
  
}

Node::Map& Node::_get_map_ref(const string& key) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->_get_map_ref(key); }
  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->_get_map_ref(key); }
  case Type::Map:  {
    return get<Map>(m_value);}
  default: {}}

  auto msg =  "Not a Node::Map, Node::m_type " 
    + _to_str(m_type) + ", Node::m_value " +  _to_str() ;

  spdlog::error(clean_function_name() + ": " +  msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();


}



//------------------------------ _get_imap_ref
Node::IMap& Node::_get_imap_ref() { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(m_type) {
  case Type::Raw: {
    auto sptr = get<ptr_R>(m_value);
    return sptr->_get_imap_ref(); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(m_value);
    return sptr->_get_imap_ref(); }
  case Type::IMap:  {
    return get<IMap>(m_value);}
  default: {}}

  auto msg = "Not a Node::IMap, Node::m_type " 
      +  _to_str(m_type) + ", Node::m_value " +  _to_str() ;
  spdlog::error(clean_function_name() + ": " +  msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();
  
}


//------------------------------ _get_vector_ref
Node::Vector& Node::_get_vector_ref() { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    cout << "get_vector_ref() " << rptr->_get_str() << "\n";
    return rptr->_get_vector_ref(); }
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(m_value);
    return sptr->_get_vector_ref(); }
  case Type::Vector:  {
    return get<Vector>(m_value); 
  }
  default: {}}

  auto msg ="Node::_get_vector_ref(): not a Node::Vector: Node::m_type " 
    + _to_str(m_type) + ", Node::m_value " +  _to_str() ;
  spdlog::error(msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();

}

//------------------------------ _get_deque_ref
Node::DeQue& Node::_get_deque_ref() { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->_get_deque_ref(); }
  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->_get_deque_ref(); }
  case Type::DeQue:  {
    return get<DeQue>(m_value); 
  }
  default: {}}

  auto msg = "Not a Node::DeQue: Node::m_type " 
    +  _to_str(m_type) + ", Node::m_value " +  _to_str() ;
  spdlog::error(clean_function_name() + ": " + msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid(); 

}


//



//------------------------------ _get_list_ref
Node::List& Node::_get_list_ref() { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->_get_list_ref(); }
  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->_get_list_ref(); }
  case Type::List:  {
    return get<List>(m_value); 
  }
  default: {}}

  auto msg =  "Not a Node::List: Node::m_type " 
      +  _to_str(m_type) + ", Node::m_value " +  _to_str();
  spdlog::error(clean_function_name() + ": " + msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  throw std::bad_typeid();
  
}

//------------------------------------------------------------------------
//------------------------------ _get_rptr_ref

//------------------------------ _get_ptr_r
Node::ptr_R Node::_get_ptr_r() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    if(rptr->m_type == Node::Type::Raw) {
      string msg = "Raw, ptr_R is pointing to another RAW pointer!";
      spdlog::warn(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Warning: "  + msg, SLOG_NODE_OP)
    }
    return rptr;
  }
  default: {}}

  auto msg = "Node::_get_ptr_r() Error! not a Node::ptr_R: Node::m_type " 
  + _to_str(m_type) + ", Node::m_value " +  _to_str() ;

  spdlog::error(clean_function_name() + ": " + msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_NODE_OP)
  throw std::bad_typeid();
  
}

/*
Node::ptr_R Node::_get_meta_ptr_r() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  switch(m_type) {
  case Type::MetaPtr: {
    auto meta_ptr_r = get<ptr_R>(m_value);
    if(meta_ptr_r->m_type == Type::Map) {
      string msg = "Raw, meta_ptr_w is not a Map!";
      spdlog::warn(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Warning: "  + msg, SLOG_NODE_OP)
    }
    return meta_ptr_r;
  }
  default: {}}

  auto msg = "Node::_get_ptr_r() Error! not a Node::ptr_R: Node::m_type " 
  + _to_str(m_type) + ", Node::m_value " +  _to_str() ;

  spdlog::error(clean_function_name() + ": " + msg);
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_NODE_OP)
  throw std::bad_typeid();
}
  
*/


Node::ptr_U Node::_get_ptr_u() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(m_type != Type::Unique)  {
    auto msg = "Not a Node::ptr_U, Node::m_type " + _to_str(m_type) + ", Node::m_value " +  _to_str() ;
    cerr << clean_function_name() << ": " << msg << "\n";
    spdlog::error(clean_function_name() + ": " + msg);
    MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_NODE_OP)
    throw std::bad_typeid();
  }
  return move(get<ptr_U>(m_value));

}



//------------------------------------------------------------------------

void  Node::nil() { m_value = monostate{};  m_type = Node::Type::Null; }
void  Node::operator=(bool v) { m_value = v; m_type = Node::Type::Bool; }
void  Node::operator=(Integer v) { m_value = v; m_type = Node::Type::Integer; }
void  Node::operator=(Float v) { m_value = v; m_type = Node::Type::Float; }
void  Node::operator=(string v) { m_value = v; m_type = Node::Type::String; }
void  Node::operator=(ptr_U v) { m_value = move(v); m_type = Node::Type::Unique; }
void  Node::operator=(Error v) { m_value = move(v); m_type = Node::Type::Error; }

//void  Node::operator = (ValueSimple & v) { m_value = v; }

//------------------------------------------------------------------------
void Node::set(unique_ptr<Node> new_node) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(!new_node) {
    nil();
  } else {
    this->m_value = move(new_node->m_value);
    this->m_type = new_node->m_type;
  }
}


Node::OpStatus Node::set(const string& key, Value v) { return set(key, create(move(v))); }

// here, it doesn't matter if element exist or not. 
//use add to check if prevent adding additional key element

Node::OpStatus Node::set(const string&key, unique_ptr<Node> child) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if (m_type != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set key on a non-Map node.")};
  }        
  Map& map= get<Map>(m_value);
  map[key] = move(child);
  return {true, create(true)};
}


//------------------------------------------------------------------------

Node::OpStatus Node::delete_key(const string &key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(m_type != Type::Map)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  Map& map = get<Map>(m_value);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + key + "' not found in map.")};
  return {true, Node::create()};
}

Node::OpStatus Node::delete_key(Integer key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(m_type != Type::IMap)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  IMap& map = get<IMap>(m_value);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + to_string( key) + "' not found in map.")};
  return {true, Node::create()};
}


//------------------------------------------------------------------------ _get

Node& Node::get_node() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  switch(m_type) {
  case Node::Type::Unique: {
    auto& ptr = get<ptr_U>(m_value);
    if(ptr ==nullptr ) return node_null; 
    return ptr->get_node();
  }
  case Node::Type::Raw:  {
    auto& ptr = get<ptr_R>(m_value);
    if(ptr ==nullptr ) return node_null; 
    return ptr->get_node();
  }
  /*
  case Node::Type::MetaPtr:  {
    auto& meta_ptr_r = get<ptr_R>(m_value);
    return meta_ptr_r->get_node();
  }*/
  default:  {}
  }
  return *this;
}
//------------------------------ _get
bool Node::_get_bool() const { return get<bool>(m_value); }

Lisp::Op Node::_get_lisp_op() const { return get<Lisp::Op>(m_value); }

Node::Integer Node::_get_integer() const { return get<Integer>(m_value); }
Node::Atom  Node::_get_atom() const { return get<Atom>(m_value); }

Node::Float Node::_get_float() const { return get<Float>(m_value); }

string Node::_get_str() const { return _to_str(); }

//------------------------------

Node::OpStatusRef Node::operator[](Integer index) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  switch(m_type) {
  case Type::Vector: {
    Vector& cc_vec = get<Vector>(m_value);
    const Integer cc_vec_size =  static_cast<Integer>(cc_vec.size());
    if(index < 0 || index >= cc_vec_size){
      string msg = "Index " + to_string(index) + " is out of bounds for list size " + to_string(cc_vec_size) + ".";
      return {false, Error::ref(Error::Type::IndexOutOfBounds, msg)};
    }
    return {true, *cc_vec[index]};}

  case Type::IMap: {
    IMap& imap = get<IMap>(m_value);
    if (auto it = imap.find(index); it != imap.end())  return {true, *imap[index]};

    return {false,
      Error::ref(Error::Type::KeyNotFound,
        "IMap::Operator[] (key) " + to_string(index) +" not found: " + _to_str(m_type)
    )};}

  default: {}
  }

  return {false,
    Error::ref( Error::Type::InvalidOperation,
      "Operator[] (index) can only be used on vector/IMap nodes. Current type: " + _to_str(m_type)
  )};

}

//
// doesn't get nested pointer node reference
//
Node::OpStatusRef Node::operator[](const string& key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  if(m_type != Type::Map){
    return {false, Error::ref(Error::Type::InvalidOperation, 
    "Operator[] (key: " + key +  ") can only be used on Map nodes. Current type: " + _to_str(m_type))};
  }
  const Map& map = get<Map>(m_value);
  auto it=map.find(key);

  if(it==map.end()) {
    string msg = "key '" + key + "' not found in map.";
    return {false, Error::ref(Error::Type::KeyNotFound, msg)};
  }
  return {true, *it->second};
}


//------------------------------ add

Node::OpStatus Node::add(unique_ptr<Node> child) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  switch(m_type) {
  case Type::List: {
    List& cc_list = get<List>(m_value);
    cc_list.push_back(move(child)); 
    break; }

  case Type::DeQue: {
    DeQue& cc_dq = get<DeQue>(m_value);
    cc_dq.push_back(move(child));
    break; }
  case Type::Vector: {
    Vector& cc_vec= get<Vector>(m_value);
    cc_vec.push_back(move(child));
    break; }
  default: {
    auto msg =  "Cannot add element to a non-Node::__Sequence__, type: " + _to_str(m_type)  + ", Node::m_value: " +  _to_str();
    spdlog::error(clean_function_name() + ": " + msg);
    MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }}

  return {true, Node::create(true)};
}

//------------------------------ add
// only when no existing key is present
Node::OpStatus Node::add(const string&key, unique_ptr<Node> child) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if (m_type != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot add key-value to a non-Map node.")};
  }        
  Map& map = get<Map>(m_value);

  if(!map.try_emplace(key, move(child)).second) {
    return {false, create_error(Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }
  return {true, Node::create(true)};

}
//------------------------------ add


void Node::set(const Integer v, Type t) { m_value = v; m_type = t; } // could be regular Integer or Atom
void Node::set(const string&v, Type t) { m_value = v; m_type = t; } // could be reuglar string or identifer

  
//------------------------------ 
 
bool Node::is_nil() { return m_type == Type::Null ? true : false; }




Node::Vector Node::create_meta_vec() {
  Vector cc_vec(MetaIndex::count);

  auto obj_info_ptr_u = Node::create(Node::Type::Map);
  cc_vec[MetaIndex::Info] = Node::create(obj_info_ptr_u.get()); // create pointer to object information

  auto table_ptr_u = Node::create(Node::Type::Map);
  table_ptr_u->add(LOOSH_D_OBJ_INFO,  move(obj_info_ptr_u));

  cc_vec[MetaIndex::Parent] = nullptr;
  cc_vec[MetaIndex::Table] = move(table_ptr_u);
  cc_vec[MetaIndex::Children] = Node::create(Node::Type::Vector);

  return cc_vec;
}

} 