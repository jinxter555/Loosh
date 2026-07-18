module Kernel 
  def main (x y) 

      print "Macros2!\n"

      = my 55555
      = t true

      unless ((== t false) (print "hello world1!\n"))
      unless false (print "hello world2!\n")

      loop
        print (eval (read)) "\n"
      end.loop

  end.def

  defmacro unless (cnd bloc)
    quote
      if (not (unquote cnd) )
        (unquote bloc)
      end.if
    end.quote


  end.defmacro

end.module


