#!./main.out

# use :namespace Main
# use :namespace England

# this is a test
module Kernel 
  def main (x y) 
    var n1  my_kinda_var
    
     # = r1 (new Lang.Text.RegExp '(\d)\s(\w+)' (:icase :ecmas))
     #  = r1 (new Lang.Text.RegExp '(\d\d)' (:icase :ecmas))
       (new Lang.Text.RegExp '(\d\d)' (:icase :ecmas))
     # = r1 (new Lang.Text.RegExp '\d\d'  :icase)

     # = bob (root)

    loop
      # print "main "
      print(eval (read)) "\n"
    end.loop
    

  end.def



end.module


#---------------------------------

module Lang.Text

  class RegExp
    var pattern flags FOUND
    def initialize(p f)
      = @pattern p
      = @flags f
      # print "RegExp init\n\n"
      call_extern (Lang.RE.CCRE apply) this :initialize p f
    end.def

    def match_part(text)
      call_extern (Lang.RE.CCRE apply) this :match :part text
    end.def

    def match_full(text)
      print "match_full(text)\n"
      call_extern (Lang.RE.CCRE apply) this :match :full text
    end.def

    #----

    def extract_part(text)
      print "extract_part(text)\n"
      call_extern (Lang.RE.CCRE apply) this :extract :part text
    end.def

    def extract_full(text)
      print "extract_full(text)\n"
      call_extern (Lang.RE.CCRE apply) this :extract :full text
    end.def

    def replace(text_src text_tgt)
      print "replace(src tgt)\n"
      call_extern (Lang.RE.CCRE apply) this :replace text_src text_tgt
    end.def

    def finalize()
      print "Lang.RE.CCRE finalize():\n"
    end.def
  end.class


end.module
