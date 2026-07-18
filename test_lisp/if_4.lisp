module Kernel 
  def main (x y) 
    var v

    (= v 
    if [ true == true ]
      print "true=true\n"
      :ok
    end.if
    )

    print "v: " v "\n"

  end.def

end.module

