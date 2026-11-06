#include "lisp.hh"

namespace Loosh 
{

Node::OpStatus Lisp::add(Node& process, const Vector& cc_vec, UnsignedInteger start) {
  unique_ptr<Node> result = make_unique<Node>(0);
  UnsignedInteger s = cc_vec.size();

/*
  for(UnsignedInteger i=start; i <s; i++) {
    auto& element = cc_vec[i];
    auto ev_status = eval(process, *element);
      if(!ev_status.first) {
          cerr << "builtin_add eval() error: " << ev_status.second->_to_str() << "\n";
          return ev_status;
      }
      if(ev_status.first) *result = *result + *ev_status.second;
    }
    return {true, move(result)};
  } 
  return {false, Node::create()};
}
*/
}