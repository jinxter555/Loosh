#include "tree.hh"
#include "node.hh"
using namespace std;
namespace Loosh 
{
//------------------------------------------------------------------------
Tree::Tree() { root = Meta::create(); }

Tree::Tree(unique_ptr<Meta> r) 
: root(move(r)) { 
  if(!root || root->m_type == Node::Type::Null) {
    root = Meta::create();
  }
}
Meta* Tree::get_root() {
  return root.get();
}

}