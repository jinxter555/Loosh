#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#define LOC_FUN source_location::current().function_name()

namespace Loosh{

unique_ptr<Node> Node::clone() const {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_TO_STR);
  return visit([](auto&& inner_arg) -> ptr_U {
    using U = decay_t<decltype(inner_arg)>;
    if constexpr (is_same_v<U, monostate>) return make_unique<Node>();
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



//-----------------------------------

}