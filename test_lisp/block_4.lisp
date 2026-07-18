module Kernel 
  ;(var v1 (v2 123))
  ;

  defun main (x y) "my func des" 
    (
      (var m1)

      (assign m1 
      (map 
        (k1 "hello, ")
        (k2 "world")
      ))

      (assign m2 
      (map 
        (k1 "hello, ")
        (k2 "world")
      ))


      (print "m1a:" m1 "\n\n")
      (print "m1.k1: " m1.k1 "\n\n")
      (print "m1.k2: " m1.k2 "\n\n")

      (assign m1.k1 "what is up ")

;      (assign m3.k1 "hola")
      ; (assign m2 "hola")

      (print "m1b:" m1 "\n\n")
      (print "m1.k1: " m1.k1 "\n\n")
      (print "m1.k2: " m1.k2 "\n\n")

      (print "hello, world\n\n")
     ; (p55 (55 2))
     ; (p55 (55 2))
      (p57 (57 7))
    )
  end.defun 

  defun p55 (x y) "my func p55" 
    (
      (print "hello, p55, 55\n")
      (print "(x): " (x) "\n")
      (print "\n")
      (assign t1  "t1 robot")
      (p56 (56 6))
    )
  end.defun

  defun p56 (x y) "my func p56" 
    (
      (print "hello, p56, 56\n")
      (print (x))
      (print "\n")
    )
  end.defun

  def p57 (x y) 
    (print "hello, p56, 56\n")
    (print (x))
    (print "\n")
    (print (y))
    (print "\n")
  end.def

end.module
