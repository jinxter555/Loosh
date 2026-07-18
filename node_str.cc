#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include "node.hh"
#include "defs.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#define LOC_FUN source_location::current().function_name()


namespace Loosh{

string Node::_to_str(Type type) {
  switch (type) {
    case Type::Null: return "Null";
    case Type::Bool: return "Bool";
    case Type::Error: return "Error";
    case Type::Integer: return "Integer";
    case Type::Float: return "Float";
    case Type::String: return "String";
    case Type::Tuple: return "Tuple";
    case Type::List: return "List";
    case Type::Vector: return "Vector";
    case Type::DeQue: return "DeQue";
    case Type::Map: return "Map";
    case Type::IMap: return "IMap";
    case Type::Atom: return "Atom";
    case Type::ObjectId: return "ObjectId";
    case Type::LispOp: return "LispOp";
    case Type::Identifier: return "Identifier";
    case Type::Raw: return "RawPtr";
    case Type::Unique: return "UniquePtr";
    case Type::Fun: return "Function";
    default:  return "Unknown Type";
  }
  return "Unknown Type";
}

string Node::_to_str() const {
  //MYLOGGER(trace_function, source_location::current().function_name(), __func__, SLOG_TO_STR);
  MYLOGGER(trace_function, LOC_FUN, LOC_FUN, SLOG_TO_STR);

  switch(type_) {
  case Type::Null: return "nil";
  case Type::Bool: {
    bool b = get<bool>(value_);
    if(b== true) return "true";
    return "false";}

  case Type::Integer: {
      Integer num = get<Integer>(value_);
      return to_string(num); }
  case Type::Float:  {
      ostringstream oss;
      Float num = get<Float>(value_);
      oss << fixed << setprecision(2) << num;
      return oss.str(); }
  case Type::Identifier: 
  case Type::String: {
    string str = get<string>(value_);
    return str; }
  case Type::Raw: {
    //cout << "\nraw to_str()\n";
    auto& ptr_r = get<ptr_R>(value_);
    return ptr_r->_to_str();
  }
  case Type::Unique: {
    //cout << "uniqur_ptr to_str()";
    auto& ptr_u = get<ptr_U>(value_);
    return ptr_u->_to_str();
  }

  default: return "Unknown Node()"; }

}

string Node::_to_str(const Map&map) {
  MYLOGGER(trace_function, "Node::_to_str(const Map&map)", __func__, SLOG_TO_STR);

  if(map.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map) {
    //cout << "Node::_to_str(const Map&map): key: " <<  key << ", val: " <<  val->_to_str() <<"\n";
    //cout << "to_str(Map&): key: " << key << "\n";
    MYLOGGER_MSG(trace_function, "key: " + key, SLOG_TO_STR);

    if(val==nullptr) {cerr << "val is null\n"; return "";}
    if(key == MODULE_PTR || key == CLASS_PTR  || key == CURRENT_CLASS_PTR
      || key == CURRENT_MODULE_PTR || key == CURRENT_FUNCTION_PTR || key == UNIVERSE) {
      //outstr = q + key + q  + colon + "--*ptr--";
      //outstr = q + key + q  + colon + "--*ptr["  +  addressToHexString( &val->get_node()) + "]--";
      outstr = q + key + q  + colon + "--*ptr[]--";
    } else  {
      if(val) outstr = q + key + q  + colon + " " + val->_to_str();
      else outstr = q + key + q  + colon + " " + "NULL-VAL";
    }
    kv_paires.push_back(outstr);
  }

  outstr="{";
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return (outstr);
}





};