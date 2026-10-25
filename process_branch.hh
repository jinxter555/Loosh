#ifndef __PROCESS_H__
#define __PROCESS_H__
#pragma once

#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <unordered_map>                                                                        
#include <functional>

#include "defs.hh"
#include "environment.hh"

using namespace std;

namespace Loosh 
{

  class Frame;

//class Process : public Environment {
class Process : public Environment {
  friend class ProcessBranch;
private:
  void set_pid(UnsignedInteger pid);

public:
  Process();
  //unique_ptr<Process> create();
  unique_ptr<Process> create(UnsignedInteger pid);
  static unique_ptr<Process> create_kernel(ptr_R parent_node);

  UnsignedInteger _get_pid() ;
  OpStatus get_pid() ;
  Frame* push_frame();
  void  pop_frame();



};

// process under root->process->[0..max_pid_count]
class ProcessBranch {
  Node* m_root;
  Node* m_process; // this branch from root. root->process->[0..max]
public:
  class Index { public: enum { Pid, PPid, Frame, count}; };

  ProcessBranch(Node*r);

  Process* create_kernel() ;
  Process* create_process(Process&proc) ;
  //static unique_ptr<Node> create_process(Node&process_branch) ;
  static Node::OpStatusRef frame_current(Node&process)  ;

  Node::UnsignedInteger _get_next_pid() const;


};




}

#endif