#include "atom.hh"

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

namespace Loosh 
{
  
std::hash<string> Atom::hasher;

Node::ptr_U Atom::atoms_uptr = Node::create_meta();
Node::ptr_R Atom::atoms = Atom::atoms_uptr.get();

//------------------------------------------------------------------------
Node::UnsignedInteger Atom::str_to_atom(const string& input) {
  Node::UnsignedInteger hashed_value = hasher(input);
  //Atoms[hash_value] = input;
  //Atoms->add(hash_value,  Node::create(input));
  atoms->obj_atom_add(hashed_value,  Node::create(input));
  //Atoms[hash_value] = Node::create(input);
  return hashed_value;
}



string Atom::atom_to_str(Node::UnsignedInteger key) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  MYLOGGER_MSG(trace_function, string("index: ") + to_string(key), SLOG_NODE_OP+30)
  auto &imap = atoms->obj_get_imap();
  cout << "atoms: " << atoms->_to_str() << "\n";
  cout << "atom: index key: "  << key << "\n";

  return ":" + imap[key]->_to_str();
  //auto &atom_ref = atoms->unwrap_value<Node::IMap>();
  //return atom_ref[key]->_to_str();
}

string Atom::atom_to_str_imap(Node::UnsignedInteger key) {
  auto atom_ref_status = atoms->obj_atom_get(key);
  if(!atom_ref_status.first)  return  to_string(key)+"i";
  return ":" + atom_ref_status.second._to_str();
}

string Atom::unqiue_name(const string& input) {
  unsigned long hashed_value = hasher(input);
  return input + to_string(hashed_value);
}

const Node::UnsignedInteger Atom::fun=str_to_atom("fun");
const Node::UnsignedInteger Atom::server=str_to_atom("server");
const Node::UnsignedInteger Atom::accept=str_to_atom("accept");
const Node::UnsignedInteger Atom::connect=str_to_atom("connect");
const Node::UnsignedInteger Atom::client=str_to_atom("client");
const Node::UnsignedInteger Atom::run=str_to_atom("run");
const Node::UnsignedInteger Atom::ok=str_to_atom("ok");
const Node::UnsignedInteger Atom::error=str_to_atom("error");
const Node::UnsignedInteger Atom::read=str_to_atom("read");
const Node::UnsignedInteger Atom::write=str_to_atom("write");
const Node::UnsignedInteger Atom::read_text=str_to_atom("read_text");
const Node::UnsignedInteger Atom::write_text=str_to_atom("write_text");
const Node::UnsignedInteger Atom::read_binary=str_to_atom("read_binary");
const Node::UnsignedInteger Atom::write_binary=str_to_atom("write_binary");
const Node::UnsignedInteger Atom::is_open=str_to_atom("is_open");
const Node::UnsignedInteger Atom::got_text=str_to_atom("got_text");
const Node::UnsignedInteger Atom::echo=str_to_atom("echo");
const Node::UnsignedInteger Atom::initialize=str_to_atom("initialize");
const Node::UnsignedInteger Atom::finalize=str_to_atom("finalize");
const Node::UnsignedInteger Atom::extract=str_to_atom("extract");
const Node::UnsignedInteger Atom::match=str_to_atom("match");
const Node::UnsignedInteger Atom::replace=str_to_atom("replace");
const Node::UnsignedInteger Atom::part=str_to_atom("part");
const Node::UnsignedInteger Atom::full=str_to_atom("full");


const Node::UnsignedInteger Atom::icase=str_to_atom("icase");
const Node::UnsignedInteger Atom::nosubs=str_to_atom("nosubs");
const Node::UnsignedInteger Atom::optimize=str_to_atom("optimize");
const Node::UnsignedInteger Atom::collate=str_to_atom("collate");
const Node::UnsignedInteger Atom::ecmas=str_to_atom("ecmas");
const Node::UnsignedInteger Atom::basic=str_to_atom("basic");
const Node::UnsignedInteger Atom::extended=str_to_atom("extended");
const Node::UnsignedInteger Atom::awk=str_to_atom("awk");
const Node::UnsignedInteger Atom::grep=str_to_atom("grep");
const Node::UnsignedInteger Atom::egrep=str_to_atom("egrep");

const Node::UnsignedInteger Atom::scope=str_to_atom("scope");
const Node::UnsignedInteger Atom::frame=str_to_atom("frame");
const Node::UnsignedInteger Atom::process=str_to_atom("process");
const Node::UnsignedInteger Atom::pid=str_to_atom("pid");
const Node::UnsignedInteger Atom::parent_pid=str_to_atom("parent_pid");
const Node::UnsignedInteger Atom::parent=str_to_atom("parent");


const Node::UnsignedInteger Atom::lang=str_to_atom("lang");
const Node::UnsignedInteger Atom::lisp=str_to_atom("lisp");
const Node::UnsignedInteger Atom::atom=str_to_atom("atom");


const Node::UnsignedInteger Atom::class_=str_to_atom("class");
const Node::UnsignedInteger Atom::function_=str_to_atom("function");
const Node::UnsignedInteger Atom::ops=str_to_atom("ops");

const Node::UnsignedInteger Atom::line=str_to_atom("line");
const Node::UnsignedInteger Atom::col=str_to_atom("col");
const Node::UnsignedInteger Atom::value=str_to_atom("value");
const Node::UnsignedInteger Atom::type=str_to_atom("type");



};