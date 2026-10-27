#include <iostream>

#include "frame.hh"
#include "scope.hh"

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace  std;
namespace Loosh 
{

Frame::Frame() :Environment(Node::Type::Vector) {}

unique_ptr<Node> Frame::create() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();
  return make_unique<Frame>();
}

Node::ptr_R Frame::push_scope() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();
  auto scope = make_unique<Scope>();
  auto ptr = scope.get();
  push_back(move(scope));
  return ptr;
}
void Frame::pop_scope() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();
  if(! _size())  {
    string msg = "pop_scope  frame error!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::system_error();
  }
  pop_back();
}


}