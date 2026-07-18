(module Kernel 
  (defun main (x y) my_func_des
    (
    ;(assign v (5 6 7))
    (assign v 123)
    (assign v2 (1 2 3))

    (print v2 " v2=(1 2 3) "  (car v2) "\n")
    (print " car cdr 4: "  (car (cdr (3 4 5))) "\n")
    (print " car cdr v2 "  (car (cdr v2 )) "\n")
    ;(print (car (car (6 7 9))) "\n")
    (print v " car " (car v))
    (print "\n")
    (print " car() " (car()))
    ;(print (car 333))
    (print "\n")
    )
  )
)
