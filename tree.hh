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
class Meta;

class Tree {
friend class Lisp;
private:
using OpStatus = pair<bool, unique_ptr<Node>>;
using OpStatusRef = pair<bool, Node&>;

protected:
  unique_ptr<Meta> root;
public:
  Tree();
  Tree(unique_ptr<Meta> r);
  Meta* get_root() ;
  /*
  OpStatus set_branch(const vector<string>&path, unique_ptr<Meta>child);
  OpStatus delete_branch(const vector<string>&path);
  Meta* get_branch(const vector<string>&path) const ;

  // use Node methods
  OpStatus set(const vector<string>&path, unique_ptr<Meta>child, bool override=false);
  OpStatusRef get_node(const vector<string>&path);
  void print() const;
  */
};

/*
class TreeWalker {
private:
  Tree *root;
  Node *current;
  const Node *start_branch;

public:


};
*/
}