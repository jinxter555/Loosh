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
#include <shared_mutex>
#include <atomic>
#include <unordered_set>


#include "defs.hh"


using namespace std;
namespace Loosh 
{


class Node {
friend class Tree;
friend class Lang;
friend class Lisp;
friend class ProcessBranch;
friend class LispReader;
friend class Environment;
friend class Scope;
friend class Frame;
friend class ostream;

public:

  enum class Op  : int
  { DONE=0, Lparen, Rparen, closurable_begin, closurable_end
  , root, nil, kernel, system, process, branch, namespace_, interpreter
  , class_, private_, new_, delete_, clone, use
  , error, noop
  , identifier, scalar, literal, quote, unquote, list, deque, vector, hash, ihash, object
  , atom, integer_, float_, number, string_, cc_vector, cc_list, cc_deque, cc_map, cc_imap
  , typeof_, size, is_atom, is_integer, is_float, is_string, is_list, is_deque, is_vector, is_cc_list, is_hash, is_ihash
  , var, setq, assign
  , car, cdr, map, index, head, tail, body
  , add, sub, div, slash=div, mul, mod, lt, gt, lteq, gteq, eq, neq, and_, or_, not_
  , read, readline, load, import, require
  , call, send, ret, call_extern, funcall, curry, pipe, spawn, spin, sleep
  , cond, print, printr, loop, eval, while_, return_, exit_, continue_, break_, repeat, for_, do_, if_, iif, case_, match, when
  , module_, def, defun, defmacro, alias, lambda, faz
  };

//----------------------------------
  struct Error {  enum class Type {
    DivideByZero, 
    InvalidOperation, // e.g., calling 'add' on an Integer node
    KeyAlreadyExists, // e.g., calling 'add' with a duplicate map key
    KeyNotFound, // e.g., calling 'add' with a duplicate map key
    IndexOutOfBounds,  // e.g., calling 'set' with an invalid list index
    IndexWrongType,  // e.g., calling 'set' with an invalid list index
    EmptyContainer,  // get front() or back() when list,queu,vector is empty
    Lock,
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
    Null, Token, Bool, Error, Size, Integer, UnsignedInteger, Float, String,
    Identifier, Identifier_g,  Tuple, List, Map, IMap, Set, Vector, DeQue, Op, 
    ControlFlow, Atom, ObjectId, MetaObject, SimpleObject, Raw, Unique, Fun, AtomicInteger, Lock}; 

    // simple object: only Info and data
  enum MetaObjectIndex {
    Info, 
    StringMap, 
    VectorArray,
    IntegerMap,
    Parent,
    MetaLock,
    WalkerCount,  // number of tree traverse walkers. if > 0, do not delete node
    cc_class,
    count}; // count is last element hack for counting size of this

  enum ProgramObjectIndex {
    ProgramName,
    Cache,
    Process,
    Atoms


  };

  enum class LockMode { Unlocked, Read, Write };


  using Integer = LOOSH_T_LONG; 
  using UnsignedInteger = unsigned LOOSH_T_LONG;
  using Atom = UnsignedInteger; 
  using Float = double;

  using List = list<unique_ptr<Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using MetaObject = Vector;
  using SimpleObject = Vector;
  using VecObject = Vector;
  using DeQue = deque<unique_ptr<Node>>;
  using ptr_R = Node *;
  using ptr_U = unique_ptr<Node>;
  using OpStatus = pair<bool, unique_ptr<Node>>;
  using OpStatusRef = pair<bool, Node&>;

  using IMap = unordered_map<UnsignedInteger, unique_ptr<Node>>;
  using Map = unordered_map<string, unique_ptr<Node>>;
  using Set = unordered_set<UnsignedInteger>;
  using Fun = function<OpStatus(Node&, Node&, const Vector& list)>; // process env, current node, this, arguments
  using LockFun = function<OpStatus(Node*, Node*, const Vector& list)>; // locked current node , interacting node, arguments
  using AtomicInteger = unique_ptr<atomic<Integer>>;
  using Lock = unique_ptr<shared_mutex>;

  
//----------------------------------


  //using Value = variant<monostate, bool, Error, Integer, Float, string, Lisp::Op, List, Vector, DeQue, Map, IMap, ptr_R, ptr_U, Fun, Lock>;
  using Value = variant<monostate, bool, Error, Integer, UnsignedInteger, Float, string, Op, List, Vector, DeQue, Map, IMap, Set, ptr_R, ptr_U, Fun, AtomicInteger, Lock>;

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

  static ptr_U create_lock(ptr_U node);
  static ptr_U create();
  static ptr_U create(Value v);
  //static ptr_U create(ValueSimple v);
  static ptr_U create(Value v, Type t);
  static ptr_U create(Type t);

  static ptr_U create_meta(ptr_R parent=nullptr);
  Node::OpStatus create_meta(const string& key);
  ptr_U create_meta_child();



  ptr_U clone() const;
  static ptr_U clone(const List& list) ;
  static ptr_U clone(const Vector& list) ;
  static ptr_U clone(const DeQue& list) ;
  static ptr_U clone(const Map& map) ;
  static ptr_U clone(const IMap& imap) ;
  static ptr_U clone(const Fun& fun) ;
  static ptr_U clone(const Lock& mtx) ;
  static ptr_U clone(const AtomicInteger&) ;

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
  void set(const UnsignedInteger, Type );
  void set(const string&, Type );

  // map
  OpStatus set(const string&key, unique_ptr<Node> child);
  OpStatus set(const UnsignedInteger key, unique_ptr<Node> child);
  OpStatus set(const string&key, Value v);
  OpStatus set(const vector<string>&path, unique_ptr<Node>child, bool override=false);
  static Node* extend_map_by_key(Map& map, const string&key, bool create=true); // for map
  bool extend(const vector<string>&path, bool create=true);

  //
  Node& get_node(); // returns node,  if it's raw unique ptr unwrap

  OpStatusRef operator[](UnsignedInteger index) ; // for only  vector
  OpStatusRef operator[](const string& key) ;
  //OpStatusRef get_imap_element(UnsignedInteger index); // for only imap aka atom
  // get leaf should be
  OpStatusRef get_node(const string&key);
  OpStatusRef get_node(const vector<string>&path);
  OpStatusRef get_node(UnsignedInteger index); // for only imap aka atom
  OpStatusRef get_node(const Node& key); // for only imap aka atom


  OpStatusRef get_subtree(const std::vector<std::string>& path);

  OpStatusRef traverse(const vector<string>&path);

  bool has_node(const vector<string>&path);

  OpStatus delete_key(const string &key);
  OpStatus delete_key(Integer key);

  //bool traverse_and_execute(const vector<string>&path, Lock::Mode, Fun &operation);
  OpStatus traverse_and_execute(const vector<string>&path, LockMode, LockFun&operation, Node* other, const Vector& list);
  OpStatus traverse_and_execute2(const vector<string>&path, LockMode, LockFun&operation, Node* other, const Vector& list);
  static OpStatusRef get_node_lockable(ptr_R& node_from, const vector<string>& path, int &start);
  inline bool is_lockable() ;

  //
  //template <typename T> const T& as() const;
  template <typename T> T& as() ;
  //template <typename T> const T& as() const;
  //template <typename T> const T* try_as() const;
  //template <typename T> T* try_as();
  //


  Type _get_type() const;
  Type _get_value_type() const;
  Node get_type() const;
//------------------------------------------------------------------------
/*
template <typename T> const T& get_value() const {
  return  get<T>(m_value);
}

template <typename T> T& get_value() {
  return const_cast<T&>(
    static_cast<const Node*>(this)->get_value<T>()
  );
}*/
//------------------------------------------------------------------------
  template <typename T> const T& get_value() const;
  template <typename T> T& get_value() ;

  template <typename T> const T& unwrap_value() const;
  template <typename T> T& unwrap_value() ;

  template <typename T> const T& unwrap_value(UnsignedInteger index) const;
  template <typename T> T& unwrap_value(UnsignedInteger index) ;


  template <typename T=Node> const T& unwrap_value(const string& key) const;
  template <typename T=Node> T& unwrap_value(const string& key) ;

  template <typename T> Type get_tmpl_type() const ;



//------------------------------------------------------------------------

  // _get
  Integer _get_integer() const;
  UnsignedInteger _get_unsigned_integer() const;
  Atom _get_atom() const;
  Float _get_float() const;
  Op _get_lisp_op() const;
  bool _get_bool() const;
  string _get_str() const;
  Map& _get_map_ref() ;
  Map& _get_map_ref(const string &key) ;
  IMap& _get_imap_ref() ;
  Vector& _get_vector_ref() ;
  DeQue& _get_deque_ref() ;
  List& _get_list_ref() ;
  ptr_R _get_ptr_r() ;
  ptr_U _get_ptr_u() ;
  //ptr_R _get_meta_ptr_r() ;

  vector<string> get_map_keys();
  vector<string> get_imap_keys();
  vector<Integer> get_imap_ikeys();


  //
  OpStatus add(unique_ptr<Node> child);
  OpStatus add(const string&key, unique_ptr<Node> child);
  OpStatus add(const UnsignedInteger key, unique_ptr<Node> child);
  //
  OpStatus pop_back();
  OpStatus pop_front();
  OpStatus push_front(unique_ptr<Node>node);
  OpStatus push_back(unique_ptr<Node>node);
  OpStatusRef front();
  OpStatusRef back();


  UnsignedInteger _size() const ;
  OpStatus size() const ;
  //
  OpStatus is_in_range(const Integer index); // if integer is in range of a sequence, vector, list or deque
  OpStatus has_key(const string&key);
  OpStatus has_atom(const Atom key);

    bool empty_container() const;


  bool _is_in_range(UnsignedInteger index);
  bool _has_key(const string&key);
  bool _has_atom(const UnsignedInteger key);


  //template <typename T>  bool _has_key(const T& key) const;
  //
  bool is_nil(); 



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




//------------------------------ node object, aka meta object
//  Node::OpStatus obj_meta_add(const string& meta_key, const string&key, unique_ptr<Node> child);
//  Node::OpStatus obj_meta_set(const string& meta_key, const string&key, unique_ptr<Node> child);
//  Node::OpStatus obj_meta_get(const string& meta_key, const string&key);

  IMap&  obj_get_imap();
  Map&  obj_get_map();
  Vector&  obj_get_vector();

  OpStatus obj_info_add(const string&key, unique_ptr<Node> child);
  OpStatus obj_info_set(const string&key, unique_ptr<Node> child);
  OpStatusRef obj_info_get(const string&key);
  UnsignedInteger obj_info_size();


  OpStatus obj_data_add(const string&key, unique_ptr<Node> child);
  OpStatus obj_data_set(const string&key, unique_ptr<Node> child);
  UnsignedInteger obj_data_size();

  OpStatus obj_atom_add(const UnsignedInteger key, unique_ptr<Node> child);
  OpStatus obj_atom_set(const UnsignedInteger key, unique_ptr<Node> child);
  OpStatusRef obj_atom_get(const UnsignedInteger key);
  UnsignedInteger _obj_atom_size();

  OpStatus obj_array_push_back(ptr_U);
  OpStatusRef obj_array_get(UnsignedInteger);
  UnsignedInteger obj_array_size() const;


  OpStatusRef obj_data_get(const string&key);
//------------------------------ 

  bool set_parent(ptr_R parent);
  ptr_R _get_parent();
  OpStatus get_parent();
//------------------------------ 


  OpStatus lock_shared() const;
  OpStatus lock_exclusive() const;
  OpStatus lock_release() const;
  LockMode lock_get_state(const Lock &) ;

  static Node::Atom _get_obj_type(Node* env_ptr);
  static Node::OpStatus get_obj_type(Node* env_ptr);




protected:
  //mutable Value m_value;
  Value m_value;
  Type m_type;
  bool m_is_marked = false;

//------------------------------ node object

//------------------------------ 
  

private:
  bool type_set_identifier();
  bool type_set_atom();
  bool type_set_object_id();

  static MetaObject create_meta_vec();
  static SimpleObject create_simple_vec();

  string to_str_meta() const ;

};


class MetaNode : public Node {
  MetaNode() : Node(Type::Vector){}
  MetaNode(Node::Type t) ;

  enum Index {
    Info, 
    StringMap, 
    VectorArray,
    IntegerMap,
    Parent,
    MetaLock,
    WalkerCount,  // number of tree traverse walkers. if > 0, do not delete node
    cc_class,
    count}; // count is last element hack for counting size of this
  unique_ptr<MetaNode> create();

};

class Token: public Node {
public:
  Token() ;
  //enum class Type {};
  using Type = Op; 
  static unique_ptr<Token> create(Type t, Value v, UnsignedInteger l, UnsignedInteger c ) ; 

};


extern Node node_null;





};


//#include "node_tmpl_cc.hh"


ostream& operator<<(ostream& os, const Loosh::Node& v) ;
ostream& operator<<(ostream& os, const Loosh::Node::OpStatus& s) ;
ostream& operator<<(ostream& os, const Loosh::Node::OpStatusRef& s) ;

