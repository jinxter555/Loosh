#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var forever (t true) f1
    assign t1  "t1 robot"
    assign forever false

    iif(t) 
      (print "forever: " forever "\n" )
      (print "sometimes, forever " forever "\n" )
    end.iif



     = f1 (new System.Io.File)

     f1.open("/etc/hosts")

     #while[ \(f1.eof()) == false  ]
     #  print (f1.getline ()) "\n"
     #end.while

    loop
      print(eval (read)) "\n"
    end.loop
    

  end.def

end.module

module My.Mod1
  def p1 ()
      print "p1\n"
  end.def
end.module

module System.Io
  class File
    var file_name 

    def initialize()
      # print "System.Io.File() initialize():\n"
    end.def
  
    def open(fn)
      = @file_name fn
     call_extern (System.Io.File apply) this :open fn
    end.def

    def getline()
     call_extern (System.Io.File apply) this :getline
    end.def

    def close()
     call_extern (System.Io.File apply) this :close
    end.def

    def eof()
     call_extern (System.Io.File apply) this :eof 
    end.def

    def finalize()
      print "System.Io.File() finalize():\n"
    end.def

  end.class

end.module
