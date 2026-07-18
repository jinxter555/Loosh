module Kernel 
  (defun main (x y) "my func des" 
    (

      (var a)
      print "Macros!\n"
      mymac 2 2

      loop
        print (eval (read)) "\n"
      end.loop
    )
  )

  defmacro mymac (mx my)
    print "hello, world\n"
    assign v1 9999
    quote
      print "q 1: " (car (unquote mx))  " " (car (unquote my)) (unquote v1) "\n"
    end.quote
    quote
      print "q 2: " (car (unquote mx))  " " (car (unquote my))  "\n"
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
