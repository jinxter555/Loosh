module Kernel 
  def main (x y) 
    var forever (count 0)
    = t1  "t1 robot"
    = forever true

     print( fib 2)

  end.def

  def fib(n) 
    if[n == 0]
      print "n == 0\n"
      return 0
    end.if

    if[n == 1 || n==2 ]
      return 1
    end.if

    = a (fib[n - 1])
    = b (fib[n - 2])


    return a + b
  end.def

end.module
