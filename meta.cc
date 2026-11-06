#include "node.hh"

//#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"
#include "atom.hh"


using namespace std;
namespace Loosh {

Meta::Meta() : Meta::Node(Vector(Meta::Index::count) ){
  m_type=Node::Type::Meta;
}
Meta::Meta(Node::Type t)  : Node(t) {
  if(t==Node::Type::Meta ) {

  }

}



}