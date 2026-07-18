module Kernel 
  def main (x y) 
      (var a)
      print "Macros!\n"
      assert [1==1]
      loop
        print (eval (read)) "\n"
      end.loop
  end.def

  defmacro assert (assertion)
    quote
      if(not (unquote assertion) )
        print  (quote (unquote assertion))  "\n"
        print "assert failed!\n"
      end.if
    end.quote

  end.defmacro

end.module
