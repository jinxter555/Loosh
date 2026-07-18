module Kernel 

  def main (x y) 

    var x v

    [x = \(:ok 5 6 7 8)]

    print "x: " x "\n"

    match x
      (:ok 1) (print "1 hello\n")
      (:ok 3) (print "3 world\n")
      (:ok 6) (print "v: " v ", 5 match\n")
      (:error v) (print "v: " v ", 5 match\n")
      (:ok v v2*) (print "v: " v ", 5 match " v2 "\n")
      (_)  ((print "default: what is up\n") (print (+ 1 2 3) "\n" ))
    end.match

  end.def


end.module
