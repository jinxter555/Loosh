module Kernel 
  def main (x y)

     ((lambda  (x y)
          (print "hello lambda \n")
          print "args: x: " x ", y: " y "\n\n"
          return  x
        ) 55555 666)

     ((lambda  (x)
          (print "hello lambda \n")
          print "arg: x: " x "\n"
          return  x
        ) 55555)

     ((lambda  ()
          (print "no arg. hello lambda \n")
        ))



     # print "v1: " v1 "\n"
      print "\n"

  end.def 
end.module
