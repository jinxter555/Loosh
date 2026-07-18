#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var forever (t true)

     = n1 (new System.Net.WS)
     n1.server "0.0.0.0" 8080


     #while[ \(f1.eof()) == false  ]
     #  print (f1.getline ()) "\n"
     #end.while

    loop
      "main "
      print(eval (read)) "\n"
    end.loop
    

  end.def

  def run (sock_obj)
    print "main run()"
    # loop
    #  "run: "
    #  print(eval (read)) "\n"
    #end.loop
    sock_obj.run()

  end.def
end.module


#---------------------------------

module System.Net
  class WS
    var addr port

    def initialize()
      print "System.Net.WS: initialize():\n"
    end.def
  
    def server(a p)
      = @addr a
      = @port p
     call_extern (System.Net.SWSS apply) this :server a p
    end.def

    def run()
      print "swss object run()!\n"
      call_extern (System.Net.SWSS apply) this :run :echo
    end.def



    def finalize()
      print "System.Net.WS: finalize():\n"
    end.def

  end.class

end.module
