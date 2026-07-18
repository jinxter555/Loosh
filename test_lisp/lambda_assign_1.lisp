module Kernel 
  def main (x y)

      (assign l1 
        lambda  (x y)
            print "hello lambda\n"
            print "x: " x ", y: " y "\n"
        end.lambda 
      )
      assign l2 "hello"
      = list1 (11 12 13 14 15)


     # ((lambda (number) (* 7 number)) 3)

    # print l1 "\n\n" l1 "\n"
  #      funcall l1 123 "holy moly"
  #      funcall l1 456 "cow moo"
        funcall l1 789 (list1  1 2 3)
  #      funcall l1 1.239 list1
      # funcall l1 2 "holy moly guacamoly"
    loop
      print(eval(read)) "\n"
    end.loop
  end.def 
end.module
