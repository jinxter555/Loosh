#include "tree.hh"
#include "node.hh"
using namespace std;
namespace Loosh 
{
//------------------------------------------------------------------------
Tree::Tree() { root = Node::create(Node::Value(Node::Map{})); }

Tree::Tree(unique_ptr<Node> root_node) 
: root(move(root_node)) { 
  if(!root || root->type_ == Node::Type::Null) {
    root = Node::create(Node::Value(Node::Map{}));
  }
  else if(root->type_ != Node::Type::Map) {
    root = Node::create(Node::Value(Node::Map{}));
  }
}


Node* Tree::get_branch(const vector<string>&path ) const {
  if(path.empty()) return root.get();

  Node* current = root.get();
  for(const auto&key : path) {
    if(!current || current->type_ != Node::Type::Map) {
      return nullptr;
    }
    Node::Map& map = get<Node::Map>(current->value_);
    auto it = map.find(key);
    if(it == map.end()) return nullptr;
    current = it->second.get();
  }
  return current;
}

Node::OpStatus Tree::set_branch(const vector<string>&path, unique_ptr<Node> child) {
  if(path.empty()) {
    root = move(child);
    return {true, nullptr};
  }
  Node* current_node = root.get() ;
  size_t last_index = path.size() - 1;
  for(size_t i=0; i<last_index; ++i) {
    const string& key = path[i];

    if(current_node->type_ != Node::Type::Map ){
      string msg = "Cannot navigate path: '" + key + "' parent is not a Map (Type: " + Node::_to_str(current_node->type_) + ")";
      return {false, Node::create_error(Node::Error::Type::InvalidOperation, msg)};
    }
    Node::Map& map = get<Node::Map>(current_node->value_);
    auto it = map.find(key);

    if(it == map.end()) {
      auto new_map_node = Node::create(Node::Value(Node::Map{}));
      Node::OpStatus status = current_node->set(key, move(new_map_node));
      if(!status.first) return status;
      current_node = get<Node::Map>(current_node->value_).at(key).get();
    } else {
      current_node = it->second.get();
    }
  }
  return current_node->set(path.back(), move(child));
}

Node::OpStatus Tree::delete_branch(const vector<string>&path) {
  if(path.empty())   
    return { 
      false, 
      Node::create_error(Node::Error::Type::InvalidOperation,  "Cannot delete the root node via delete_branch.") 
    };

  vector<string> parent_path(path.begin(), path.end()-1);

  Node* parent_node = get_branch(parent_path);

  if(!parent_node || parent_node->type_ != Node::Type::Map){
    return { false
      , Node::create_error(Node::Error::Type::InvalidOperation, 
        "Invalid path: parent node is not a Map or doesn't exist.")}; 
  }

  const string& key_to_delete = path.back();
  return parent_node->delete_key(key_to_delete);
}

const Node* Tree::get_root() const {
  return root.get();
}


Tree::OpStatus Tree::set(const vector<string>&path, unique_ptr<Node>child, bool override) {
  return root->set(path, move(child), override);
}

Tree::OpStatusRef Tree::get_node(const vector<string>&path) { return root->get_node(path); }

void Tree::print() const {
//  root->print();
}

}