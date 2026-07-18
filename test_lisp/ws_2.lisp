#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var n1
    
     = n1 (new System.Net.WS)
     = n2 (new System.Net.WS)
     n1.server "0.0.0.0" 8080
     n2.server "0.0.0.0" 9999


    # run(n1)

    loop
      print "main "
      print(eval (read)) "\n"
    end.loop
    

  end.def

  # can't be spawn and access global from another process
  def run (x)
    print "run\n"
    # loop
    #   print "run() "
    #   print(eval (read)) "\n"
    # end.loop
    print "x: " x "\n"
    x.run()

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
