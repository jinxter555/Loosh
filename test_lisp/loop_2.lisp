module Kernel 
  def main (x y) 
    (var input)
    (assign t1  "t1 robot")
    (assign x  5555)

    print "hello, world from main()\n\n"
    loop 
      (assign input (read))
       print input
      print (eval (read)) "\n"
    end.loop
  end.def
end.module
