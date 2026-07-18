module Kernel 
  def main (x y) 
    
  
     var (v1 "hola mundo") (v2 "halo welt")
     print "hello "
     print "world\n" 
#     print v1 ", " v2 "\n"

      
     # p55 88888888
     loop
        print (eval (read)) "\n"
      end.loop
  end.def


  # spawn p55 5000
  def p55(value)
    print "p55 hello\n" 
    print (process :pid) ", " (process :ppid) "\n"
    # print :frame_front "\n"
    print "sleep value:" value "\n"
    sleep value
    print "p55 world\n" 

  

#      loop
#        print (eval (read)) "\n"
#      end.loop


  end.def



  def runq()
    while [true]
      # print "run queue!\n"
      print "process id: "  (process :pid) ", " (process :ppid) "\n"
      process :receive
      process :queue :worker :eval
      process :queue :inbox :wait
     # sleep 5000
    end.while
  end.def



end.module

