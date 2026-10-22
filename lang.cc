#include "lang.hh"
#include "atom.hh"
#include "node.hh"
#include "process.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh 
{


//unordered_map<UnsignedInteger , string> Lang::Atoms;
//unique_ptr<Node> Lang::Atoms=make_unique<Node>(Node::Type::IMap);

std::hash<string> Lang::hasher;


Lang::Lang(Node *r) : m_root(r), process_branch(r) {
  if(r->m_type != Node::Type::MetaObject) {
    auto msg =  "Lang::Lang(Node* root) not a MetaObject "   ;
    //spdlog::error(clean_function_name() + ": " +  msg);
    spdlog::error(msg);
   // MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }

  auto lang = m_root->create_meta();
  m_lang = lang.get();
  m_root->obj_atom_add(Atom::lang, move(lang));
}

void Lang::add_atoms(unique_ptr<Node>atoms) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)

  if(atoms->m_type != Node::Type::MetaObject){
    string msg =  "Lang::add_atoms(Node* root) not a MetaObject "   ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(clean_function_name() + ": " +  msg);
    MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }

  atoms->set_parent(m_root);
  m_atoms = atoms.get();
  m_root->obj_data_add(LOOSH_ATOMS, move(atoms));
}

//------------------------------------------------------------------------
UnsignedInteger Lang::str_to_atom(const string& str_value) {
  UnsignedInteger hashed_value = hasher(str_value);
  m_atoms->obj_atom_add(hashed_value,  Node::create(str_value));
  return hashed_value;
}



string Lang::atom_to_str(UnsignedInteger v) {
  auto &atom_ref = m_atoms->unwrap_value<IMap>();
  return atom_ref[v]->_to_str();
}

string Lang::atom_to_str_imap(UnsignedInteger v) {
  auto &atom_ref = m_atoms->unwrap_value<IMap>();
  //if (auto it = Atoms.find(v); it != Atoms.end()) 
  if (auto it = atom_ref.find(v); it != atom_ref.end()) 
    return atom_ref[v]->_to_str();
  return  to_string(v)+"i";
}

string Lang::unqiue_name(const string& input) {
  unsigned long hashed_value = hasher(input);
  return input + to_string(hashed_value);
}


};