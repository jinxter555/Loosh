module Kernel 
  def main (x y)
    #load "fib_5.lisp"
    #load "use_build_1.lisp"

    var v a list1
    = list1 ( 11 22 33 44 55)
      loop
        print (eval (read)) "\n"
      end.loop
  end.def

  def p1(myl *myl2)
    print "p1(myl) " myl "\n"
    loop
      print (eval (read)) "\n"
    end.loop

  end.def

end.module
