module Kernel 
  def main (x y) 

    if [ true != true ]
      print (+ 1 2 3) "\n"
      print "hello\n"
      print "hola\n"

      if [ true != true ]
        print "ni hao\n"
      :else
        print "oi gente \n"
      end.if

      return :ok

    :else
      print "world\n"
      print "mundo\n"
      return :error
    end.if

  end.def

end.module

