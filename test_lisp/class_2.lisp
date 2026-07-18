module Kernel 

  class Dict

    (var size (length 124) )

    def initialize(x)  
      (var (that 555))
      print "hello class constructor Dict.init()\n"
    end.def

    def area(a1 pi)  
      var name (value 555)
      assign name "area of planet earth"
      print "\nhello class Dict::area ()\n"
      print "area is: " a1 "\n"
      print "pi: " pi "\n"
      = b (+ 1 2 3)
      loop 
        print (eval (read)) "\n" 
      end.loop


    end.def

    def m1 ()
      print "method m1"
    end.def

  end.class

  def main (x y)

    (assign x1 999)
    assign m1 (new Dict "hello dictionary")
    (send m1 :area 999 3.14)
    print "x1: " x1 "\n"
    print "m1: " m1 "\n"

  end.def

  def f1 ()
    print "main f1\n"
  end.def

end.module
