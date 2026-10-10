#include "atom.hh"

namespace Loosh 
{
  
std::hash<string> Lang::hasher;
Node::ptr_U Atom::atoms_uptr = Node::create_meta();
Node::ptr_R Atom::atoms = Atom::atoms_uptr.get();

//------------------------------------------------------------------------
UnsignedInteger Atom::str_to_atom(const string& input) {
  UnsignedInteger hashed_value = hasher(input);
  //Atoms[hash_value] = input;
  //Atoms->add(hash_value,  Node::create(input));
  atoms->obj_atoms_add(hashed_value,  Node::create(input));
  //Atoms[hash_value] = Node::create(input);
  return hashed_value;
}



string Atom::atom_to_str(UnsignedInteger v) {
  auto &atom_ref = atoms->unwrap_value<IMap>();
  return atom_ref[v]->_to_str();
}

string Atom::atom_to_str_imap(UnsignedInteger v) {
  auto &atom_ref = atoms->unwrap_value<IMap>();
  //if (auto it = Atoms.find(v); it != Atoms.end()) 
  if (auto it = atom_ref.find(v); it != atom_ref.end()) 
    return atom_ref[v]->_to_str();
  return  to_string(v)+"i";
}

string Atom::unqiue_name(const string& input) {
  unsigned long hashed_value = hasher(input);
  return input + to_string(hashed_value);
}

};