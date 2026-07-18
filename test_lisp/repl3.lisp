module Kernel 

  def repl3 ()
  end.def

  def repl ()
    var input
    print "hello"
  end.def

  def repl2 ()
    var (i 0)
    while [i < 10]
      print "i " i "\n";
      [i = i+1]
    end.while
  end.def

  def main (x y)
    print "hello main"

    var input
      = input "exit"

   if [input == "exit"]
   end.if

;    repl()
;    repl2()



  end.def

  def f1 ()
    print "here in f1\n"
    return :ok
  end.def

end.module
