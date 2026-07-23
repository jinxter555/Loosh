#include "lisp.hh"
#include "node.hh"
#include "defs.hh"
#include <iostream>


namespace Loosh 
{

Lisp::Lisp() : Lang() {}

string Lisp::_to_str(Lisp::Op op) {
  switch (op) {
    case Lisp::Op::root: return "root";
    case Lisp::Op::nil: return "nil";
    case Lisp::Op::kernel: return "kernel";
    case Lisp::Op::system: return "system";
    case Lisp::Op::process: return "process";
    case Lisp::Op::branch: return "branch";
    case Lisp::Op::namespace_: return "namespace";
    case Lisp::Op::interpreter: return "interpreter";
    case Lisp::Op::class_: return "class";
    case Lisp::Op::private_: return "private";
    case Lisp::Op::new_: return "new";
    case Lisp::Op::delete_: return "delete";
    case Lisp::Op::clone: return "clone";
    case Lisp::Op::use: return "use";
    case Lisp::Op::error: return "error";
    case Lisp::Op::noop: return "noop";
    case Lisp::Op::identifier: return "identifier";
    case Lisp::Op::scalar: return "scalar";
    case Lisp::Op::literal: return "literal";
    case Lisp::Op::quote: return "quote";
    case Lisp::Op::unquote: return "unquote";
    case Lisp::Op::list: return "list";
    case Lisp::Op::deque: return "deque";
    case Lisp::Op::vector: return "vector";
    case Lisp::Op::hash: return "hash";
    case Lisp::Op::ihash: return "ihash";
    case Lisp::Op::object: return "object";
    case Lisp::Op::integer_: return "integer";
    case Lisp::Op::float_: return "float";
    case Lisp::Op::number: return "number";
    case Lisp::Op::string_: return "string";

    case Lisp::Op::car: return "car";
    case Lisp::Op::cdr: return "cdr";
    case Lisp::Op::map: return "map";
    case Lisp::Op::index: return "index";
    case Lisp::Op::head: return "head";
    case Lisp::Op::body: return "body";
    case Lisp::Op::tail: return "tail";

    case Lisp::Op::add: return "add";
    case Lisp::Op::sub: return "sub";
    case Lisp::Op::mul: return "mul";
    case Lisp::Op::div: return "div";
    case Lisp::Op::mod: return "mod";

    case Lisp::Op::eq: return "eq";
    case Lisp::Op::neq: return "neq";
    case Lisp::Op::lt: return "lt";
    case Lisp::Op::gt: return "gt";
    case Lisp::Op::gteq: return "gteq";
    case Lisp::Op::lteq: return "lteq";
    case Lisp::Op::and_: return "and";
    case Lisp::Op::or_: return "or";
    case Lisp::Op::not_: return "not";

    case Lisp::Op::var: return "var";
    case Lisp::Op::assign: return "assign";
    case Lisp::Op::def: return "def";
    case Lisp::Op::call: return "call";
    case Lisp::Op::funcall: return "funcall";
    case Lisp::Op::curry: return "curry";
    case Lisp::Op::pipe: return "pipe";
    case Lisp::Op::spawn: return "spawn";
    case Lisp::Op::spin: return "spin";
    case Lisp::Op::sleep: return "sleep";
    case Lisp::Op::eval: return "eval";

    case Lisp::Op::call_extern: return "call_extern";
    case Lisp::Op::send: return "send";
    case Lisp::Op::ret: return "ret";
    case Lisp::Op::loop: return "loop";
    case Lisp::Op::while_: return "while";
    case Lisp::Op::return_: return "return";
    case Lisp::Op::exit_: return "exit_";
    case Lisp::Op::break_: return "break";
    case Lisp::Op::continue_: return "continue";

    case Lisp::Op::repeat: return "repeat";
    case Lisp::Op::for_: return "for";
    case Lisp::Op::do_: return "do";
    case Lisp::Op::faz: return "faz";
    case Lisp::Op::if_: return "if";
    case Lisp::Op::iif: return "iif";
    case Lisp::Op::cond: return "cond";
    case Lisp::Op::case_: return "case";
    case Lisp::Op::match: return "match";
    case Lisp::Op::when: return "when";
    case Lisp::Op::print: return "print";
    case Lisp::Op::printr: return "printr";
    case Lisp::Op::module_: return "module";
    case Lisp::Op::defun: return "defun";
    case Lisp::Op::defmacro: return "defmacro";
    case Lisp::Op::alias: return "alias";
    case Lisp::Op::lambda: return "lambda";
    case Lisp::Op::read: return "read";
    case Lisp::Op::readline: return "readline";
    case Lisp::Op::load: return "load";
    case Lisp::Op::require: return "require";
    case Lisp::Op::import: return "import";
    case Lisp::Op::typeof_: return "typeof";
    case Lisp::Op::size: return "size";
    case Lisp::Op::is_atom: return "is_atom";
    case Lisp::Op::is_integer: return "is_integer";
    case Lisp::Op::is_float: return "is_float";
    case Lisp::Op::is_string: return "is_string";
    case Lisp::Op::is_list: return "is_list";
    case Lisp::Op::is_deque: return "is_deque";
    case Lisp::Op::is_vector: return "is_vector";
    case Lisp::Op::is_cc_list: return "is_cc_list";
    case Lisp::Op::is_hash: return "is_hash";
    case Lisp::Op::is_ihash: return "is_ihash";
    default: {}
  }
  return "Unknown LispOp";
}


}