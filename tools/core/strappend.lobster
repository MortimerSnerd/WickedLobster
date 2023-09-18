// Dead simple string appender

class str_appender:
   buf = ""
   len = 0

   def add(s):
      buf, len = write_substring(buf, len, s, 0)

   def add(indent: int, s: string):
      for(indent): add("   ")
      add(s)

   def nl():
      add("\n")

   def line(s):
      add(s)
      nl()

   def line(indent: int, s: string):
      for(indent): add("   ")
      add(s)
      nl()

   def result():
      return substring(buf, 0, len)



