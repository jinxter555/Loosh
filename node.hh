#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <unordered_map>                                                                        
#include <functional>


using namespace std;
namespace Loosh 
{

class Node {
public:
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

  enum class Type { 
    Null, Bool, Error, Integer, Float, String, 
    Identifier, Tuple, List, Map, IMap, Vector, DeQue, LispOp, ProcState, 
    ControlFlow, Atom, ObjectId, Shared, Raw, Unique, Fun };

  using Integer = long; using Float = double;

  using List = list<unique_ptr<Loosh::Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using DeQue = deque<unique_ptr<Node>>;
  using ptr_R = Node *;
  using ptr_U = unique_ptr<Node>;
  using OpStatus = pair<bool, unique_ptr<Node>>;

  using IMap = unordered_map<Integer, unique_ptr<Node>>;
  using Map = unordered_map<string, unique_ptr<Node>>;
  using Fun = function<OpStatus(Node&, Node&, const Vector& list)>; // process, this, arguments

  using Value = variant<monostate, bool, Error, Integer, Float, string, List, Vector, DeQue, Map, IMap, ptr_R, ptr_U, Fun>;
  //using Value = variant<monostate, bool, Error, Integer, Float, string, List, Vector, DeQue, ptr_R, Fun, IMap>;
  //using Value = variant<monostate, bool, Error, Integer, Float, string, ptr_R, ptr_U>;


  
  Node();
  explicit Node(Value val);
  //Node(Value val);
  Node(Value v , Type t);
  //Node(Map v , Type t);

  ptr_U create_error(Error::Type err_type, const string& msg);
  static ptr_U create();
  static ptr_U create(Value v);
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

  ~Node() = default; 

protected:
  Value value_;
  Type type_;
  bool isMarked = false;


};

};

ostream& operator<<(ostream& os, const Loosh::Node& v) ;
//ostream& operator<<(ostream& os, const Node::OpStatus& s) ;
//ostream& operator<<(ostream& os, const Node::OpStatusRef& s) ;

