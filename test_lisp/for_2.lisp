module Kernel 
  class Range
    (var begin fin step state)

    def initialize(start fin step)  
      # assign needs to return a value
      = @begin start
      = @state start
      = @fin fin
      = @step  step

    end.def

    def init()  
      = @state @begin
      (:ok @state)
    end.def

    # return statement needed
    def next ()
      = @state (+ @state @step)
       # print "in next, state= " @state "\n"

      iif (>= @state @fin)
        return (:end @fin)
      end.iif

      iif(> @state @fin)
        return (:error nil)
        return (:ok @state)
      end.iif

      # print "i am in next(v): \n"
    end.def

    def end ()
      assign @state @begin
    end.def

    def finalize()
    end.def

  end.class

  defmacro forloop ( it cblock )
    quote
      var rv  (forever~ true)
      = rv (send (unquote it)  :init)
  
      # faz (rv) (unquote cblock)
      while(forever~)
        #= rv (send (unquote it)  :next)
        

        iif (= (:end _) rv)
         ( print "end\n"
          = forever~ false
         )
        end.iif

        iif (= (:error _) rv)
        (
          print "error\n"
          = forever~ false
        )
        end.iif


        faz (rv) (unquote cblock)
        = rv (send (unquote it)  :next)
        #faz (rv2) (unquote cblock)
        # faz (rv) (unquote cblock)

      

      end.while

      (:ok)
    end.quote


  end.defmacro

  def main (x y)
    var i forever
    # = r1 (new Range 1 6 3)
    = r1 (new Range 1 10 1)

    #send r1 :next 

    forloop r1 
      do (:ok i)
        print i ": what is up\n"
      end.do
    end.forloop

   (loop (print (eval (read)) "\n"))
  

  end.def

end.module
