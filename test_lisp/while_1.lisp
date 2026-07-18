module Kernel 
  def main (x y) 
    var forever value
    assign t1  "t1 robot"
    assign forever true

    while [forever] 
      print "forever: " forever "\n"
      = value (eval (read)) "\n"
      if[value == "exit"]
        print "exiting...\n"
        = forever false
      :else
        print value "\n"
      end.if

    end.while

  end.def

end.module
