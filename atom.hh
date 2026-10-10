#include "node.hh"

namespace Loosh 
{
class Atom {
protected:

  static std::hash<string> hasher;
public: 
  static const UnsignedInteger fun, server, client, connect, accept, run, ok, error, read, write, read_text, write_text, 
      read_binary, write_binary, is_open, got_text, echo, initialize, finalize,
      match, extract, replace, full, part,
      icase, nosubs, optimize, collate, ecmas, basic, extended, awk, grep, egrep,
      scope, frame, process
  ;

static Node::ptr_U atoms_uptr;
static Node::ptr_R atoms;

static  UnsignedInteger str_to_atom(const string& input);
static  string unqiue_name(const string& input);
static  string atom_to_str(UnsignedInteger v);
static  string atom_to_str_imap(UnsignedInteger v);




};



}
