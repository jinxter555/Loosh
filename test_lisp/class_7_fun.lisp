module Kernel 

  class Dict
    (var size (length 123) w )

    def initialize(w1 w2 w3)  
      print "Dict init:  " w1 "\n"
      = @w w1

    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def

    def finalize()
      print @w " Dict finalize destructor!\n\n"
    end.def

  end.class


  def main (x y)

    var v1 v3

    = v1 (new Dict "main-webster11  " "global" "affairs")

    #print "v2 " v2 "\n"
    print "v1 " v1 "\n"
    print "f1(v1) \n"
#    f1(v1)
  

    loop
       print "main loop: "
       print ( eval (read)) "\n"
    end.loop

  end.def

  def f1 (x)
    print "x " x "\n"

    loop
       print "f1 loop: "
       print ( eval (read)) "\n"
    end.loop

    print "\n"
  end.def

end.module
