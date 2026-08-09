#pragma once
#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <unordered_map>                                                                        
#include <functional>
#include <spdlog/spdlog.h>


#include "defs.hh"
#include "lisp.hh"


using namespace std;
namespace Loosh 
{


class Node {
friend class Tree;
friend class NodeObject;
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
    Unknown };
    //
    Error(Type t, const string msg="");
    static Node& ref(Type t); 
    static Node& ref(Type t, const string& msg); 
    static Node& ref_out(Type t, const string& msg);
    static Node& ref_log(Type t, const string& msg); 
    static string _to_str(Type t) ;
    static void init() ;
    static vector<unique_ptr<Node>> list;

    Type type_;
    string message_;
  };

//----------------------------------
// GCObjectId: for Garbage collection
// MapObjectId: 
  enum class Type { 
    Null, Bool, Error, Size, Integer, Float, String, 
    Identifier, Identifier_g,  Tuple, List, Map, IMap, Vector, DeQue, LispOp, 
    ControlFlow, Atom, ObjectId, ObjectMeta, Raw, Unique, Fun };

  using Integer = LOOSH_T_LONG; 
  using Float = double;

  using List = list<unique_ptr<Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using DeQue = deque<unique_ptr<Node>>;
  using ptr_R = Node *;
  using ptr_U = unique_ptr<Node>;
  using OpStatus = pair<bool, unique_ptr<Node>>;
  using OpStatusRef = pair<bool, Node&>;

  using IMap = unordered_map<Integer, unique_ptr<Node>>;
  using Map = unordered_map<string, unique_ptr<Node>>;
  using Fun = function<OpStatus(Node&, Node&, const Vector& list)>; // process, this, arguments

  using Value = variant<monostate, bool, Error, Integer, Float, string, Lisp::Op, List, Vector, DeQue, Map, IMap, ptr_R, ptr_U, Fun>;
  //using ValueSimple = variant<monostate, bool, Error, Integer, Float, string, Lisp::Op>;

//----------------------------------
  
  Node();
  //explicit Node(Value val);
  Node(Type t);
  Node(Value v);
  Node(ptr_U uptr) ;
  Node(ptr_R rptr) ;

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
  void set(const Integer, Type );
  void set(const string&, Type );

  // map
  OpStatus set(const string&key, unique_ptr<Node> child);
  OpStatus set(const string& key, Value v);
  OpStatus set(const vector<string>&path, unique_ptr<Node>child, bool override=false);
  static Node* extend_map_by_key(Map& map, const string&key, bool create=true); // for map
  bool extend(const vector<string>&path, bool create=true);
  //
  Node& get_node(); // returns node if it's ptrs shared raw unique

  OpStatusRef operator[](Integer index) ;
  OpStatusRef operator[](const string& key) ;
  OpStatusRef get_node(const string&key);
  OpStatusRef get_node(const vector<string>&path);
  OpStatusRef get_node(Integer index);

  bool has_node(const vector<string>&path);

  OpStatus delete_key(const string &key);
  OpStatus delete_key(Integer key);

  //
  Type _get_type() const;
  Type _get_value_type() const;
  Node get_type() const;

  // _get
  Integer _get_integer() const;
  Float _get_float() const;
  Lisp::Op _get_lisp_op() const;
  bool _get_bool() const;
  string _get_str() const;
  Map& _get_map_ref() ;
  Map& _get_map_ref(const string &key) ;
  IMap& _get_imap_ref() ;
  Vector& _get_vector_ref() ;
  DeQue& _get_deque_ref() ;
  List& _get_list_ref() ;
  ptr_R _get_ptr_r() const;

  //
  OpStatus add(unique_ptr<Node> child);
  OpStatus add(const string&key, unique_ptr<Node> child);
  //
  OpStatus pop_back();
  OpStatus pop_front();
  OpStatus push_front(unique_ptr<Node>node);
  OpStatus push_back(unique_ptr<Node>node);


  //
  OpStatus has_key(const string&key);
  bool m_has_key(const string&key);


  uintptr_t GetObjectId(Node* obj) { return reinterpret_cast<uintptr_t>(obj); }
  //

  //
  Node operator +(const Node& other) const;
  Node operator -(const Node& other) const;
  Node operator *(const Node& other) const;
  Node operator /(const Node& other) const;
  //
  Node operator >(const Node& other) const;
  Node operator <(const Node& other) const;
  Node operator >=(const Node& other) const;
  Node operator <=(const Node& other) const;
  Node operator ==(const Node& other) const;
  Node operator !=(const Node& other) const;
  //
  Node operator &&(const Node& other) const;
  Node operator ||(const Node& other) const;
  Node operator !() const;


  //
  void print(int depth=0) const;
  static void print_value_recursive(const Node& node, int depth=0);
  //static void print_value(const Value& node, int depth=0);




//------------------------------ node object


protected:
  Value value_;
  Type type_;
  bool isMarked = false;

//------------------------------ node object
  Node::OpStatus obj_meta_add(const string& meta_key, const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_meta_set(const string& meta_key, const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_meta_get(const string& meta_key, const string&key);

  Node::OpStatus obj_info_add(const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_info_set(const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_info_get(const string&key);


  Node::OpStatus obj_data_add(const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_data_set(const string&key, unique_ptr<Node> child);
  Node::OpStatus obj_data_get(const string&key);


//------------------------------ 
  

private:
  bool type_set_identifier();
  bool type_set_atom();
  bool type_set_object_id();


};


extern Node node_null;


};

ostream& operator<<(ostream& os, const Loosh::Node& v) ;
ostream& operator<<(ostream& os, const Loosh::Node::OpStatus& s) ;
ostream& operator<<(ostream& os, const Loosh::Node::OpStatusRef& s) ;

