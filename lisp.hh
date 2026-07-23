#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "lang.hh"
#include "tree.hh"
//#include "node.hh"

using namespace  std;





namespace Loosh 
{


//class Lisp : public Lang {
class Lisp : public Lang {
  friend class Node;

public:
  enum class Op  : int
  { root, nil, kernel, system, process, branch, namespace_, interpreter
  , class_, private_, new_, delete_, clone, use
  , error, noop
  , identifier, scalar, literal, quote, unquote, list, deque, vector, hash, ihash, object
  , atom, integer_, float_, number, string_, cc_vector, cc_list, cc_deque, cc_map, cc_imap
  , typeof_, size, is_atom, is_integer, is_float, is_string, is_list, is_deque, is_vector, is_cc_list, is_hash, is_ihash
  , var, assign
  , car, cdr, map, index, head, tail, body
  , add, sub, div, mul, mod, lt, gt, lteq, gteq, eq, neq, and_, or_, not_
  , read, readline, load, import, require
  , call, send, ret, call_extern, funcall, curry, pipe, spawn, spin, sleep
  , cond, print, printr, loop, eval, while_, return_, exit_, continue_, break_, repeat, for_, do_, if_, iif, case_, match, when
  , module_, def, defun, defmacro, alias, lambda, faz
  };
  using Type=Op;
  Lisp();
  static string _to_str(Lisp::Op op);
};

}
