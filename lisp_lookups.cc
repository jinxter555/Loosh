#include <string>
#include <memory>
#include <unordered_map>
#include "node.hh"
#include "lisp.hh"


using namespace  std;
namespace Loosh 
{

Node::OpStatusRef Lisp::symbol_lookup(Node&process, const string&name ) {

}
Node::OpStatusRef Lisp::symbol_lookup_frame(Node&process, Node&frame, const string&name ) {

}

vector<string> Lisp::get_local_vars(Node&process) {
  return {};
}

}