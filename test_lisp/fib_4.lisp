module Kernel 
  def main (x y) 
    print "Fib!\n"
     print (fib 6)  "\n"
  end.def

  def fib(n) 
    print "n: " n "\n"
    print "hello"
    if[n <= 1]
      print "n less than zero"
      return n
    :else
      return(+
        (fib[n-1])
        (fib[n-2])
      )
    end.if


  end.def

end.module
