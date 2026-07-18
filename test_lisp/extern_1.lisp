(module Kernel 
  (defun main (x y) my_func_des
    (
      (var m1 s1 v5)
      (assign s1 "hello, world1")
      (assign m1 
        (map 
            (k1 123)
            (k2 456)
            (k3 456)
            (k4 (map(l1 456)))
            (k5 s1)
        )
      )
      (print m1 "\n\n")
      (print "keys m1: " (call_extern (Map keys) m1 ()))
      (print "\n")
      (print "m1[k1]: " (call_extern (Map get) m1 ('k1)))
      (print "\n")
      (print "m1[k5]: " (call_extern (Map get) m1 ('k5)   ))
      (print "\n")
;      (print "m1[__object_info__]: " (call_extern (Map get) m1 ('__object_info__)) "\n")
;      (print "m1[__object_info__2]: " (call_extern (Map get) m1 '(__object_info__2)) "\n")
   ;   (call_extern (Map set) m1 '(pi 3.1415))

      (call_extern (Map set) m1 ('pi 3.1415))
      ;(call_extern (Map set) m1 '(pi 3.1415))


      (print "\n\n" m1 "\n\n")
      (print (call_extern (Map has) m1 ('k1)) "\n")
      ;(print (call_extern (Map del) m1 ('k1)) "\n")
      ((call_extern (Map del) m1 ('k1)) "\n")
      (print (call_extern (Map has) m1 ('k1)) "\n")
      (print "\n\n" m1 "\n\n")


  ;    (assign v5  (call_extern (Map map_get_value) m1 '(k5)))
  ;    (print "v5: " v5 "\n")
    )
  )
)
