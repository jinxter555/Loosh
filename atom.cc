#include "atom.hh"

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
  atoms->obj_atoms_add(hashed_value,  Node::create(input));
  //Atoms[hash_value] = Node::create(input);
  return hashed_value;
}



string Atom::atom_to_str(Node::UnsignedInteger v) {
  auto &atom_ref = atoms->unwrap_value<Node::IMap>();
  return atom_ref[v]->_to_str();
}

string Atom::atom_to_str_imap(Node::UnsignedInteger v) {
  auto &atom_ref = atoms->unwrap_value<Node::IMap>();
  //if (auto it = Atoms.find(v); it != Atoms.end()) 
  if (auto it = atom_ref.find(v); it != atom_ref.end()) 
    return atom_ref[v]->_to_str();
  return  to_string(v)+"i";
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
};