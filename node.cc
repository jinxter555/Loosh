#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;
namespace Loosh 
{
  

Node::Node() : type_(Type::Null) {
  value_ = {};
}

Node::Node(ptr_U ptr) : value_(move(ptr)), type_(Type::Unique) {};
Node::Node(ptr_R ptr) : value_(ptr), type_(Type::Raw) {};

Loosh::Node::Node(Value val) 
: value_(move(val)) 
, type_(value_variant_type())
{}

Loosh::Node::Node(Value v, Type t) 
: value_(move(v))
, type_(t) {}

//Node::Node(Map v, Type t)  { }

Node::Node(Type t)
  : type_(t) {
  switch(t) {
  case Type::Null: value_= {}; break;
  case Type::Bool: value_=true; break;
  case Type::Integer: value_=0; break;
  case Type::Float: value_=0.0; break;
  case Type::String: value_=""; break;
  //case Type::Error: value_ = {} ; break;
  case Type::Error: value_ = Error{Error::Type::Unknown, "Unknown Init"} ; break;
  case Type::Map: { 
    Map nm={};
    value_ = move(nm);
    break;}
  case Type::IMap: { 
    IMap nm={};
    value_ = move(nm);
    break;}

  case Type::List: { 
    List l={};
    value_ = move(l);
    break;}
  case Type::Vector: { 
    Vector l={};
    value_ = move(l);
    break;}
  case Type::DeQue: { 
    DeQue l={};
    value_ = move(l);
    break;}
  default: {
    value_ = monostate{};
    type_ = Type::Null;

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
    using U = decay_t<decltype(inner_arg)>;
    if constexpr (is_same_v<U, monostate>) return Type::Null;
    else if constexpr (is_same_v<U, bool>) return Type::Bool;
    else if constexpr (is_same_v<U, Error>) return Type::Error;
    else if constexpr (is_same_v<U, Integer>) return Type::Integer;
    else if constexpr (is_same_v<U, Float>) return Type::Float;
    else if constexpr (is_same_v<U, string>) return Type::String;
    else if constexpr (is_same_v<U, List>) return Type::List;
    else if constexpr (is_same_v<U, Vector>) return Type::Vector;
    else if constexpr (is_same_v<U, DeQue>) return Type::DeQue;
    else if constexpr (is_same_v<U, Map>) return Type::Map;
    else if constexpr (is_same_v<U, IMap>) return Type::IMap;
    else if constexpr (is_same_v<U, ptr_R>) return Type::Raw;
    else if constexpr (is_same_v<U, ptr_U>) return Type::Unique;
    else if constexpr (is_same_v<U, Fun>) return Type::Fun;
    return Type::Null;
  }, value_);
}

//------------------------------------------------------------------------
Node::Type Node::_get_type() const { return type_; }
Node::Type Node::_get_value_type() const { 
  switch(type_) {
  case Node::Type::Unique: {
    auto& ptr = get<ptr_U>(value_);
    return ptr->_get_value_type();
  }
  case Node::Type::Raw:  {
    auto& ptr = get<ptr_R>(value_);
    return ptr->_get_value_type();
  }
  default:  {}
  }
  return type_;
}


//------------------------------------------------------------------------

void  Node::nil() { value_ = std::monostate{};  type_ = Node::Type::Null; }
void  Node::operator=(bool v) { value_ = v; type_ = Node::Type::Bool; }
void  Node::operator=(Integer v) { value_ = v; type_ = Node::Type::Integer; }
void  Node::operator=(Float v) { value_ = v; type_ = Node::Type::Float; }
void  Node::operator=(string v) { value_ = v; type_ = Node::Type::String; }
void  Node::operator=(ptr_U v) { value_ = move(v); type_ = Node::Type::Unique; }
void  Node::operator=(Error v) { value_ = move(v); type_ = Node::Type::Error; }

//void  Node::operator = (ValueSimple & v) { value_ = v; }

//------------------------------------------------------------------------
void Node::set(unique_ptr<Node> new_node) {
  if(!new_node) {
    nil();
  } else {
    this->value_ = move(new_node->value_);
    this->type_ = new_node->type_;
  }
}


Node::OpStatus Node::set(const string& key, Value v) {
  return set(key, create(move(v))); 

}

Node::OpStatus Node::set(const string&key, unique_ptr<Node> child) {
  if (type_ != Type::Map) {
    return {false, create_error(Error::Type::InvalidOperation, "Cannot set key on a non-Map node.")};
  }        
  Map& map= get<Map>(value_);
  map[key] = move(child);
  return {true, create(true)};
}


//------------------------------------------------------------------------

Node::OpStatus Node::delete_key(const string &key) {
  if(type_ != Type::Map)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  Map& map = get<Map>(value_);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + key + "' not found in map.")};
  return {true, Node::create()};
}

Node::OpStatus Node::delete_key(Integer key) {
  if(type_ != Type::IMap)
    return {false, create_error(Error::Type::InvalidOperation, "Cannot delete key on a non-Map node.")};

  IMap& map = get<IMap>(value_);
  if(map.erase(key)==0)
    return {false, create_error(Error::Type::InvalidOperation,  "Key '" + to_string( key) + "' not found in map.")};
  return {true, Node::create()};
}


//------------------------------------------------------------------------ _get

Node& Node::get_node() {
  switch(type_) {
  case Node::Type::Unique: {
    auto& ptr = get<ptr_U>(value_);
    return ptr->get_node();
  }
  case Node::Type::Raw:  {
    auto& ptr = get<ptr_R>(value_);
    return ptr->get_node();
  }
  default:  {}
  }
  return *this;
}
//------------------------------ _get
bool Node::_get_bool() const { return get<bool>(value_); }

Lisp::Op Node::_get_lisp_op() const { return get<Lisp::Op>(value_); }

Node::Integer Node::_get_integer() const { return get<Integer>(value_); }

Node::Float Node::_get_float() const { return get<Float>(value_); }

string Node::_get_str() const { return _to_str(); }

//------------------------------

Node::OpStatusRef Node::operator[](size_t index) {
  if(type_ != Type::Vector) {
    return { false,
    Error::ref(
      Error::Type::InvalidOperation,
      "Operator[] (index) can only be used on vector nodes. Current type: " + _to_str(type_)
    )};
  }
  Vector& list = get<Vector>(value_);
  if(index >= list.size()){
    string msg = "Index " + to_string(index) + " is out of bounds for list size " + to_string(list.size()) + ".";
    return {false, Error::ref(Error::Type::IndexOutOfBounds, msg)};
  }
  return {true, *list[index]};
}

Node::OpStatusRef Node::operator[](const string& key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  if(type_ != Type::Map){
    return {false, Error::ref(Error::Type::InvalidOperation, 
    "Operator[] (key: " + key +  ") can only be used on Map nodes. Current type: " + _to_str(type_))};
  }
  const Map& map = get<Map>(value_);
  auto it=map.find(key);

  if(it==map.end()) {
    string msg = "key '" + key + "' not found in map.";
    return {false, Error::ref(Error::Type::KeyNotFound, msg)};
  }
  return {true, *it->second};
}





} 