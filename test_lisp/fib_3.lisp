module Kernel 
  def main (x y) 
    var forever (count 0)
    = t1  "t1 robot"
    = forever true

     print (fib 6)  "\n"

  end.def

  def fib(n) 
    print "n: " n "\n"
    if[n <= 1]
      return n
    :else
      # return (+  (fib[n-1]) (fib[n-2]))
      return [\(fib(- n 1)) + \(fib(- n 2))]
    end.if

  end.def

end.module
