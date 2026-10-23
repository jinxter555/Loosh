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


class Process : public Environment {


};

// process under root->process->[0..max_pid_count]
class ProcessBranch {
  Node* m_root;
  Node* m_process;
public:
  class Index { public: enum { Pid, PPid, Frame, count}; };

  ProcessBranch(Node*r);

  Process* create_kernel() ;
  Process* create_process(Node&parent_process) ;
  //static unique_ptr<Node> create_process(Node&process_branch) ;
  static Node::OpStatusRef frame_current(Node&process)  ;


};




}

#endif