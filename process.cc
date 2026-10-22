#include "atom.hh"
#include "process.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;

namespace Loosh 
{


ProcessBranch::ProcessBranch(Node*r) :  m_root(r){
  if(r->m_type != Node::Type::MetaObject) {
    auto msg =  "Lang::Lang(Node* root) not a MetaObject "   ;
    spdlog::error(msg);
    throw std::bad_typeid();
  }

  auto pb = m_root->create_meta();
  m_process= pb.get();
  m_root->obj_atom_add(Atom::process, move(pb));


}

Node::ptr_U ProcessBranch::create_process(Node&parent_process) {
  Node::Vector cc_vec(Index::count); 

  m_process->push_back(Node::create (move(cc_vec)));

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



}