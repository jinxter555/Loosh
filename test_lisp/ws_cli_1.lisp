#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var c1
    
     = c1 (new System.Net.WSClient)
     = c2 (new System.Net.WSClient)
      c1.connect "0.0.0.0" 8080

    # run(n1)

    loop
      print "main "
      print(eval (read)) "\n"
    end.loop
    

  end.def

end.module


#---------------------------------

module System.Net

  class WSClient
    var addr port __cc_obj_id__
    def initialize()
      print "System.Net.WSClient.initialize():\n"
      call_extern (System.Net.SWSSClient apply) this :initialize
      print "cc_obj_id: " @__cc_obj_id__ "\n"
    end.def

    def read_text()
      call_extern (System.Net.SWSSClient apply) this :read_text
    end.def

    def write_text(msg)
      call_extern (System.Net.SWSSClient apply) this :write_text msg
    end.def

    def connect(h p)
      = @addr h
      = @port p
      call_extern (System.Net.SWSSClient apply) this :connect h p
    end.def


    def is_open()
      call_extern (System.Net.SWSSClient apply) this :is_open
    end.def

    def got_text()
      call_extern (System.Net.SWSSClient apply) this :got_text
    end.def

    def finalize()
      print "System.Net.WSSession: finalize():\n"
    end.def
  end.class

end.module
