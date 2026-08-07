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



namespace Loosh{

string Node::_to_str(Type type) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
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
    case Type::ObjectMeta: return "ObjectMeta";
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
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)

  switch(type_) {
  case Type::Null: return "nil";
  case Type::Bool: {
    bool b = get<bool>(value_);
    if(b== true) return "true";
    return "false";}

  case Type::Atom: {
    Integer num = get<Integer>(value_);
    return ":" + Lang::atom_to_str(num); 
  }
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

  
  case Type::List: {
      //cout << "_to_str() List\n";
      auto& cc_list = get<List>(value_);
      return _to_str(cc_list);}
  case Type::DeQue: {
      auto&  cc_dq= get<DeQue>(value_);
      return _to_str(cc_dq);}
  case Type::Vector: {
      //cout << "_to_str() vector\n";
      auto& cc_vec = get<Vector>(value_);
      return _to_str(cc_vec);}

  case Type::IMap: {
      auto& imap = get<IMap>(value_);
  return _to_str(imap);}
  case Type::ObjectMeta: 
  case Type::Map: {
      auto& map = get<Map>(value_);
      return _to_str(map);}

  case Type::Raw: {
    //cout << "\nraw to_str()\n";
    auto ptr_r = get<ptr_R>(value_);
    return "--*ptr_r["  +  addressToHexString( ptr_r ) + "]--";
  }
  case Type::Unique: {
    //cout << "uniqur_ptr to_str()";
    auto& ptr_u = get<ptr_U>(value_);
    return ptr_u->_to_str();
  }

  default: return "Unknown Node()"; }

}

//----------------------------------- cc map
string Node::_to_str(const Map&map) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)

  if(map.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map) {
    //cout << "Node::_to_str(const Map&map): key: " <<  key << ", val: " <<  val->_to_str() <<"\n";
    //cout << "to_str(Map&): key: " << key << "\n";
    MYLOGGER_MSG(trace_function, "key: " + key, SLOG_TO_STR);

    //if(val==nullptr) { cerr << "k: " << key << ", val=null\n"; return ""; }

    if(val) outstr = q + key + q  + ":" + " " + val->_to_str();
    else outstr = q + key + q  + colon + " " + "nil";

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



//----------------------------------- cc vec
string Node::_to_str(const Vector&cc_vec) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  size_t s = cc_vec.size(), i;
  //if(s==0) {return "Vector[]";}
  if(s==0) {return "():nil";}
  string outstr("Vector[");

  for(i=0; i<s-1; i++) {
    auto &e = cc_vec[i];
    if(e==nullptr) continue;
    outstr = outstr + e->_to_str() + ", ";
  }
  if(cc_vec[i]) 
    outstr = outstr + cc_vec[i]->_to_str() + "]";
   else 
    outstr = outstr + "NULLPTR" + "]";
  return outstr;
}
//----------------------------------- cc list

string Node::_to_str(const List&cc_list) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  size_t s = cc_list.size(), i=0;
  MYLOGGER_MSG(trace_function, string("size: ") + to_string(s), SLOG_TO_STR+30);
  if(s==0) {return "List[]";}

  string outstr("List[");

  for(auto &e : cc_list) {
    if(i==s-1) break;
    if(e==nullptr) {
      cerr << "list::_to_str() is null!\n";
      continue;
    }
    outstr = outstr + e->_to_str() + ", ";
    i++;
  }
  if(cc_list.empty()) return outstr + "]";
  auto& e = cc_list.back(); 
  // to prevent last back() node_ptr is null 

  if(e==nullptr)  return outstr + "]"; 
  return outstr + e->_to_str() +" ]";
}

//----------------------------------- cc dq
string Node::_to_str(const DeQue&cc_dq) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  size_t s = cc_dq.size();
  if(s==0) {return "DeQue[]";}
  string outstr("DeQue[");

  for(auto &e : cc_dq) {
    if(e==nullptr) continue;
    outstr = outstr + e->_to_str() + ", ";
  }
  outstr = outstr + " ]";
  return outstr;
}

//----------------------------------- cc imap
string Node::_to_str(const IMap&cc_imap) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)

  if(cc_imap.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : cc_imap) {
      //outstr = q + Lang::atom_to_str( key) + q  + colon + " " + val->_to_str();
      auto atom_key_str = Lang::atom_to_str_imap(key);
      if(atom_key_str.back() == 'i')
        outstr =  atom_key_str  + " " + val->_to_str();
      else
        outstr =  ":" + atom_key_str   + "  " + val->_to_str();

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