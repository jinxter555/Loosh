#include "frame.hh"
#include "scope.hh"

using namespace  std;
namespace Loosh 
{

Frame::Frame() :Environment(Node::Type::Vector) {}

unique_ptr<Node> Frame::create() {
  return make_unique<Frame>();
}

}