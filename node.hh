#pragma once
#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <unordered_map>                                                                        
#include <functional>

#include "defs.hh"
#include "lisp.hh"


using namespace std;
namespace Loosh 
{


class Node {
friend class Tree;
public:

//----------------------------------
  class Error {  public: enum class Type {
    DivideByZero, 
    InvalidOperation, // e.g., calling 'add' on an Integer node
    KeyAlreadyExists, // e.g., calling 'add' with a duplicate map key
    KeyNotFound, // e.g., calling 'add' with a duplicate map key
    IndexOutOfBounds,  // e.g., calling 'set' with an invalid list index
    IndexWrongType,  // e.g., calling 'set' with an invalid list index
    EmptyContainer,  // get front() or back() when list,queu,vector is empty
    ModuleNotFound,  //  module
    FunctionNotFound,  // function not found
    SymbolNotFound,  // var, immute, arg not found
    Incomplete,
    System,
    Parse,
    User,
    NotEqual,
    Eval,
    Unknown,
  };
  Type type_;
  string message_;
  };

//----------------------------------
  enum class Type { 
    Null, Bool, Error, Integer, Float, String, 
    Identifier, Tuple, List, Map, IMap, Vector, DeQue, LispOp, 
    ControlFlow, Atom, ObjectId, Raw, Unique, Fun };

  using Integer = LOOSH_T_LONG; 
  using Float = double;

  using List = list<unique_ptr<Loosh::Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using DeQue = deque<unique_ptr<Node>>;
  using ptr_R = Node *;
  using ptr_U = unique_ptr<Node>;
  using OpStatus = pair<bool, unique_ptr<Node>>;

  using IMap = unordered_map<Integer, unique_ptr<Node>>;
  using Map = unordered_map<string, unique_ptr<Node>>;
  using Fun = function<OpStatus(Node&, Node&, const Vector& list)>; // process, this, arguments

  using Value = variant<monostate, bool, Error, Integer, Float, string, Lisp::Op, List, Vector, DeQue, Map, IMap, ptr_R, ptr_U, Fun>;
  using ValueSimple = variant<monostate, bool, Error, Integer, Float, string, Lisp::Op>;

//----------------------------------
  
  Node();
  //explicit Node(Value val);
  Node(Value val);
  Node(Value v , Type t);
  ~Node() = default; 

  static ptr_U create_error(Error::Type err_type, const string& msg);
  static ptr_U create();
  static ptr_U create(Value v);
  //static ptr_U create(ValueSimple v);
  static ptr_U create(Value v, Type t);
  static ptr_U create(Type t);



  ptr_U clone() const;
  static ptr_U clone(const List& list) ;
  static ptr_U clone(const Vector& list) ;
  static ptr_U clone(const DeQue& list) ;
  static ptr_U clone(const Map& map) ;
  static ptr_U clone(const IMap& imap) ;
  static ptr_U clone(const Fun& fun) ;

  //clone_ptr_r() ;



  string _to_str() const ;

  static string _to_str(const Map&m) ;
  static string _to_str(const IMap&m) ;
  static string _to_str(const Vector&l) ;
  static string _to_str(const List&l) ;
  static string _to_str(const DeQue&l) ;
  static string _to_str(Type type);
  //Node to_str() const;


  Type value_variant_type();

//----------------------------------
  void nil();
  void  operator = (bool v);
  void  operator = (Integer v);
  void  operator = (Float v);
  void  operator = (string v);
  void  operator = (Error v);
  void  operator = (ptr_U v);
  //
  void set(unique_ptr<Node> new_node);

  // map

  OpStatus set(const string&key, unique_ptr<Node> child);
  OpStatus set(const string& key, Value v);
  OpStatus set(const vector<string>&path, unique_ptr<Node>child, bool override=false);
  bool extend(const vector<string>&path, bool override=false);

 static Node* extend_map_by_key(Map& map, const string&key, bool create=true); // for map




  OpStatus delete_key(const string &key);
  OpStatus delete_key(Integer key);



  uintptr_t GetObjectId(Node* obj) { return reinterpret_cast<uintptr_t>(obj); }


protected:
  Value value_;
  Type type_;
  bool isMarked = false;

private:
  bool type_set_identifier();
  bool type_set_atom();
  bool type_set_object_id();


};

};

ostream& operator<<(ostream& os, const Loosh::Node& v) ;
//ostream& operator<<(ostream& os, const Node::OpStatus& s) ;
//ostream& operator<<(ostream& os, const Node::OpStatusRef& s) ;

