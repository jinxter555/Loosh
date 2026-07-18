(module Kernel 
  (defun main (x y) my_func_des
    (
     (var m1)
      (assign m1 
      (hash  \
            (k1 123) \
            (k2 456) \
            (k3 456) \
            (k4 (hash (l1 456))) \
      ))

      loop
        print "Map:m1 "  m1 "\n\n"
        print (eval (read)) "\n"
      end.loop


    )
  )
)
