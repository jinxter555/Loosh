module Kernel 
  def main (x y) 
    var forever (count 0)
    = t1  "t1 robot"
    # = forever true
    = forever (vt())

    print "forever: " forever "\n"

    while [ \(vt()) ]
      print "forever: " count " " t1 "\n"
       = count (+ count 1)
    #  [ count = count + 1]
    end.while

  end.def

  def vt()
    true
  end.def

end.module
