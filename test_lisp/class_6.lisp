module Kernel 
  defmacro clone(x)
    quote
      eval (unquote x) 
    end.quote
  
  end.defmacro


  class Dict
    (var size (length 123) w )

    def initialize(w1)  
      print "Dict::init() w1: " w1 "\n"
      = @w w1

    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def

    def per()
      print "Dict::per()"   "\n"
      loop
        print ( eval (read)) "\n"
      end.loop
    end.def

    def finalize()
      print @w " Dict::finalize() destructor!\n\n"
    end.def

  end.class


  def main (x y)

    var v m1



    = m1 (new Dict "ship building" )
    = r1 (root)

    print "m1: " m1 "\n"

    loop
       print ( eval (read)) "\n"
    end.loop

  end.def

  def p1(m)
    print "p1(m): m " m "\n"
    loop
       print ( eval (read)) "\n"
    end.loop
    
  end.def
  


end.module
