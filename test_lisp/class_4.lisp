module Kernel 

  defmacro clone(x y) 
    quote
      = (unquote y) (eval (unquote x) )
    end.quote
  end.defmacro

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

    # f1()
    = v1 (new Dict "webster11  " "global" "affairs")
    = v2 v1

    print "v2 " v2 "\n"

#    delete v1
#    print "v2 " v2
#    delete v2

    loop
       print ( eval (read)) "\n"
    end.loop

  end.def

  def f1 ()
    var m1 
    print "f1\n"
    = m1 (new Dict "webster11  " "global" "affairs")
  end.def

end.module
