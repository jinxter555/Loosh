module Kernel 

  defmacro clone(x y) 
    quote
      = (unquote y) (eval (unquote x) )
    end.quote
  end.defmacro

  class Car
    var type
    def initialize()
      = @type  123

      # print  "car init\n"
    end.def

    def finalize()
      #print  "car fin\n"
    end.def

  end.class

  class Dict
    (var size (length 123) w c1)

    def initialize(w1 w2 w3)  
      # print "Dict init:  " w1 "\n"
      = @w w1
      = @c1 (new Car  )

    end.def

    def area(a pi)  
      print "\nhello class Dict::area ()\n"
      print "area is: " a "\n"
      print "pi: " pi "\n"
    end.def

    def finalize()
      #print @w " Dict finalize destructor!\n\n"
    end.def

  end.class


  def main (x y)

    var v1 v3

    f1()
    = v1 (new Dict "main-webster11  " "global" "affairs")
    = v2 v1

    # print "v2 " v2 "\n"

#    delete v1
#    print "v2 " v2
#    delete v2

    loop
       print ( eval (read)) "\n"
    end.loop

  end.def

  def f1 ()
    var m1 
    print "in f1\n"
    = m1 (new Dict "f1-webster11  " "global" "affairs")
    # print :gc

    #loop
    #   print ( eval (read)) "\n"
    #end.loop

    print "\n"
  end.def


  def fib(n) 

    print "fib(n) is " n "\n"

    return n
  
  end.def


end.module

