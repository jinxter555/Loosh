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

  def main (x y)
    = x1 999
    = r1 (new Range 1 13 3)
    ;send r1 :next 

      loop
        print (eval (read)) "\n"
      end.loop
  end.def

end.module
