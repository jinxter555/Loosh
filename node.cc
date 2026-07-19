#include "node.hh"

using namespace std;
namespace Loosh 
{
  

Node::Node() : type_(Type::Null) {
  value_ = {};
}

Loosh::Node::Node(Value val) 
: value_(move(val)) 
, type_(value_variant_type())
{}

Loosh::Node::Node(Value v, Type t) 
: value_(move(v))
, type_(t) {}

//Node::Node(Map v, Type t)  { }


unique_ptr<Node> Node::create() { return make_unique<Node>(); }
unique_ptr<Node> Node::create(Value v) { return make_unique<Node>(move(v)); }
unique_ptr<Node> Node::create(Value v, Type t) { return make_unique<Node>(move(v), t); }
unique_ptr<Node> Node::create(Type t) { 
  switch(t) {

/*
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
*/

  default: return make_unique<Node>(); }

  return make_unique<Node>();
}




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

//void  Node::operator = (ValueSimple & v) { value_ = v; }
void  Node::nil() { value_ = std::monostate{};  type_ = Node::Type::Null; }
void  Node::operator=(bool v) { value_ = v; type_ = Node::Type::Bool; }
void  Node::operator=(Integer v) { value_ = v; type_ = Node::Type::Integer; }
void  Node::operator=(Float v) { value_ = v; type_ = Node::Type::Float; }
void  Node::operator=(string v) { value_ = v; type_ = Node::Type::String; }
void  Node::operator=(ptr_U v) { value_ = move(v); type_ = Node::Type::Unique; }



} 