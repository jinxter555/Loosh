module Kernel 

  def repl ()

    loop
      print (eval (read)) "\n"
    end.loop
  end.def




  def main (x y)
    print "hello main\n"
    repl()
    f1()
    print "goodbye main\n"


  end.def

  def f1 ()
    print "here in f1\n"
    ;return :ok
  end.def

end.module
