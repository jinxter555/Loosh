#include "atom.hh"
#include "process_branch.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;

namespace Loosh 
{

//------------------------------------------------------------------------ 

Process::Process() : Environment(Node::Type::MetaObject) {}

unique_ptr<Process> Process::create() {
  auto proc = make_unique<Process>();
}
unique_ptr<Process> Process::create_kernel(ptr_R parent_node ) {
  auto proc = make_unique<Process>();
  proc->obj_atom_add(Loosh::Atom::pid, Node::create(UnsignedInteger(0)));
  proc->obj_atom_add(Loosh::Atom::parent_pid, Node::create(0));
  proc->set_parent(parent_node);
}

//------------------------------------------------------------------------ 
ProcessBranch::ProcessBranch(Node*r) :  m_root(r){
  if(r->m_type != Node::Type::MetaObject) {
    auto msg =  "Lang::Lang(Node* root) not a MetaObject "   ;
    spdlog::error(msg);
    throw std::bad_typeid();
  }

  auto pb = Node::create_meta(m_root);
  m_process= pb.get();
  m_root->obj_atom_add(Atom::process, move(pb));


}

Process* ProcessBranch::create_process(Node&parent_process) {
  Node::Vector cc_vec(Index::count); 

  m_process->push_back(Node::create (move(cc_vec)));

}


Process* ProcessBranch::create_kernel() {
  if(m_process->obj_array_size()> 0) {
    auto msg =  "kernel process space has already been created"   ;
    spdlog::error(msg);
    throw std::bad_typeid();
  }
  auto proc = Process::create_kernel(m_process);
  auto ptr = proc.get();

  m_process->push_back(move(proc));
  return ptr; //return static_cast<Process*>(ptr);
}

Node::OpStatusRef ProcessBranch::frame_current(Node&process)  {
  MYLOGGER(trace_function, "LispExpr::frame_current(Node& process)", __func__, SLOG_FUNC_INFO);

  auto frames_ref_status = process[Index::Frame];
  //cout << "frame_current(): frames_ref_status " << frames_ref_status << "\n";

  if(!frames_ref_status.first) {
    cerr << "frames[] doesn't exist!\n";
    return frames_ref_status;
  }
  auto s = frames_ref_status.second.size();

  auto frame_ref_back_status = frames_ref_status.second.back();
  if(!frame_ref_back_status.first) {
    cerr << "frames back() doesn't exist!\n";
  }
  return frame_ref_back_status;
}



//------------------------------------------------------------------------ 
}