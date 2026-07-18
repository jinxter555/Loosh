#include <iostream>
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
  MYLOGGER(trace_function, "ostream& << (Node::OpStatus&)", __func__, SLOG_FUNC_INFO);
  if(s.first)  cout << "true: "; else cout << "false: ";

  if(s.second==nullptr) { 
    cout << "nullptr";
    return os;
  }
  //cout << "value: " << s.second->_to_str() << ", type: " <<  Loosh::Node::_to_str(s.second->_get_type()) ;
//  s.second->print();
  return os;
}
/*
ostream& operator<<(ostream& os, const Loosh::Node::OpStatusRef& s) {
  MYLOGGER(trace_function, "ostream& << (Node::OpStatusRef&)", __func__, SLOG_FUNC_INFO);
  if(s.first)  cout << "true: "; else cout << "false: ";
  if(s.second._get_type() == Node::Type::Null) {cout << "OS()<<Node::Nil"; return os;}
  cout << "value: " << s.second << ", type: " << Node::_to_str(s.second._get_type());
  return os;
}
*/