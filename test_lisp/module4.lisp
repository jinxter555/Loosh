module Kernel 
  var (gvalue 123)
  def main (x y) 
    
     use :global Kernel
  
     var (v1 "hola mundo") (v2 "halo welt")
     print "hello "
     print "world\n" 
     print v1 ", " v2 "\n"

      My.Mod1.p1()
      
     # p55 88888888
     loop
        print (eval (read)) "\n"
      end.loop
  end.def

  def p55(value)
    print "p55 hello\n" 
    print "value:" value "\n"
      loop
        print (eval (read)) "\n"
      end.loop
  end.def
end.module

module Another
  var (my_var1 "variable string") (my_int2 6) (my_map3 (1 2 3))
  def p1()
    print "Another p1()\n"
      loop
        print (eval (read)) "\n"
      end.loop
  end.def
end.module

module My.Mod1

  var data  (my_var1 "variable string--Mod.Mod1--") (my_int2 6) (my_map3 (1 2 3))

  class Dict
    (var size (length 123) w)

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



  def p1()
    use :global My.Mod1
    var (hello "world")
     # = $d (new Dict 1 2 3)

    print "Another p1() with class Dict() \n"
    print  hello "\n"
      loop
        print (eval (read)) "\n"
      end.loop
  end.def





end.module
