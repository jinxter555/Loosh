module Kernel 
  def main (x y) 

    cond
      (false) (print "false!\n")
      (true) (print "true\n")
      [1==1] (print "hello\n")
      [2==1] (print "world\n")
      [true==true]  (print "what is up\n")
    end.cond

  end.def


end.module
