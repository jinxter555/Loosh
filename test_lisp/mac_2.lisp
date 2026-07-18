module Kernel 
  (def main (x y) "my func des" 
    (

      (var a)
      print "Macros!\n"
      mymac 555 666

      loop
        print (eval (read)) "\n"
      end.loop
    )
  )

  defmacro mymac (mx my)
    print "hello, world\n"
    assign v1 9999
    quote
      (var temp~)
      print "q 1: " (unquote mx)  " " (unquote my) " " (unquote v1) "\n"
    end.quote
    quote
      print "q 2: " (unquote mx)  " " (unquote my) " " (unquote v1) "\n"
    end.quote

  end.defmacro

  def l1 ()
    5
    8
  end.def

  def l2 ()
    7 9
  end.def

  def l3 ()
    1 2 3
    4 5 6 7 
    8 9
  end.def

  def l4 ()
    print 
    print 
    print 
  end.def

end.module
