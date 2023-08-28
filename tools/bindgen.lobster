// Generates most of the language binding boilerplate from a simply formatted
// data file that resembles lobster declarations. 
import std
import core.lexbase

def genload_fn(paramname: string) -> string
def genstore_fn(expr: string) -> string

class str_appender:
   buf = ""
   len = 0

   def add(s):
      buf, len = write_substring(buf, len, s, 0)

   def line(s):
      add(s)
      add("\n")

   def result():
      return substring(buf, 0, len)

// Description of types we handle
struct TD:
   name: string
   lobster_tyspec: string
   wbnd_tyname: string
   // Call this to generate the C++  statement to pull the given type
   // from the lobster stack.
   loadfn: genload_fn
   // Call this to generate the c++ statement to push the given expression 
   // onto the lobster stack.
   storefn: genstore_fn
   pass_as_constref: bool

// All the types we can handle in bindings.
let known_types = [
   TD{
      name:"H", 
      lobster_tyspec: "I}}:2", 
      wbnd_tyname: "wo_handle", 
      loadfn: fn(name): "auto {name} = pop_wo_handle(sp);",
      storefn: fn(expr): "push_wo_handle(sp, {expr});",
      pass_as_constref: true
   },
   TD{name: "float3", 
      lobster_tyspec: "F}}:3", 
      wbnd_tyname: "XMFLOAT3", 
      loadfn: fn(name): "XMFLOAT3 {name};\npop_xmfloat3(sp,{name});", 
      storefn: fn(expr): "push_xmfloat3(sp, {expr});", 
      pass_as_constref: true
   },
   TD{
      name: "string",
      lobster_tyspec: "S",
      wbnd_tyname: "std::string_view", 
      loadfn: fn(name): "auto {name} = Pop(sp).sval()->strv();",
      storefn: fn(expr): "Push(sp, Value(vm.NewString({expr})));",
      pass_as_constref: true
   },
   TD{
      name: "bool",
      lobster_tyspec: "B",
      wbnd_tyname: "bool", 
      loadfn: fn(name): "auto {name} = Pop(sp).True();",
      storefn: fn(expr): "Push(sp, Value({expr}));",
      pass_as_constref: false
   },
   TD{
      name: "int", 
      lobster_tyspec: "I",
      wbnd_tyname: "int64_t", 
      loadfn: fn(name): "auto {name} = Pop(sp).ival();",
      storefn: fn(expr): "Push(sp, Value({expr});",
      pass_as_constref: false
   }
]

class param:
   name = ""
   type = -1  // index into known_types

   // Type declaration for a function parameter.
   def fun_ptype() -> string:
      let t = known_types[type]
      if t.pass_as_constref:
         return "{t.wbnd_tyname} const&"
      else:
         return t.wbnd_tyname

class fundef:
   name = ""
   params = [] :: param
   doc = ""
   returns = -1


def parse_bindings(fname: string) -> string?, [fundef]:
   let contents = read_file(fname)
   guard contents:
      return "file {fname} not found", []

   let L = lex_base{buf:contents, srcname: fname}
   let funs = []

   def error(msg):
      return L.format_error("", msg), [] from parse_bindings

   def keyword(k):
      L.ignore_ws():
         L.expect_word(k): error("expected keyword {k}")

   def identifier():
      L.skip_ws()
      guard L.chars_left():
         error("unexpected eof looking for identifier")
      let p0 = L.p
      guard is_alpha_ascii(L.cur_char()):
         error("Invalid identifier character")
      L.skip_while() c: is_alpha_ascii(c) or is_num_ascii(c) or c == '_'
      return substring(L.buf, p0, L.p - p0)

   def parse_param():
      let p = param{}
      p.name = identifier()
      L.expect(':'): error("expecting :")
      let tyname = identifier()
      let ti = find(known_types): _.name == tyname
      if ti >= 0:
         p.type = ti
      else:
         error("unknown type identifier: {tyname}")

      return p

   L.skip_ws()
   while L.chars_left():
      let fd = fundef{}
      L.skip_ws()
      fd.doc = L.expect_string(): error("Expecting doc string.")
      keyword("def")
      fd.name = identifier()
      L.expect('('): error("expected opening paren")
      L.skip_ws()
      while L.chars_left() and L.char() != ')':
         push(fd.params, parse_param())
         L.skip_ws()
         if not L.matched_word(","):
            break
         
      L.expect(')'): error("Closing paren not found")
      L.skip_ws()

      if L.matched_word("->"):
         let rty = identifier()
         let ti = find(known_types): _.name == rty
         if ti >= 0:
            fd.returns = ti
         else:
            error("unrecognized return type {rty}")

         L.skip_ws()

      push(funs, fd)


   return nil, funs

def join(items, delim):
   let out = str_appender{}
   var first=true
   for(items) it:
      if first:
         first = false
      else:
         out.add(delim)
      out.add(it)
   return out.result()

// We assume a formatter will be run on the resulting code, and don't put effort
// into making it pretty.
def write_lobster_binding_code(defs) -> string?:
   let out = str_appender{}
   out.line("// GENERATED for inclusion into lobutils.cpp, do not edit.")

   for(defs) d:
      out.add("anfr(\"wi_{d.name}\", \"")
      out.add(join(map(d.params): _.name, ","))
      out.add("\", ")

      let ltys = map(d.params): known_types[_.type].lobster_tyspec
      out.add("\"")
      out.add(join(ltys, ""))
      out.add("\", ")
      if d.returns >= 0:
         out.add("\"{known_types[d.returns].lobster_tyspec}\"")
      else:
         out.add("\"\"")
      out.line(",")

      out.line("\"{d.doc}\",")

      out.line("   [](StackPtr& sp, VM&) {{")
      // Pop params off in reverse order
      reverse(d.params) p:
         let loadf = known_types[p.type].loadfn
         out.line(loadf(p.name))

      // build up call to wbnd:: function 
      let cout = str_appender{}
      cout.add("wbnd::{d.name}(")
      cout.add(join(map(d.params): _.name, ", "))
      cout.add(")")

      if d.returns >= 0:
         let store = known_types[d.returns].storefn
         out.line("{store(cout.result())}")
      else:
         out.line("{cout.result()};")

      out.line("}});\n")

   let fname = "../src/lobutil.inl"
   if not write_file(fname, out.result(), 1):
      return "could not write {fname}"

   return nil

// Writes the function prototypes for the wibindings.h functions.
def write_wbnd_prototypes(defs):
   let out = str_appender{}
   out.line("// GENERATED for inclusion in wibindings.h by tools/bindgen.lobster, do not edit")

   for(defs) d:
      if d.returns >= 0:
         out.add("{known_types[d.returns].wbnd_tyname} ")
      else:
         out.add("void ")

      // this is included in namespace decl, so we don't need qualification.
      out.add("{d.name}(")
      let pdecls = map(d.params): "{_.fun_ptype()} {_.name}"
      out.add(join(pdecls, ", "))
      out.line(");")

   let fname = "../src/wibindings.inl"
   if not write_file(fname, out.result(), 1):
      return "could not write {fname}"

   return nil


// We assume we're in the tools directory.
let err, defs = parse_bindings("binddefs.txt")
guard not err:
   print(err)

var errb = write_lobster_binding_code(defs)
guard not errb:
   print("write_lobster_bindings: {errb}")

errb = write_wbnd_prototypes(defs)
guard not errb:
   print("write_wbnd_prototypes: {errb}")

print("done")