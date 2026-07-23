#include "lang.hh"


using namespace std;
namespace Loosh 
{

const vector<string> Lang::atoms_key = {UNIVERSE, "Lang", "Atoms"};

unordered_map<Integer , string> Lang::Atoms;
std::hash<string> Lang::hasher;

Lang::Lang() {}

//------------------------------------------------------------------------
Integer Lang::str_to_atom(const string& input) {
  Integer hash_value = hasher(input);
  Atoms[hash_value] = input;
  return hash_value;
}

string Lang::atom_to_str(Integer v) {
  return Atoms[v];
}
string Lang::atom_to_str_imap(Integer v) {
  if (auto it = Atoms.find(v); it != Atoms.end()) 
    return Atoms[v];
  return  to_string(v)+"i";
}

string Lang::unqiue_name(const string& input) {
  unsigned long hash_value = hasher(input);
  return input + to_string(hash_value);
}



const Integer Lang::Atom::fun=str_to_atom("fun");
const Integer Lang::Atom::server=str_to_atom("server");
const Integer Lang::Atom::accept=str_to_atom("accept");
const Integer Lang::Atom::connect=str_to_atom("connect");
const Integer Lang::Atom::client=str_to_atom("client");
const Integer Lang::Atom::run=str_to_atom("run");
const Integer Lang::Atom::ok=str_to_atom("ok");
const Integer Lang::Atom::error=str_to_atom("error");
const Integer Lang::Atom::read=str_to_atom("read");
const Integer Lang::Atom::write=str_to_atom("write");
const Integer Lang::Atom::read_text=str_to_atom("read_text");
const Integer Lang::Atom::write_text=str_to_atom("write_text");
const Integer Lang::Atom::read_binary=str_to_atom("read_binary");
const Integer Lang::Atom::write_binary=str_to_atom("write_binary");
const Integer Lang::Atom::is_open=str_to_atom("is_open");
const Integer Lang::Atom::got_text=str_to_atom("got_text");
const Integer Lang::Atom::echo=str_to_atom("echo");
const Integer Lang::Atom::initialize=str_to_atom("initialize");
const Integer Lang::Atom::finalize=str_to_atom("finalize");
const Integer Lang::Atom::extract=str_to_atom("extract");
const Integer Lang::Atom::match=str_to_atom("match");
const Integer Lang::Atom::replace=str_to_atom("replace");
const Integer Lang::Atom::part=str_to_atom("part");
const Integer Lang::Atom::full=str_to_atom("full");


const Integer Lang::Atom::icase=str_to_atom("icase");
const Integer Lang::Atom::nosubs=str_to_atom("nosubs");
const Integer Lang::Atom::optimize=str_to_atom("optimize");
const Integer Lang::Atom::collate=str_to_atom("collate");
const Integer Lang::Atom::ecmas=str_to_atom("ecmas");
const Integer Lang::Atom::basic=str_to_atom("basic");
const Integer Lang::Atom::extended=str_to_atom("extended");
const Integer Lang::Atom::awk=str_to_atom("awk");
const Integer Lang::Atom::grep=str_to_atom("grep");
const Integer Lang::Atom::egrep=str_to_atom("egrep");

};