

//-------------------------------- parse def 
// (def name (param_list) (code list))
// def fun (x,y) ... end.def
// return map as function
// return -> fun_name -> {code,params,object_info}
Node::OpStatus Lisp::build_parsed_def(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_def(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  string name;
  Node::Map fun={}; 
  if(list.empty()) return {false, Node::create_error(Node::Error::Type::Parse, "def empty list to get fun name.")};

  name = list.front()->_to_str();
  
  list.pop_front(); // function name

  // set func
  {// turn params List to params Vector for speed performance
  auto status =  build_parsed_vector(*list.front()); 
  if(!status.first) return status;
  fun[LOOSH_PARAMS] = move(status.second); list.pop_front();
  }


  /*
  for(auto &ele : list) {// find alias
    auto &inner_line = ele->_get_list_ref();
    auto &inner_ele = inner_line.front();
    if(inner_ele->_to_str() == ALIAS)  {
      inner_line.pop_front();
      auto alias_status = build_parsed_alias(inner_line);
      if(!alias_status.first) {
        return alias_status;
      }
    //  fun[ALIAS] = move(alias_status.second);
      cout << "alias ele " <<  *ele << "\n";
      list.push_front(Node::create(Lisp::Op::noop));
    }
  }*/
  

  {// turn code List to code Vector for speed performance
  //auto status=  build_parsed_vector(*list.front()); 
  auto status=  build_parsed_vector(list); 
  if(!status.first) return status;
  fun[LOOSH_CODE] = move(status.second); 
  if(!list.empty()) list.pop_front();
  //cout << "code: list after pop!" << Node::_to_str(list) << "\n";
  }

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(LOOSH_TYPE,  Node::create(Lisp::Type::def));

  fun[LOOSH_D_OBJ_INFO] = move(obj_info);
  fun[LOOSH_NAME] = Node::create(name);
  fun[LOOSH_NAMESPACE] = Node::create(build_namespace.back());

  return {true, Node::create(move(fun))};
}

//-------------------------------- parse macro
// (defmacro (param_list) (code list))
// def fun (x,y) ... end.def
// return map as function
// return -> fun_name -> {code,params,object_info}

Node::OpStatus Lisp::build_parsed_macro(Node::List& cclist) {
  MYLOGGER(trace_function, "Lisp::build_parsed_macro(Node::List& cclist)", __func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, "list: " + Node::_to_str(cclist), SLOG_FUNC_INFO+30)

  string name;

  Node::Map macro={}; 
  if(cclist.empty()) return {false, Node::create_error(Node::Error::Type::Parse, "defmacro empty cclist to get macro name.")};
  name = cclist.front()->_to_str();

  cclist.pop_front(); // function name

  {// Parameter block
  auto status =  build_parsed_vector(*cclist.front()); 
  if(!status.first) return status;
  macro[LOOSH_PARAMS] = move(status.second); cclist.pop_front();
  }

  {
  auto status=  build_parsed_vector(cclist); 
  if(!status.first) return status;
  macro[LOOSH_CODE] = move(status.second); 
  if(!cclist.empty()) cclist.pop_front();
  }

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(LOOSH_TYPE,  Node::create(Lisp::Type::defmacro));
  macro[LOOSH_D_OBJ_INFO] = move(obj_info);
  macro[LOOSH_NAME] = Node::create(name);
  macro[LOOSH_NAMESPACE] = Node::create(build_namespace.back());
  return {true, Node::create(move(macro))};
}




//-------------------------------- parse module
// (module Main (defun main ) (defun f1 ) (defun f2) (class end.class)) 
Node::OpStatus Lisp::build_parsed_module(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_module(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto module_functions=make_unique<Node>(Node::Type::Map);
  auto module_aliases=make_unique<Node>(Node::Type::Map);
  auto module_classes=make_unique<Node>(Node::Type::Map);
  auto module_macros=make_unique<Node>(Node::Type::Map);
  auto module_node=make_unique<Node>(Node::Type::Map);

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(LOOSH_TYPE,  Node::create(Lisp::Type::module_));

  string module_name = get<string>(list.front()->m_value); list.pop_front(); // module name

  for(auto& ele: list) {  
    auto status = parse_build(*ele); // parse (defun ...) (class ...)
    if(!status.first) return status;
    status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 

    switch(Lisp::type(*status.second)){
    case Lisp::Type::def: {
      auto fun_name = (*status.second)["name"].second._to_str();
      //status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 
      module_functions->set(fun_name, move(status.second));
      continue;
    }


    case Lisp::Type::defmacro: {
      auto mac_name = (*status.second)["name"].second._to_str();
      //status.second->set(MODULE_PTR, module_node.get()); // causes recursive segault when print recursive// get raw pointer from 
      module_macros->set(mac_name, move(status.second));
      continue;
    }

    case Lisp::Type::class_: {
      auto class_name = (*status.second)["name"].second._to_str();
      //cout << "class name: " << class_name << "\n";
      module_classes->set(class_name, move(status.second));
      break;
    }

    case Lisp::Type::alias: {
      auto alias_name = (*status.second)["name"].second._to_str();
      module_aliases->set(alias_name, move(status.second));
      break;
    }


    default: { // assign module attributes here like  (var )
      if(status.second->m_type==Node::Type::Vector) {
        auto head = status.second->front().second._to_str();
        auto v2o_status = vector_to_object(status.second->_get_vector_ref()); // vector 2 object
        v2o_status.second->pop_front();
        module_node->set(head,  move(v2o_status.second) );

      } else {
        cerr << "unknown module attribute not vector!\n";
        return {false, Node::create_error(Node::Error::Type::Parse, "unknown class attribute:" )};
      }
    }}
  }
  module_node->set(FUNCTION, move(module_functions));
  module_node->set(MACRO, move(module_macros));
  module_node->set(_CLASS, move(module_classes));
  module_node->set(ALIAS, move(module_aliases));
  module_node->set(OBJ_INFO, move(obj_info));
  module_node->set(_NAME, module_name);
  module_node->set(NAMESPACE,  Node::create(build_namespace.back()));

  return {true, move(module_node)};
}

//-------------------------------- attach 'this'  var to class method
Node::OpStatus Lisp::attach_this_to_arguments(Node::Vector& list){
  list.insert(list.begin(), Node::create("this", Node::Type::Identifier)); 
  return {true, Node::create()};
}

//-------------------------------- parse class
// (class Car (defun start) (defun drive) (defun f2) ) 
Node::OpStatus Lisp::build_parsed_class(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_class(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  vector<string> keys={};

  auto class_functions=make_unique<Node>(Node::Type::Map);
  auto class_aliases=make_unique<Node>(Node::Type::Map);
  auto class_node=make_unique<Node>(Node::Type::Map);

  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(LOOSH_TYPE,  Node::create(Lisp::Type::class_));

  string class_name = get<string>(list.front()->m_value); list.pop_front(); // class name

  for(auto& ele: list) {  
    auto status = parse_build(*ele); // parse (defun ...) (class ...)

    if(!status.first) return status;
    status.second->set(CLASS_PTR, class_node.get()); // recursive will segfault, check to_str and print recursive

    switch(Lisp::type(*status.second)){
    case Lisp::Type::def: {
      auto fun_name = (*status.second)[LOOSH__NAME].second._to_str();
    //  auto &code_list = (*status.second)[CODE].second._get_vector_ref();
      //cout << "defun code list:" << code_list << "\n";
      attach_this_to_arguments((*status.second)[LOOSH__PARAMS].second._get_vector_ref());
   //   attach_this_to_var(code_list); // pre-prend (var this) to a class method, hopeflly only private in future
      class_functions->set(fun_name, move(status.second));
      continue;
    }

    case Lisp::Type::alias: {
      auto alias_name = (*status.second)["name"].second._to_str();
      class_aliases->set(alias_name, move(status.second));
      break;
    }

    case Lisp::Type::class_: {
    }
    default: { // assign class attributes here like  (var )
      if(status.second->m_type==Node::Type::Vector) {
        auto head = status.second->front().second._to_str();
        auto v2o_status = vector_to_object(status.second->_get_vector_ref()); // vector 2 object
        class_node->set(head,  move(v2o_status.second) );

      } else {
        cerr << "unknown class attribute not vector!\n";
        return {false, Node::create_error(Node::Error::Type::Parse, "unknown class attribute:" )};
      }
    }}
  }
  class_node->set(FUNCTION, move(class_functions));
  class_node->set(ALIAS, move(class_aliases));
  class_node->set(OBJ_INFO, move(obj_info));
  class_node->set(_NAME, class_name);
  class_node->set(NAMESPACE,  Node::create(build_namespace.back()));

  //cout << "module_node:" << *module_node << "\n";
  return {true, move(class_node)};
}



//-------------------------------- parse root
// (root :set (path,..) value )
// (root :get () )
Node::OpStatus Lisp::build_parsed_root(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_root(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  try {
    auto root_sym_op = get<Node::Integer>(list.front()->m_value); list.pop_front(); // root op symbol 
    if(root_sym_op == atom_set) {
      auto path_list = move(get<Node::List>(list.front()->m_value));  list.pop_front();
      auto value = move(list.front());  list.pop_front();

      auto path_vec_str = Node::list_to_vector_string(path_list);
      return set(path_vec_str, move(value), true);
      //return {true, Node::create(true)};

    } else if(root_sym_op== atom_get){
      auto path_list = move(get<Node::List>(list.front()->m_value));  list.pop_front();
      auto path_vec_str = Node::list_to_vector_string(path_list);
      auto node_ref = get_node(path_vec_str);
      if(node_ref.first) return {true, node_ref.second.clone()};
    }
  } catch(...) { 
    return {false, Node::create_error(Node::Error::Type::InvalidOperation, 
        "error: parsed root get symbol") };
  }
  return {true, Node::create()};

}
//------------------------------------------------------------------------
// attach module to 'Lisp' Language tree
//
Node::OpStatus Lisp::attach_module(unique_ptr<Node> mod_ptr) {
  MYLOGGER(trace_function, "Lisp::attach_module(unique_ptr<Node>module)", __func__, SLOG_FUNC_INFO);
  //auto mod_loc = get_branch(lisp_path_module);
  auto mod_loc = get_branch(namespace_module_path());


  auto name_ref_status  = mod_ptr->get_node(_NAME);

  if(!name_ref_status.first) {
    cerr << "error getting module name!\n";
    return {false, name_ref_status.second.clone()};
  }
  auto module_name = name_ref_status.second._to_str();
  //cout << "module name: " << module_name << "\n";


  // merging other file modules
  if(mod_loc->m_has_key(module_name)) {
    cout << "module name " << module_name << " already exist!\n";
    //cout << "mod_ptr is : " << mod_ptr->_to_str() << "\n\n";
    auto m1_status = mod_loc->get_node(module_name);
   // cout << "mod_loc address: " << &m1_status.second<< "\n";

    // overwrite the mod_ptr to the m1 mod_ptr
    //mod_ptr->replace_nested(MODULE_PTR, &m1_status.second); 
    //cout << "\n replaced, *mod_ptr: " << *mod_ptr << "\n\n";

    //return m1_status.second.merge_nested(move(mod_ptr));
    m1_status.second.merge_nested(move(mod_ptr));
    m1_status.second.replace_nested(LOOSH_MODULE_PTR, &m1_status.second);

    //cout << "\nmerged, m1_status : " << m1_status << "\n\n";
    //cout << "\nmerged, mod_loc: " << *mod_loc << "\n\n";
    return {true, Node::create(true)};
  }

  //return mod_loc->set(module_name, move(mod_ptr));


  mod_loc->set(module_name, move(mod_ptr));
  //cout << "\nnon merge, mod_loc: " << *mod_loc << "\n\n";
  //cout << "mod_loc: " << *mod_loc << "\n\n";
  //return {false, Node::create(true)};
  return {true, Node::create(true)};
}
//--------------------------------  attach c++ static function
Node::OpStatus Lisp::attach_cc_fun(const string&name, const Node::Fun& f) {
  MYLOGGER(trace_function, "Lisp::attach_cc_fun(const string&name, const Node::Fun&f)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("name: ") + name, SLOG_FUNC_INFO+30);

  auto mod_loc = get_branch(cc_path_module);
  if(mod_loc==nullptr) {
    cerr << "attach_cc_fun(): mod_loc is nullptr!\n";
    return {false, Node::create_error(Node::Error::Type::Unknown, "attach_cc_fun(): mod loc is nullptr!")};
  }

  Node::Map nm = {};
  nm[name] = Node::clone(f);
  return mod_loc->merge(Node::create(move(nm)));
}
Node::OpStatus Lisp::attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun& f) {
  MYLOGGER(trace_function, "Lisp::attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun&f)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "name_mod: " + name_mod + ", name_fun: " + name_fun, SLOG_FUNC_INFO+30);
  auto location  = cc_path_module;
  location.push_back(name_mod);
  auto mod_loc_ref = get_node(location );
  if(!mod_loc_ref.first) { // module location does not exist
    //cerr << "CC_path_module returned false! !" << mod_loc_ref.second._to_str() << ", create new module\n";
    //return {false, mod_loc_ref.second.clone()};
    set_branch(location , Node::create(Node::Type::Map));
  }
  location.push_back(FUNCTION); // add 'function' sub branch as well
  auto modfun_loc = get_branch(location );

  if(modfun_loc==nullptr) 
    set_branch(location , Node::create(Node::Type::Map));

  modfun_loc = get_branch(location );
  Node::Map nm = {};
  nm[name_fun] = Node::clone(f);
  return modfun_loc->merge(Node::create(move(nm)));


}


//------------------------------------------------------------------------ build parse
// assumes Node.m_value contains a Node::List of nodes

//-------------------------------- vector

Node::OpStatus Lisp::build_parsed_vector(Node& node) {
  MYLOGGER(trace_function, "Lisp::build_parsed_vector(Node&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);

  if(node.m_type != Node::Type::List) {
    cerr << "build_parsed_vector() error with '"<<  node << "',type: " << Node::_to_str(node.m_type) << "\n";
    return {false, Node::create_error(Node::Error::Type::Parse, "build_parsed_vector()! not vector type:Can't build vector!")};
  }

  try {
  auto &list = get<Node::List>(node.m_value);
  return build_parsed_vector(list);
  } catch(...) { 
    cerr << "build_parsed_vector() error with list '" <<  node << "'\n";
  }
  return {false, Node::create_error(Node::Error::Type::Parse, "build_parsed_vector()! not vector type:Can't build vector!")};

}




Node::OpStatus Lisp::build_parsed_vector(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_vector(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);

  Node::Vector vl;
  vl.reserve(list.size());
  for(auto& ele: list) {
    if(ele->m_type == Node::Type::List) { // nested parsing
      MYLOGGER_MSG(trace_function, string("build nested list: ") + ele->_to_str(), SLOG_FUNC_INFO+30);
      auto status_parsed = parse_build(*ele);
      if(!status_parsed.first) return status_parsed;
      MYLOGGER_MSG(trace_function, string("returned list type: ") + Node::_to_str(status_parsed.second->m_type), SLOG_FUNC_INFO+30);
      vl.push_back(move(status_parsed.second));
    } else 
    //vl.push_back(move(ele->clone()));
    vl.push_back(move(ele));
  }
  return {true, Node::create(move(vl))};
}

//-------------------------------- pipe
Node::OpStatus Lisp::build_parsed_pipe(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_list(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  Node::List result_list ={};

  if(list.empty()) return {true, Node::create(move(result_list))};

  auto ele= move(list.front());
  list.pop_front();
  result_list.push_back(move(ele));
  

  //cout << "1 result: " << Node::_to_str(result_list) << "\n";
  
  for(auto& ele_line: list) {
    if(ele_line->m_type == Node::Type::List) { // nested parsing

      auto &ele_list = get<Node::List>(ele_line->m_value);
      auto ele_list_front = move(ele_list.front());

      ele_list.pop_front();

      //ele_list.push_front(Node::create(move(result_list)));
      ele_list.splice(ele_list.begin(), result_list, result_list.begin(), result_list.end());

      //cout << "ele_list : " << Node::_to_str(ele_list) << "\n";
      ele_list.push_front(Node::create(move(ele_list_front)));
      
      

      result_list.push_back(Node::create(move(ele_list)));

     // cout << "1m result: " << Node::_to_str(result_list) << "\n";

    } else {
      auto msg = "in Pipe(), each statement line needs to be a list";
      cerr << msg << "\n";
      return {false, Node::create_error(Node::Error::Type::Parse, msg)};
    }
  }
  //cout << "2 result: " << Node::_to_str(result_list) << "\n";
  result_list.push_front(Node::create(Lisp::Op::eval));
  return  build_parsed_vector( result_list);
  //return {true, Node::create(move(result_list))};

}


//-------------------------------- list
Node::OpStatus Lisp::build_parsed_list(Node& node) {
  MYLOGGER(trace_function, "Lisp::build_parsed_list(Node& node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  auto &list = get<Node::List>(node.m_value);
  return build_parsed_list(list);
}

Node::OpStatus Lisp::build_parsed_list(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_list(Node::List&list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("list: ") + Node::_to_str(list), SLOG_FUNC_INFO+30);
  Node::List dl;
  for(auto& ele: list) {
    if(ele->m_type == Node::Type::List) { // nested parsing
      MYLOGGER_MSG(trace_function, string("build nested list: ") + ele->_to_str(), SLOG_FUNC_INFO+30);
      auto status_parsed = parse_build(*ele);
      if(!status_parsed.first) return status_parsed;
      MYLOGGER_MSG(trace_function, string("returned list type: ") + Node::_to_str(status_parsed.second->m_type), SLOG_FUNC_INFO+30);
      dl.push_back(move(status_parsed.second));
    } else {
      //dl.push_back(move(ele->clone()));
      dl.push_back(move(ele));
    }
  }
  return {true, Node::create(move(dl))};

}

//-------------------------------- deque

Node::OpStatus Lisp::build_parsed_deque(Node::List& list) {
  Node::DeQue dl;
  for(auto& e : list) dl.push_back(e->clone());
  return {true, Node::create(move(dl))};
}

Node::OpStatus Lisp::build_parsed_deque(Node& node) {
  MYLOGGER(trace_function, "Lisp::build_parsed_deque(Node& node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("node: ") + node._to_str(), SLOG_FUNC_INFO+30);
  auto &list = get<Node::List>(node.m_value);
  return build_parsed_deque(list);
  //return {true, Node::clone(node)};
}

//-------------------------------- map
Node::OpStatus Lisp::build_parsed_map(Node::List& list) {
  Node::Map map;
  //for(auto& e : list) { }
  return {true, Node::create(move(map))};
}
//Node::OpStatus Lisp::build_parsed_map(Node& node) { }

Node::OpStatus Lisp::vector_to_object(const Node::Vector&list) {
  MYLOGGER(trace_function, "Lisp::vector_to_object(const Node::Vector& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: " + Node::_to_str( list), SLOG_FUNC_INFO+30);

  auto object = make_unique<Node>(Node::Type::Map);
  auto object_info = make_unique<Node>(Node::Type::Map);

  auto& head = list[0];
  try {
    auto lisp_type = get<Lisp::Type>(head->m_value);
    if(lisp_type==Lisp::Type::var) {
      //cout << "need to assign vars differently because  in a class init object value (var (length 3.14159))!\n";
      //object->set(OBJ_INFO, move(object_info));
      //object->set(VECTOR, Node::clone(list));
      return {true, Node::clone(list)};

    }
    object_info->set(LOOSH_TYPE, lisp_type);
  } catch (...) {
    object_info->set(LOOSH_TYPE, Lisp::Type::nil);
  }
/*
  size_t s = list.size();
  for(size_t i=1;  i <s; i++  ) {
    object->set(list[i]->_to_str(), Node::create());
  }
*/
  object->set(OBJ_INFO, move(object_info));
  object->set(VECTOR, Node::clone(list));
  return {true, move(object)};
}


//-------------------------------- iif
Node::OpStatus Lisp::build_parsed_if(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_iif(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "Node::List& list : " + Node::_to_str(list), SLOG_FUNC_INFO+30);
  Node::Vector if_vl, block_vl;

  if_vl.reserve(list.size());
  block_vl.reserve(list.size());

  // first block
  if(list.empty()) {
    return {false, Node::create_error(Node::Error::Type::Parse, "parse: if error!")};
  }

  { // condition block
    auto status_parsed = parse_build(*list.front());
    if(!status_parsed.first) return status_parsed;
    if_vl.push_back(Node::create(Lisp::Op::if_));
//    cout << "condition: status_parsed" << status_parsed << "\n";
    if_vl.push_back(move(status_parsed.second));
    list.pop_front();
  }


  for(auto& ele: list) {
    auto status_parsed = parse_build(*ele);
    if(!status_parsed.first) return status_parsed;

    auto back_status_ref = status_parsed.second->back();
    if(back_status_ref.second.m_type == Node::Type::Atom &&
       back_status_ref.second._get_integer() == atom_else) {

      //cout << "build iif, block:  " << Node::_to_str(block_vl) << "\n";
      if_vl.push_back(Node::create(move(block_vl))); // push the first block
      block_vl.clear();
      continue;
    }
    block_vl.push_back(move(status_parsed.second));
  }
  if_vl.push_back(Node::create(move(block_vl)));

  //cout << "if_vl:  " << Node::_to_str(if_vl) << "\n\n";



  return {true, Node::create(move(if_vl))};
}

//-------------------------------- use
Node::OpStatus Lisp::use_at_parse_build(Node::List& cc_list) {
  MYLOGGER(trace_function, "Lisp::use_at_parse_build(Node::List& list)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "Node::List& list : " + Node::_to_str(cc_list), SLOG_FUNC_INFO+30);

  //cout << "namespace: " << Node::_to_str( cc_list) << "\n";
  auto cmd_option = move(cc_list.front()); cc_list.pop_front();

  //return {true, Node::create()};
  if(cmd_option->_get_integer() == atom_namespace) {
    auto ns = move(cc_list.front()); 
    build_namespace.push_back(  ns->_to_str());
    set_branch(namespace_module_path(), Node::create(Node::Type::Map));
    //cout << "namespace: " << build_namespace << "\n";
    return {true, Node::create(true)};

  } else {
    // put everything back
    cc_list.push_front(move(cmd_option));
    cc_list.push_front(Node::create(Lisp::Op::use));
   
    return build_parsed_vector(cc_list);
  }

}
//-------------------------------- 


// alias Mod.Part1.Part2.fun
// alias Mod.Part1.Part2.fun :as newfun
// alias NameSpace.Part1.Part2::Mod.Part1.Part2.fun
// alias NameSpace.Part1.Part2::Mod.Part1.Part2.fun :as newfun
//
Node::OpStatus Lisp::build_parsed_alias(Node::List& list) {
  MYLOGGER(trace_function, "Lisp::build_parsed_deque(Node& node)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "list: " + Node::_to_str(list), SLOG_FUNC_INFO+30);
  auto alias_map = make_unique<Node>(Node::Type::Map);
  auto obj_info = make_unique<Node>(Node::Type::Map);
  obj_info->set(LOOSH_TYPE,  Node::create(Lisp::Type::alias));

  auto s =  list.size();
  if(!s) return {false, Node::create()};
  
  auto alias_fullname =  list.front()->_to_str();
  list.pop_front();
  switch(s) {
  case 1: {
    auto vec_str  = split_string(alias_fullname, ".");
    auto alias_name  = vec_str.back();  // vec_str.pop_back();  
    if(vec_str.size() == 0) {
      auto msg = "alias error: requires Mod.Fun format!";
      cerr << msg << "\n";
      return {false, Node::create_error(Node::Error::Type::Parse, msg)};
    }
    alias_map->set(alias_name, move(alias_fullname));
    alias_map->set(_NAME, alias_name);
    break;
  }
  case 2: {
    auto alias_name = list.front()->_to_str();
    alias_map->set(alias_name, move(alias_fullname));
    alias_map->set(_NAME, alias_name);
    break;
  }
  default: {
    auto msg = "unknow alias option errors";
    cerr << msg << "\n";
    return {false, Node::create_error(Node::Error::Type::Parse, msg)};
  }}

  alias_map->set(OBJ_INFO,  move(obj_info));
  //cout << "alias map: " << alias_map->_to_str() << "\n";
  return {true, move(alias_map)};
}

}