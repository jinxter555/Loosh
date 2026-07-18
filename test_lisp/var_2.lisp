(module Kernel 
  (defun main (x y) my_func_des
    (
;    (print "hello, world1\n")    (print "hello, world2\n")
    (var v1 v_3 v.4  (v2 (vector 12345 3457)) (v3 3.14159) (s1 "hello") (s2 "world") )
    (assign v1 "what is up")
    (assign v5 "hello v5")
    (assign v_3 "hello v333")
    ;(assign v5 "hello v555")
    (assign v.4 "hello v.4444")
    (assign v6 :atomic_physics)
    (print v5 "\n")
    (print v2 "\n")
    (print v_3 "\n")
    (print v.4 "\n")
    (print v3 "\n")
    (print v6 "\n")
    (print "hello literal!! (v2 v3): " (literal v2 v3 (1 2 3))  "\n")
    ; (p55 (11111 22222))
    ;(assign v6 :atomic_physics2)
    (print v6 "\n")
    )
  )


  (defun p55 (x y) "my func p55" 
    (
      (print "hello, p55, 55\n")
      (print x; print out x 
             "\n" ; print new
             y "\n"; new line
            )
    )
  )

)
