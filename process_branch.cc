#include "atom.hh"
#include "process_branch.hh"
#include "frame.hh"

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;

namespace Loosh 
{

//------------------------------------------------------------------------ 

Process::Process() : Environment(Node::Type::MetaObject) {}

unique_ptr<Process> Process::create(UnsignedInteger pid) {
  auto proc = make_unique<Process>();
  proc->obj_atom_add(Loosh::Atom::pid, Node::create(pid));
  proc->obj_atom_add(Loosh::Atom::parent_pid, Node::create(_get_pid()));
  proc->obj_atom_add(Loosh::Atom::frame, Node::create(Node::Type::Vector));
  proc->set_parent(Node::_get_parent()); // _get_parent node
  return proc;
}


unique_ptr<Process> Process::create_kernel(ptr_R parent_node ) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto proc = make_unique<Process>();
  proc->obj_atom_add(Loosh::Atom::pid, Node::create(UnsignedInteger(0)));
  proc->obj_atom_add(Loosh::Atom::parent_pid, Node::create(UnsignedInteger(0)));
  proc->set_parent(parent_node);
  return proc;
}

Node::UnsignedInteger Process::_get_pid() {
  auto pid_status = obj_atom_get(Loosh::Atom::pid);
  if(!pid_status.first) { }
  return pid_status.second._get_unsigned_integer();


}

void Process::set_pid(Node::UnsignedInteger pid) {
  obj_atom_set(Loosh::Atom::pid, Node::create(pid));
}

Frame *Process::push_frame() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto frame_branch_status = obj_atom_get(Loosh::Atom::frame);
  if(!frame_branch_status.first){
    string msg = "push  frame error!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::system_error();
  }
  auto frame = make_unique<Frame>();
  auto ptr = frame.get();
  frame_branch_status.second.push_back(move(frame));
  return ptr;
}
void Process::pop_frame() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto frame_branch_status = obj_atom_get(Loosh::Atom::frame);
  if(!frame_branch_status.first){
    string msg = "pop  frame error!";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw std::system_error();
  }
  frame_branch_status.second.pop_back();
}

/*
unique_ptr<Process> Process::create() 
  auto proc = make_unique<Process>();
  proc->obj_atom_add(Loosh::Atom::pid, Node::create(UnsignedInteger(0)));
  proc->obj_atom_add(Loosh::Atom::parent_pid, Node::create(UnsignedInteger(0)));
  proc->set_parent(Node::_get_parent()); // _get_parent node
  return proc;
}
 */
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

Process* ProcessBranch::create_process(Process& current_process ) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)

  auto proc =  current_process.create(_get_next_pid());
  auto proc_ptr =  proc.get();
  m_process->push_back(move(proc));
  return proc_ptr;

}


Process* ProcessBranch::create_kernel() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  AUTO_TRACE();
  cout << "create kernel\n";

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
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)

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


Node::UnsignedInteger ProcessBranch::_get_next_pid() const {
  return m_process->obj_array_size();
}

//------------------------------------------------------------------------ 
}