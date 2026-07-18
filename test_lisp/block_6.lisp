module Kernel 
  def main (x y) 
      (print "hello, world\n\n")
      (p55 (55 2))
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
  end.def

end.module
