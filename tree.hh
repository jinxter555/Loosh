#pragma once
//#include "node.hh"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

using namespace std;
namespace Loosh 
{

class Node;

class Tree {
private:
using OpStatus = pair<bool, unique_ptr<Node>>;
using OpStatusRef = pair<bool, Node&>;

protected:
  unique_ptr<Node> root;
public:
  Tree();
  Tree(unique_ptr<Node> root_node);
  const Node* get_root() const ;
  OpStatus set_branch(const vector<string>&path, unique_ptr<Node>child);
  OpStatus delete_branch(const vector<string>&path);
  Node* get_branch(const vector<string>&path) const ;

  // use Node methods
  OpStatus set(const vector<string>&path, unique_ptr<Node>child, bool override=false);
  OpStatusRef get_node(const vector<string>&path);
  void print() const;
};

}