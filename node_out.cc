#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>

#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"




ostream& operator<<(ostream& os, const Loosh::Node& v) {
  //cout << "\naddr v:" <<  &v << " "; cout << v._to_str();
  //cout << "\n";
  cout << v._to_str();
  return os;
}
ostream& operator<<(ostream& os, const Loosh::Node::OpStatus& s) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_FUNC_INFO);
  if(s.first)  cout << "true: "; else cout << "false: ";

  if(s.second==nullptr) { 
    cout << "nullptr";
    return os;
  }
  cout << "value: " << s.second->_to_str() << ", type: " <<  Loosh::Node::_to_str(s.second->_get_type()) ;
//  s.second->print();
  return os;
}
ostream& operator<<(ostream& os, const Loosh::Node::OpStatusRef& s) {
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_FUNC_INFO);

  if(s.first)  cout << "true: "; else cout << "false: ";
  if(s.second._get_type() == Loosh::Node::Type::Null) {cout << "OS()<<Node::Nil"; return os;}
  cout << "value: " << s.second << ", type: " << Loosh::Node::_to_str(s.second._get_type());
  return os;
}


using namespace std;
namespace Loosh 
{

//------------------------------------------------------------------------
void Node::print(int depth) const { print_value_recursive(*this, depth); }

//------------------------------------------------------------------------
void Node::print_value_recursive(const Node& node, int depth) {
  if(depth==0) cout << "print recursive:\n";
  auto indent=[depth]() {
    for(int i = 0; i<depth; i++) cout << " ";
  };

  visit([&](auto&& arg) {
    using T = decay_t<decltype(arg)>;

    if constexpr (is_same_v<T, monostate>){
      cout << "Null";
    }
    else if constexpr (is_same_v<T, bool>){
      cout << "bool: " << arg;
    } else if constexpr (is_same_v<T, Error>){
      cout << "\033[31m[ERROR: " << Error::_to_str(arg.type_) << "]\033[0m: " << arg.message_;
    } else if constexpr (is_same_v<T, Integer>) {
      cout << arg; 
    } else if constexpr (is_same_v<T, Float>) {
      cout << fixed << setprecision(2) << arg; 
    } else if constexpr (is_same_v<T, Lisp::Op>) {
      cout << Lisp::_to_str(arg); 
    } else if constexpr (is_same_v<T, string>) {
      std::cout << "\"" << arg << "\""; 
    } else if constexpr (is_same_v<T, List>) {
      cout << "List["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << " ]";
    } else if constexpr (is_same_v<T, DeQue>) {
      cout << "DeQue["; 
      for(auto &e : arg) cout << *e <<","; 
      cout << " ]";
    } 
    else if constexpr (is_same_v<T, Vector>) {
      cout << "Vector[(size=" << arg.size() << ") " << endl;
      for(size_t i=0; i<arg.size(); ++i) {
        indent();
        cout  << "  - [" << i << ", Type: " << Node::_to_str(arg[i]->type_) << "]: ";
        print_value_recursive(*arg[i].get(), depth+1);
        cout << "\n";
      }
      indent(); 
      cout << " ]";
    } else if constexpr (is_same_v<T, Map>) {
      cout << "{ (Map, size=" << arg.size() << ") " << endl;
      for(const auto&[key, child_ptr] : arg) {

        indent(); 
        cout << "  - " << key << " (Type: " << Node::_to_str(child_ptr->type_) << "): ";
        //if(key == MODULE_PTR || key == CLASS_PTR) { cout << "==*ptr[" << &child_ptr->value_ << "]==\n"; continue; }
        if(key == MODULE_PTR || key == CLASS_PTR) { cout << "==*ptr[" << &child_ptr->get_node() << "]==\n"; continue; }
        //if(key == CURRENT_MODULE_PTR || key == CURRENT_CLASS_PTR) { cout << "###*ptr["<< &child_ptr->value_ << "]##\n"; continue; }
        if(key == CURRENT_MODULE_PTR || key == CURRENT_CLASS_PTR) { cout << "###*ptr["<< &child_ptr->get_node()<< "]##\n"; continue; }

        print_value_recursive(*child_ptr.get(), depth+1);
        cout << "\n";
      }
      indent();
      cout << " }";
    } else if constexpr (is_same_v<T, ptr_R>) {
      cout << "raw*:" << *arg;
    } else if constexpr (is_same_v<T, ptr_U>) {
      cout << "unique_ptr*:" << *arg;
    } else if constexpr (is_same_v<T, Fun>) {
      cout << "Fun*:" ;
    }


  }, node.value_);
}

//------------------------------------------------------------------------

}