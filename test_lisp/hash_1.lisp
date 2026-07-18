(module Kernel 
  (def main (x y) 
    (
      (var m1)
      (assign m1 
      (hash 
            (k1 123)
            (k2 456)
            (k3 456)
            ))
      = keys (call_extern (Map keys) m1 (2))
      print keys "\n"

      loop
          
        (print(eval (read)) "\n")
      end.loop
    )
  )
)
