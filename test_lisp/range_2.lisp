module Kernel 
  class Range
    (var begin fin step state)

    def Range(start fin step)  
      ; assign needs to return a value
      = @begin start
      = @state start
      = @fin fin
      = @step  step

    end.def

    def init()  
      = @state @begin
      (:ok @state)
    end.def

    ; return statement needed
    def next ()
      = @state (+ @state @step)
      print "next: " @state "\n"

      if (== @state @fin)
        return (:end @fin)
      end.if

      if (> @state @fin)
        return (:error nil)
        return (:ok @state)
      end.if

      ;print "i am in next(v): \n"
    end.def

    def end ()
      assign @state @begin
    end.def

  end.class

  defmacro forloop ( it cblock )
    quote
      var (forever true)
      = i (send (unquote it) :init)
      (faz  i unquote(cblock))
    end.quote
  end.defmacro

  def main (x y)
    var i forever
    = x1 999
    = r1 (new Range 1 13 3)
    ;send r1 :next 

    = forever true
    = i (send r1 :init)
    print i "\n"
    while (forever)
      = i (send r1 :next)
      if (= (:end v) i)
      (
        = forever  false
        print i "\n"
      )
      ( print i "\n")
      end.if
    end.while


      loop
        print (eval (read)) "\n"
      end.loop
  end.def

end.module
