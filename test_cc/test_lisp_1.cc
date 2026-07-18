#include "../node.hh"
#include "../lisp_expr.hh"
#include <iostream>

using namespace  std;
  

int main() {
  Node::List nl1;
  //vector<Node::Value> vnv1 = {1,2,3};
  //nl1.push_back(Node::create(1));
  //nl1.push_back(Node::create(2));
  //nl1.push_back(Node::create(Lisp::Op::add));
  nl1.push_back(Node::create(1));
  nl1.push_back(Node::create(2));
  nl1.push_back(Node::create(5));

  Node l1(move(nl1));
  auto result1 =  l1.list_add();
  cout << "l1: " << l1 << "\n";
  cout << "l1.add(): " <<  *result1.second << "\n";
  auto result_status1b = l1.pop_back();
  auto result1b =  l1.list_add();
  cout << "l1: " << l1 << "\n";
  cout << "result_status1a: " <<  *result_status1b.second << "\n";
  cout << "l1.add(): " <<  *result1b.second << "\n";
  cout << "\n\n";

  Node::Vector nl2, vl2;

  nl2.push_back(Node::create(3));
  nl2.push_back(Node::create(5));
  nl2.push_back(Node::create(7));
  vl2.push_back(Node::clone(nl2));



  Node l2(move(nl2));
  cout << "l2: " << l2 << "\n";
  auto result2 =  l2.list_add();
  cout << "l2.add(): " <<  *result2.second << "\n";

  auto result_status2b = l2.pop_front();
  auto result2b =  l2.list_add();
  cout << "l2: " << l2 << "\n";
  cout << "result_status2a: " <<  *result_status2b.second << "\n";
  cout << "l2.add(): " <<  *result2b.second << "\n";
  cout << "\n\n";



  vl2.push_back(Node::create(6));
  vl2.push_back(Node::create(7));
  vl2.push_back(Node::create(8));
  Node v2(move(vl2));

  v2.print();
  cout << "v2: " << v2._to_str() << "\n";



/*
  //Node s1("what is up");
  //v1.push_back(Node::create(1));
  //v1.add("hello2");
  //v1.push_back(2233);
  //Node l2({1, 2});
  Node::Value nv1=123;
  Node ml(move(nv1));
  Node l1(move(nl1));

  //Node::print_value_recursive(v1, 0);
  Node::print_value_recursive(ml, 0);
  Node::print_value_recursive(l1, 0);

  vector<Node::Value> vnv1;
  vector<Node::ValueSimple> vnv2={11,22,33};
  vnv1.push_back(1);
  vnv1.push_back(2.3);
  //Node l2(move(vnv1));
  //Node::print_value_recursive(l2, 0);
  Node l3(vnv2);
  Node l4(vector<Node::ValueSimple>{44,55,66});
  Node::print_value_recursive(l3, 0);
  Node::print_value_recursive(l4, 0);

  LispExpr sp1(vector<Node::ValueSimple>{Node::LispOp::add, 44,55,66});
    cout << "\nsp1\n";
  //Node::print_value_recursive(sp1, 0);
  Node env;
  //auto result = sp1.builtin_add(env, 1);
  if(result.first){
    cout << "result of sp1\n";
    Node::print_value_recursive(*result.second, 0);
  }
  //Node::print_value_recursive(*result.second, 0);
*/
}