#include "lang.hh"
#include "node.hh"


using namespace std;
namespace Loosh 
{


//unordered_map<UnsignedInteger , string> Lang::Atoms;
unique_ptr<Node> Lang::Atoms=make_unique<Node>(Node::Type::IMap);

std::hash<string> Lang::hasher;


Lang::Lang(Node *r) : root(r) {
  if(r->m_type != Node::Type::MetaObject) {
    auto msg =  "Lang::Lang(Node* root) not a MetaObject "   ;
    //spdlog::error(clean_function_name() + ": " +  msg);
    spdlog::error(msg);
   // MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }
  //Node a(move(Atoms), Node::Type::IMap);



}

//------------------------------------------------------------------------
UnsignedInteger Lang::str_to_atom(const string& input) {
  UnsignedInteger hash_value = hasher(input);
  //Atoms[hash_value] = input;
  Atoms->add(hash_value,  Node::create(input));
  //Atoms[hash_value] = Node::create(input);
  return hash_value;
}



string Lang::atom_to_str(UnsignedInteger v) {
  auto &atom_ref = Atoms->unwrap_value<IMap>();
  return atom_ref[v]->_to_str();
}

string Lang::atom_to_str_imap(UnsignedInteger v) {
  auto &atom_ref = Atoms->unwrap_value<IMap>();
  //if (auto it = Atoms.find(v); it != Atoms.end()) 
  if (auto it = atom_ref.find(v); it != atom_ref.end()) 
    return atom_ref[v]->_to_str();
  return  to_string(v)+"i";
}

string Lang::unqiue_name(const string& input) {
  unsigned long hash_value = hasher(input);
  return input + to_string(hash_value);
}


const UnsignedInteger Lang::Atom::fun=str_to_atom("fun");
const UnsignedInteger Lang::Atom::server=str_to_atom("server");
const UnsignedInteger Lang::Atom::accept=str_to_atom("accept");
const UnsignedInteger Lang::Atom::connect=str_to_atom("connect");
const UnsignedInteger Lang::Atom::client=str_to_atom("client");
const UnsignedInteger Lang::Atom::run=str_to_atom("run");
const UnsignedInteger Lang::Atom::ok=str_to_atom("ok");
const UnsignedInteger Lang::Atom::error=str_to_atom("error");
const UnsignedInteger Lang::Atom::read=str_to_atom("read");
const UnsignedInteger Lang::Atom::write=str_to_atom("write");
const UnsignedInteger Lang::Atom::read_text=str_to_atom("read_text");
const UnsignedInteger Lang::Atom::write_text=str_to_atom("write_text");
const UnsignedInteger Lang::Atom::read_binary=str_to_atom("read_binary");
const UnsignedInteger Lang::Atom::write_binary=str_to_atom("write_binary");
const UnsignedInteger Lang::Atom::is_open=str_to_atom("is_open");
const UnsignedInteger Lang::Atom::got_text=str_to_atom("got_text");
const UnsignedInteger Lang::Atom::echo=str_to_atom("echo");
const UnsignedInteger Lang::Atom::initialize=str_to_atom("initialize");
const UnsignedInteger Lang::Atom::finalize=str_to_atom("finalize");
const UnsignedInteger Lang::Atom::extract=str_to_atom("extract");
const UnsignedInteger Lang::Atom::match=str_to_atom("match");
const UnsignedInteger Lang::Atom::replace=str_to_atom("replace");
const UnsignedInteger Lang::Atom::part=str_to_atom("part");
const UnsignedInteger Lang::Atom::full=str_to_atom("full");


const UnsignedInteger Lang::Atom::icase=str_to_atom("icase");
const UnsignedInteger Lang::Atom::nosubs=str_to_atom("nosubs");
const UnsignedInteger Lang::Atom::optimize=str_to_atom("optimize");
const UnsignedInteger Lang::Atom::collate=str_to_atom("collate");
const UnsignedInteger Lang::Atom::ecmas=str_to_atom("ecmas");
const UnsignedInteger Lang::Atom::basic=str_to_atom("basic");
const UnsignedInteger Lang::Atom::extended=str_to_atom("extended");
const UnsignedInteger Lang::Atom::awk=str_to_atom("awk");
const UnsignedInteger Lang::Atom::grep=str_to_atom("grep");
const UnsignedInteger Lang::Atom::egrep=str_to_atom("egrep");

const UnsignedInteger Lang::Atom::scope=str_to_atom("scope");
const UnsignedInteger Lang::Atom::frame=str_to_atom("frame");
const UnsignedInteger Lang::Atom::process=str_to_atom("process");

};