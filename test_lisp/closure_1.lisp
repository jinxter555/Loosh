(module Kernel 
  (defun main (x y) my_func_des
    (
     (var c1)
     (assign c1 
      (do (x)
        print "hello, world1"
        print "hello, world2"
        print "hello, world3"
      )
     )
     (assign c2
      do (x)
        print "c2 hello, world1"
        print "c2 hello, world2"
        print "c2 hello, world3"
      end.do
     )
     


     


      loop
        print c2 "\n"
        (print(eval (read)) "\n")
      end.loop
    )
  )
)
