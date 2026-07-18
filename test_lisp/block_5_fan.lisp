%%module  kernel

module Kernel 
  class Map
    (var size (length 123) )
    def Map(x)  
     (print "hello class mp1()\n")
    end.def
infi
   

  end.class

  def main (x y)
    (type {main :int,  x:string y: :string})

    print "hello, world\n"
    assign m1 (new Map)
    assign method1 (:Map)
;      (p55 (55 2))
;      (print "\n\n")
    print m1 "\n\n"
    send m1 (:Map 555)
    send m1 ((method1) 555)

    for (1 10) 
      do (i) 
        print i
      end
    end.for

    for (1..3) (i)
      print i
    end.for

    for (map) (k v) 
    end.for

    for (map)
      do (k v) 
      end
    end.for

    while [] do
    end.while

    if (true)
      print "true"
    :else
      print "not true"
    end.if

    repeat
      print i
    until [] 
    end.repeat

    case x
    when (> x 5) 
      print "x is > 5"
    end.when
    when (< x 3) 
      print "x is < 3"
    end.when
    end.case

    case x
    (> 5) ( print ) 
    (< 3) ( print ) 
    end.case

    case x
    [x > 5] do print end.do
    [x < 3] do print end.do
    end.case

    cond 
    [x > 5] (print )
    [x < 3] (print )
    end.cond


    case x
    (:ok v)     (print)
    (:error v)  
    end.case


    case x
    (1) (print)
    [> 5] (print )
    [< 3] (print )
    end.case
    
    if[ (x y z) (2 3 4) ]
    endif

    if [ true ]
      p1()
      p2()
    :else
      p3()
      p4()
    end.if

  end.def



end.module


end.defun
