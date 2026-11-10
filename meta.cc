#include "node.hh"

//#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"
#include "atom.hh"


using namespace std;
namespace Loosh {

Meta::Meta() : Meta::Node(create_vec()) {
  m_type=Node::Type::Meta;
  
}
Meta::Meta(Node::Type t)  : Node(t) {
  if(t==Node::Type::Meta ) {
    m_value = create_vec();
    return;
  }

}
Node::Vector Meta::create_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  //MetaObject cc_vec(ObjectIndex::count);
  Vector cc_vec(Index::count);


  cc_vec[Index::Parent] = nullptr;
  cc_vec[Index::InfoMap] = Node::create(Node::Type::IMap);
  cc_vec[Index::AtomMap] = Node::create(Node::Type::IMap);
  cc_vec[Index::VectorArray] = Node::create(Node::Type::Vector);
  cc_vec[Index::StringMap] = Node::create(Node::Type::Map);
  cc_vec[Index::MetaLock] = Node::create(Node::Type::Lock);
  cc_vec[Index::cc_class] = Node::create(Node::Type::Atom);
  cc_vec[Index::WalkerCount] = Node::create(Node::Type::AtomicInteger);

  return cc_vec;
}


unique_ptr<Meta> Meta::create(ptr_R parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  auto obj = make_unique<Meta>();
  obj->set_parent(parent);
  return obj;
}
unique_ptr<Meta> Meta::create_child(const string &name) {
  auto child = create(this);
  if(name!="") child->set_name(name);
  
  return child;
}

bool Meta::set_name(const string& name) {
  info_add(Atom::name, Node::create(name));
  return true;
}

//------------------------------------------------------------------------ 
bool Meta::set_parent(ptr_R parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a Meta Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return false;
  }
  auto &obj = get<Vector>(m_value);
  obj[Index::Parent] = Node::create(parent);
  return true;
}


//------------------------------------------------------------------------  array
//------------------------------ push front
Node::OpStatus Meta::array_push_front(ptr_U v) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create()};
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  obj_array->push_front(move(v));

  return {true, Node::create()};
}

//------------------------------ push back
Node::OpStatus Meta::array_push_back(ptr_U v) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create()};
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  obj_array->push_back(move(v));

  return {true, Node::create()};
}


//------------------------------ pop front
Node::OpStatus Meta::array_pop_front() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create()};
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  return obj_array->pop_front();
}


//------------------------------ pop back
Node::OpStatus Meta::array_pop_back() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create()};
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  return obj_array->pop_back();
}



//------------------------------ 

Node::UnsignedInteger Meta::array_size() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::bad_typeid();
  }

  const auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[Index::VectorArray];
  return obj_array->_size();

}

Node::OpStatusRef Meta::array_back() {
  const auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  if(obj_array->_size())
    return obj_array->back();
  return {false, node_null};
}
Node::OpStatusRef Meta::array_front() {
  const auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  if(obj_array->_size())
    return obj_array->front();
  return {false, node_null};
}

Node::OpStatusRef Meta::array_get(UnsignedInteger key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::bad_typeid();
  }
  const auto &obj = get<Vector>(m_value);
  auto &obj_array  = obj[VectorArray];
  if( obj_array->_size() > key) {
    return  (*obj_array)[key];
  }
  string msg = "Index out of bound";
  cerr << clean_function_name() <<  ":" + msg << "\n";
  spdlog::error(msg);
  throw std::bad_typeid();

}
//------------------------------------------------------------------------ Atom
//------------------------------  size
Node::UnsignedInteger Meta::atom_size() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  //return "nhello";
  auto &obj = get<Vector>(m_value);
  auto &obj_atom  = obj[AtomMap];
  return obj_atom->_size();

}

//------------------------------  add
Node::OpStatus Meta::atom_add(const UnsignedInteger key, unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_atom  = obj[AtomMap];

  if(!obj_atom->add(key, move(value)).first) {
    auto key_vstr = Loosh::Atom::atom_to_str_imap(key);
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key_vstr + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}

//------------------------------  set
Node::OpStatus Meta::atom_set(const UnsignedInteger key, unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_atom  = obj[AtomMap];

  if(!obj_atom->set(key, move(value)).first) {
    return {false, Node::create_error(Node::Error::Type::Unknown, "Key '" + Loosh::Atom::atom_to_str_imap(key) + " unknown set atom error ")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}
Node::OpStatusRef Meta::atom_get(const UnsignedInteger key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if (m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return{false, 
      Error::ref(Error::Type::InvalidOperation, 
        "Not a Meta Object! " + Node::_to_str(m_type) + " : " + Node::_to_str(m_type))
    };
  }
  //cout << "obj atom get: " << Loosh::Atom::atom_to_str( key) << "\n";
  //cout << clean_function_name() << "obj atom get: key " << key << "\n";

  auto &obj = get<Vector>(m_value);
  auto &obj_atom = obj[AtomMap];
 // auto &n1 = obj_atom->get_node();
 // cout <<  clean_function_name() <<  "n1: " << n1._to_str() << "\n";

  return obj_atom->get_node(key);
}

//------------------------------------------------------------------------ Info
//------------------------------  size
Node::UnsignedInteger Meta::info_size() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  //return "nhello";
  auto &obj = get<Vector>(m_value);
  auto &obj_info  = obj[InfoMap];
  return obj_info->_size();

}

//------------------------------  add
Node::OpStatus Meta::info_add(const UnsignedInteger key, unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_info  = obj[InfoMap];

  if(!obj_info->add(key, move(value)).first) {
    auto key_vstr = Loosh::Atom::atom_to_str_imap(key);
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key_vstr + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}

//------------------------------  set
Node::OpStatus Meta::info_set(const UnsignedInteger key, unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
    //throw system_error();
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_info  = obj[InfoMap];

  if(!obj_info->set(key, move(value)).first) {
    return {false, Node::create_error(Node::Error::Type::Unknown, "Key '" + Loosh::Atom::atom_to_str_imap(key) + " unknown set atom error ")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}
Node::OpStatusRef Meta::info_get(const UnsignedInteger key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if (m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return{false, 
      Error::ref(Error::Type::InvalidOperation, 
        "Not a Meta Object! " + Node::_to_str(m_type) + " : " + Node::_to_str(m_type))
    };
  }
  //cout << "obj atom get: " << Loosh::Atom::atom_to_str( key) << "\n";
  //cout << clean_function_name() << "obj atom get: key " << key << "\n";

  auto &obj = get<Vector>(m_value);
  auto &obj_info = obj[InfoMap];
 // auto &n1 = obj_atom->get_node();
 // cout <<  clean_function_name() <<  "n1: " << n1._to_str() << "\n";

  return obj_info->get_node(key);
}

//------------------------------------------------------------------------ object data add, set, get
Node::OpStatus Meta::data_add(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_data = obj[MetaObjectIndex::StringMap]->get_node();

  if(!obj_data.add(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";
  return {true, Node::create(true)};
}


//------------------------------  set
Node::OpStatus Meta::data_set(const string&key, unique_ptr<Node> value) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is not a Meta Object!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return {false, Node::create_error(Node::Error::Type::IndexWrongType, msg)};
  }


  auto &obj = get<Vector>(m_value);
  auto &obj_data = obj[MetaObjectIndex::StringMap]->get_node();

  if(!obj_data.set(key, move(value)).second) {
    return {false, Node::create_error(Node::Error::Type::KeyAlreadyExists, "Key '" + key + "' already exists in map.")};
  }

  //cout << "obj_meta_add(), map_ptr_r: " << Node::_to_str( *map_ptr_r) << "\n";

  return {true, Node::create(true)};
}

//------------------------------ 
Node::OpStatusRef Meta::data_get(const string&key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if (m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not an Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return{false, 
      Error::ref(Error::Type::InvalidOperation, 
        "Unsupported types for addition! " + Node::_to_str(m_type) + " : " + Node::_to_str(m_type))
    };
  }

  auto &obj = get<Vector>(m_value);
  auto &obj_data = obj[MetaObjectIndex::StringMap];
  return obj_data->get_node(key);

}
Node::UnsignedInteger Meta::data_size() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a MetaObject" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::bad_typeid();
  }

  const auto &obj = get<Vector>(m_value);
  return obj.size();

}

string Meta::_to_str() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  string result="";
  auto& cc_vec = get<Vector>(m_value);
  return _to_str(cc_vec);

  /*
  result  += "Map:" + cc_vec[Index::StringMap]->_to_str() + "\n";
  //result  += "Atom:" + cc_vec[Index::AtomMap]->get_node()._to_str() + "\n";
  result  += "Atom:" + cc_vec[Index::AtomMap]->_to_str() + "\n";
  //result  += "Vector: " + cc_vec[Index::VectorArray]->get_node()._to_str() + "\n";
  result  += "Vector: " + cc_vec[Index::VectorArray]->_to_str() + "\n";
  return result;
  */
}

string Meta::_to_str(const Vector& cc_vec)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  string result;
  result  += "Map:" + cc_vec[Index::StringMap]->_to_str() + "\n";
  result  += "Atom:" + cc_vec[Index::AtomMap]->_to_str() + "\n";
  result  += "Info:" + cc_vec[Index::InfoMap]->_to_str() + "\n";
  result  += "Vector: " + cc_vec[Index::VectorArray]->_to_str() + "\n";
  return result;

}
}
