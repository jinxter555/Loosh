(module Kernel 
  (def main (x y) "my func des" 
    (
      (var (x "xxx"))

      print 1 \
      2 \
      3 \
      4 \
      5

      (print "hello, world\n")
      (print "\n")
      (p55 (55 2))
      (print "\n\n")
      loop
        print (eval (read)) "\n"
      end.loop
    )
  )
  (def p55 (x y) "my func p55" 
    (
      (var (z "zzz"))
      (print "hello, p55, 55\n")
      (print "x: " x "\n")
      (print "(x): " (x) "\n")
      (print "(y): " (y) "\n")
      (print "\n")
      (print "-" x "-")
      (print "-" z "-")
      (print "\n")
    )
  )
  (def p56 (x y) "my func p56" 
    (
      (print "hello, p56, 56\n")
      (print (x))
      (print "\n")
      (print "-" x "-")
      (print "\n")
    )
  )

  defmacro mymac (mx my)
    assign y 1
    print "my mac1\n"
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

)
