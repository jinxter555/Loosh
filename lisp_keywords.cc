#include "node.hh"
#include "lisp.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

namespace Loosh 
{
//------------------------------------------------------------------------ Lisp Expr Keywords
void Lisp::set_op_str() {
  auto map_ = make_unique<Node>(Node::Type::Map);

  map_->set("kernel", Op::kernel);
  map_->set("system", Op::system);
  map_->set("process", Op::process);
  map_->set("interpreter", Op::interpreter);
  map_->set("namespace", Op::namespace_);
  map_->set("nil",   Op::nil);
  map_->set("root",   Op::root);
  map_->set("new",   Op::new_);
  map_->set("delete",   Op::delete_);
  map_->set("class",   Op::class_);
  map_->set("private",   Op::private_);
  map_->set("new", Op::new_);
  map_->set("clone", Op::clone);
  map_->set("use", Op::use);
  map_->set("error",Op::error);
  map_->set("noop", Op::noop);
  map_->set("identifier", Op::identifier);
  map_->set("scalar", Op::scalar);
  map_->set("literal", Op::literal);
  map_->set("quote", Op::quote);
  map_->set("unquote", Op::unquote);
  map_->set("list", Op::list);
  map_->set("vector", Op::vector);
  map_->set("deque", Op::deque);
  map_->set("hash", Op::hash);
  map_->set("ihash", Op::ihash);
  map_->set("cc_list", Op::cc_list);
  map_->set("cc_deque", Op::cc_deque);
  map_->set("cc_vector", Op::cc_vector);
  map_->set("var", Op::var);
  map_->set("assign", Op::assign);
  map_->set("car", Op::car);
  map_->set("cdr", Op::cdr);
  map_->set("map", Op::map);
  map_->set("index", Op::index);
  map_->set("head", Op::head);
  map_->set("body", Op::body);
  map_->set("tail", Op::tail);
  map_->set("add", Op::add);
  map_->set("sub", Op::sub); 
  map_->set("mul", Op::mul);
  map_->set("div", Op::div);
  map_->set("mod", Op::mod); 
  map_->set("def", Op::def); 
  map_->set("call", Op::call);
  map_->set("funcall", Op::funcall);
  map_->set("curry", Op::curry);
  map_->set("pipe", Op::pipe);
  map_->set("spawn", Op::spawn);
  map_->set("spin", Op::spin);
  map_->set("sleep", Op::sleep);
  map_->set("eval", Op::eval);
  map_->set("call_extern", Op::call_extern);
  map_->set("send", Op::send);
  map_->set("ret", Op::ret);
  map_->set("cond", Op::cond);
  map_->set("loop", Op::loop);
  map_->set("while", Op::while_);
  map_->set("return", Op::return_);
  map_->set("exit", Op::exit_);
  map_->set("continue", Op::continue_);
  map_->set("break", Op::break_);
  map_->set("repeat", Op::repeat);
  map_->set("for", Op::for_);
  map_->set("do", Op::do_);
  map_->set("faz", Op::faz);
  map_->set("print",Op::print);
  map_->set("printr",Op::printr);
  map_->set("module",Op::module_);
  map_->set("defun", Op::defun);
  map_->set("defmacro", Op::defmacro);
  map_->set("alias", Op::alias);
  map_->set("lambda", Op::lambda);
  map_->set("read", Op::read);
  map_->set("readline", Op::readline);
  map_->set("load", Op::load);
  map_->set("require", Op::require);
  map_->set("import", Op::import);
  map_->set("size", Op::size);
  map_->set("typeof", Op::typeof_);
  map_->set("is_atom", Op::is_atom);
  map_->set("is_integer", Op::is_integer);
  map_->set("is_float", Op::is_float);
  map_->set("is_string", Op::is_string);
  map_->set("is_list", Op::is_list);
  map_->set("is_cc_list", Op::is_cc_list);
  map_->set("is_deque", Op::is_deque);
  map_->set("is_vector", Op::is_vector);
  map_->set("is_hash", Op::is_hash);
  map_->set("is_ihash", Op::is_ihash);

  map_->set("+", Op::add);
  map_->set("-", Op::sub);
  map_->set("*", Op::mul);
  map_->set("/", Op::div);
  map_->set("%", Op::mod);

  map_->set("<", Op::lt);
  map_->set(">", Op::gt);
  map_->set("<=", Op::lteq);
  map_->set(">=", Op::gteq);
  map_->set("==", Op::eq);
  map_->set("!=", Op::neq);
  map_->set("=", Op::assign);
  map_->set("if", Op::if_);
  map_->set("iif", Op::iif);
  map_->set("case", Op::case_);
  map_->set("match", Op::match);
  map_->set("not", Op::not_);
  map_->set("and", Op::and_);
  map_->set("or", Op::or_);
  map_->set("||", Op::or_);
  map_->set("&&", Op::and_);

  m_lisp->add("Keywords", move(map_));
}

Lisp::Op Lisp::str_to_op(const string &input) {
  MYLOGGER(trace_function, "LispExpr::keyword_to_op()", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  auto map_ = get_branch(lisp_path_keyword);
  //auto &map_ = Lisp::map_;

  if(map_ == nullptr || map_->type_ != Node::Type::Map) {
    cout << "lisp keyworld map_ type != map\n";
    return Lisp::Op::error;
  }
  auto status = (*map_)[input];
  if(!status.first) {
    MYLOGGER_MSG(trace_function, "Lisp keyword: " + input + " not found , return as scalar", SLOG_FUNC_INFO+30);
    return Lisp::Op::scalar;
  }
  auto op = get<Lisp::Op>(status.second.value_);
  return op;
}

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