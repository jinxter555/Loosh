#include "frame.hh"
#include "scope.hh"

using namespace  std;
namespace Loosh 
{

Frame::Frame() :Environment(Node::Type::Vector) {}

unique_ptr<Node> Frame::create() {
  return make_unique<Frame>();
}

Node::ptr_R Frame::push_scope() {
  auto scope = make_unique<Scope>();
  auto ptr = scope.get();
  push_back(move(scope));
  return ptr;
}



}