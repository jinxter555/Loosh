module Kernel 
  def main (x y) 
    var forever (t true)
    assign t1  "t1 robot"
    assign forever false

    iif(t) 
      (print "forever: " forever "\n" )
      (print "sometimes, forever " forever "\n" )
    end.iif

    myif()

    print "myif "   "\n"

    My.Mod1.p1()
    System.Io.File.open()
    

  end.def

  def myif() 

    if [ true == false ]
      print (+ 1 2 3) "\n"
      print "hello\n"
      print "hola\n"
      return :ok
    :else
      print "world\n"
      print "mundo\n"
      return :error
    end.if

  end.def


end.module

module My.Mod1
  def p1 ()
      print "p1\n"
  end.def
end.module

module System.Io.File
  def open()
    print "opening a file!\n"
  end.def
end.module
