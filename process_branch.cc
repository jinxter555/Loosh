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

Process::Process() : Environment() {}

// pid comes from ProcessBranch 
unique_ptr<Process> Process::create(UnsignedInteger new_pid, UnsignedInteger ppid) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  auto proc = make_unique<Process>();
  proc->atom_add(Loosh::Atom::pid, Node::create(new_pid));
  proc->atom_add(Loosh::Atom::ppid, Node::create(ppid));

  auto frame_uptr = Node::create(Node::Type::Vector);
  proc->frame_vec = frame_uptr.get();

  proc->atom_add(Loosh::Atom::frame_vec, move(frame_uptr));


  //proc->set_parent(Meta::_get_parent()); // _get_parent node
  //cout << clean_function_name() << ": *proc:  " << proc->_to_str() << "\n\n";

  return proc;
}


Node::UnsignedInteger Process::_get_pid() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  auto pid_status = atom_get(Loosh::Atom::pid);
  if(!pid_status.first) { }
  return pid_status.second._get_unsigned_integer();


}

void Process::set_pid(Node::UnsignedInteger pid) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  atom_set(Loosh::Atom::pid, Node::create(pid));
}
void Process::set_ppid(Node::UnsignedInteger ppid) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  atom_set(Loosh::Atom::ppid, Node::create(ppid));
}

Frame *Process::push_frame() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  AUTO_TRACE();

  //cout << "process push from *this: " << _to_str() << "\n\n";
  auto frame_branch_status = atom_get(Loosh::Atom::frame_vec);
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
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS);
  AUTO_TRACE();

  auto frame_branch_status = atom_get(Loosh::Atom::frame_vec);
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
ProcessBranch::ProcessBranch(Meta*r) :  m_root(r){

  //auto pb = Meta::create(m_root);
  auto pb = m_root->create_child("process branch");
  m_process = pb.get();
  m_root->atom_add(Atom::process, move(pb));

}

Process* ProcessBranch::create_process(Process& current_process ) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)

  auto pid = _get_next_pid();
  //auto proc =  current_process.create(pid, current_process._get_pid());
  auto proc =  Process::create(pid, current_process._get_pid());
  auto ptr =  proc.get();
  m_process->atom_add(pid,  move(proc));
  return ptr;

}


Process* ProcessBranch::create_kernel() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  AUTO_TRACE();

  //cout << "create kernel\n";
 /*
  if(m_process->array_size()> 0) {
    auto msg =  "kernel process space has already been created"   ;
    spdlog::error(msg);
    throw std::bad_typeid();
  }
*/

  auto proc = Process::create(_get_next_pid(), 0 );
  proc->push_frame()->push_scope();
  auto ptr = proc.get();

  m_process->atom_add(0,  move(proc));
  return ptr; 
}

Node::OpStatusRef ProcessBranch::frame_current(Node&process)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)

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


Node::UnsignedInteger ProcessBranch::_get_next_pid() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_PROCESS)
  return pid_current++;
}

//------------------------------------------------------------------------ 
}