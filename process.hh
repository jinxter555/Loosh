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
  Node* m_root;
public:
  class Index { public: enum { Pid, Frames, PPid}; };

  static unique_ptr<Node> create() ;
  static Node::OpStatusRef frame_current(Node&process)  ;


};




}

#endif