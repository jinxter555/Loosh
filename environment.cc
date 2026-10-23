#include "environment.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace  std;
namespace Loosh 
{
Environment::Environment() {}
Environment::Environment(Node::Type t) : Node(t) {}

};
