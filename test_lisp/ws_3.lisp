#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var n1
    
     = n1 (new System.Net.WSListener)
     = n2 (new System.Net.WSListener)
     n1.server "0.0.0.0" 8080
    = s1 (n1.accept())
    # n2.server "0.0.0.0" 9999


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

  class WSSession
    var addr __cc_obj_id__
    def initialize()
      print "System.Net.WSSession.initialize():\n"
    end.def

    def read_text()
      call_extern (System.Net.SWSSSession apply) this :read_text
    end.def

    def write_text(msg)
      call_extern (System.Net.SWSSSession apply) this :write_text msg
    end.def

    def echo()
      call_extern (System.Net.SWSSSession apply) this :echo
    end.def

    def is_open()
      return( call_extern (System.Net.SWSSSession apply) this :is_open)
    end.def

    def echo2()
      var msg open_cond

      while [ \(@is_open()) ]
        = msg (@read_text())
        print msg
        # @write_text "got_it"
        @write_text msg
     end.while

    end.def


    def got_text()
      call_extern (System.Net.SWSSSession apply) this :got_text
    end.def

    def finalize()
      print "System.Net.WSSession: finalize():\n"
    end.def
  end.class

  class WSListener
    var addr port

    def initialize()
      print "System.Net.WSListener: initialize():\n"
    end.def
  
    def server(a p)
      print "server!\n\n"
      = @addr a
      = @port p
      call_extern (System.Net.SWSSListener apply) this :server a p
    end.def

    def accept()
        var ssocket
        = ssocket (new System.Net.WSSession)
        = ssid (call_extern (System.Net.SWSSListener apply) this :accept)
        print "ssid: " ssid "\n"
        = ssocket.__cc_obj_id__ ssid
        return ssocket
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
