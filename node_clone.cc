#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include "node.hh"
#include "defs.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


namespace Loosh
{

bool Node::type_set_identifier() { type_ = Node::Type::Identifier; return true;}
bool Node::type_set_atom() { type_ = Node::Type::Atom; return true; };
bool Node::type_set_object_id() { type_ = Node::Type::ObjectId; return true;};

//-----------------------------------
unique_ptr<Node> Node::clone() const {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);
  return visit([&](auto&& arg) -> ptr_U {
    using U = decay_t<decltype(arg)>;
    if constexpr (is_same_v<U, monostate>) return make_unique<Node>();

    else if constexpr (is_same_v<U, Integer>) {
      auto uptr = create(arg); // create a new objec with same value
      if(type_ == Type::Atom) uptr->type_set_atom();
      if(type_ == Type::ObjectId) uptr->type_set_object_id();
      return uptr; }

    else if constexpr (is_same_v<U, string>) {
      auto uptr = create(arg); // create a new objec with same value
      uptr->type_ = type_;
      if(type_ == Type::Identifier) uptr->type_set_identifier();
      return uptr; }

    else if constexpr(
      is_same_v<U, Float> ||  
      is_same_v<U, bool> ||
      is_same_v<U, ptr_R> ||  
      is_same_v<U, Error >) {
      auto uptr = create(arg); 
      uptr->type_ = type_;
      return  uptr; }

    else if constexpr (is_same_v<U, List>) return clone(arg);
    else if constexpr (is_same_v<U, Vector>) return clone(arg);
    else if constexpr (is_same_v<U, DeQue>) return clone(arg);
    else if constexpr (is_same_v<U, Map>) return clone(arg);
    else if constexpr (is_same_v<U, IMap>) return clone(arg);
    else if constexpr (is_same_v<U, ptr_R>) return create(*arg);
    //else if constexpr (is_same_v<U, ptr_U>) return create();
    else if constexpr (is_same_v<U, Fun>) return clone(arg);
    else return nullptr;
  }, value_);

}
//----------------------------------- cc list

unique_ptr<Node> Node::clone(const List& cc_list) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);
  List cloned_list;
  for(const auto& child_u_ptr : cc_list ) 
    cloned_list.push_back(child_u_ptr->clone());
  return create(move(cloned_list));
}

//----------------------------------- cc deque
unique_ptr<Node> Node::clone(const DeQue& cc_deque) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);

  DeQue cloned_deque;

  for(const auto& child_u_ptr : cc_deque ) 
    cloned_deque.push_back(child_u_ptr->clone());
  return create(move(cloned_deque));
}

//----------------------------------- cc vector
unique_ptr<Node> Node::clone(const Vector& cc_vec) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);

  Vector cloned_vector;

  for(const auto& child_u_ptr : cc_vec ) 
    cloned_vector.push_back(child_u_ptr->clone());
  return create(move(cloned_vector));
}

//----------------------------------- fun
unique_ptr<Node> Node::clone(const Fun& f) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);
  return make_unique<Node>(f);
}

//-----------------------------------
unique_ptr<Node> Node::clone(const Map& map) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);

  Map cloned_map;
  for(const auto& [key, child_ptr] : map) {
    //if(key == CLASS_PTR) { cloned_map.try_emplace(key, create( child_ptr.get())); continue; }
    //if(key == MODULE_PTR) { cloned_map.try_emplace(key, create( child_ptr.get())); continue; }
    cloned_map.try_emplace(key, child_ptr->clone());
  }
  return create(move(cloned_map));
}
//-----------------------------------

unique_ptr<Node> Node::clone(const IMap& map) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_NODE_OP);

  IMap cloned_map;
  for(const auto& [key, child_ptr] : map) {
    cloned_map.try_emplace(key, child_ptr->clone());
  }
  return create(move(cloned_map));
}




}