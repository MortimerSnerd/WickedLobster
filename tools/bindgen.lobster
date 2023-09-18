// Generates most of the language binding boilerplate from a simply formatted
// data file that resembles lobster declarations. 
import std
import core.lexbase

def genload_fn(paramname: string) -> string
def genstore_fn(expr: string) -> string

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
   // Handle for a tagged pointer of some sort.
   TD{
      name:"H", 
      lobster_tyspec: "I}}:2", 
      wbnd_tyname: "wo_handle", 
      loadfn: fn(name): "auto {name} = pop_wo_handle(sp);",
      storefn: fn(expr): "push_wo_handle(sp, {expr});",
      pass_as_constref: true
   },
   // Handle for a tagged pointer where Lobster takes care of the lifetime.
   // (A is for Alien)
   TD{
      name:"A", 
      lobster_tyspec: "R:alien", 
      wbnd_tyname: "wo_handle", 
      loadfn: fn(name): "auto {name} = pop_alien(sp);",
      storefn: fn(expr): "push_alien(sp, vm, {expr});",
      pass_as_constref: true
   },
   TD{
      name:"X", 
      lobster_tyspec: "I}}:2", 
      wbnd_tyname: "wo_iterator", 
      loadfn: fn(name): "auto {name} = pop_wo_iterator(sp);",
      storefn: fn(expr): "push_wo_iterator(sp, {expr});",
      pass_as_constref: true
   },
   TD{name: "float3", 
      lobster_tyspec: "F}}:3", 
      wbnd_tyname: "XMFLOAT3", 
      loadfn: fn(name): "XMFLOAT3 {name};\npop_xmfloat3(sp,{name});", 
      storefn: fn(expr): "push_xmfloat3(sp, {expr});", 
      pass_as_constref: true
   },
   TD{name: "float4", 
      lobster_tyspec: "F}}:4", 
      wbnd_tyname: "XMFLOAT4", 
      loadfn: fn(name): "XMFLOAT4 {name};\npop_xmfloat4(sp,{name});", 
      storefn: fn(expr): "push_xmfloat4(sp, {expr});", 
      pass_as_constref: true
   },
   TD{name: "float2", 
      lobster_tyspec: "F}}:2", 
      wbnd_tyname: "XMFLOAT2", 
      loadfn: fn(name): "XMFLOAT2 {name};\npop_xmfloat2(sp,{name});", 
      storefn: fn(expr): "push_xmfloat2(sp, {expr});", 
      pass_as_constref: true
   },
   TD{name: "int2", 
      lobster_tyspec: "I}}:2", 
      wbnd_tyname: "XMINT2", 
      loadfn: fn(name): "XMINT2 {name};\npop_xmint2(sp,{name});", 
      storefn: fn(expr): "push_xmint2(sp, {expr});", 
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
      wbnd_tyname: "int32_t", 
      loadfn: fn(name): "auto {name} = (int32_t)Pop(sp).ival();",
      storefn: fn(expr): "Push(sp, Value({expr}));",
      pass_as_constref: false
   },
   TD{
      name: "iint",  // We want a real 64 bit value, not 32 bit.
      lobster_tyspec: "I",
      wbnd_tyname: "int64_t", 
      loadfn: fn(name): "auto {name} = Pop(sp).ival();",
      storefn: fn(expr): "Push(sp, Value({expr}));",
      pass_as_constref: false
   },
   TD{
      name: "float", 
      lobster_tyspec: "F",
      wbnd_tyname: "float", 
      loadfn: fn(name): "auto {name} = Pop(sp).fltval();",
      storefn: fn(expr): "Push(sp, Value({expr}));",
      pass_as_constref: false
   },
   // All lobster reals are doubles, but in most cases we only need float.  
   // This is for cases where we need double.
   TD{
      name: "double",      
      lobster_tyspec: "F",
      wbnd_tyname: "double", 
      loadfn: fn(name): "auto {name} = Pop(sp).fval();",
      storefn: fn(expr): "Push(sp, Value({expr}));",
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
   returns = [] :: int

def retval_param_name(ix: int):
   return "retval{ix+1}"

def parse_bindings(fname: string) -> string?, [fundef]:
   let contents = read_file(fname)
   guard contents:
      return "file {fname} not found", []

   let L = lex_base{buf:contents, srcname: fname}
   let funs = []

   def error(msg):
      return L.format_error("", msg), [] from parse_bindings

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

   def parse_struct_def():
      let members = []
      var make_constructor = true
      var managed_handles = false
      L.skip_ws()
      let sname = identifier()
      L.skip_ws()

      var maybe_modifiers = true
      while maybe_modifiers:
         if L.matched_word("!bare"):
            make_constructor = false
         elif L.matched_word("!managed"):
            managed_handles = true
         else:
            maybe_modifiers = false

      while L.chars_left() and not L.matched_word("endstruct"):
         push(members, parse_param())
         L.skip_ws()

      let handname = if managed_handles: "A" else: "H"
      let hix = find(known_types): _.name == handname
      assert hix >= 0

      if make_constructor:
         // Construct and destruct.
         push(funs, fundef{
            name: "create_{sname}", 
            params: [], 
            returns: [hix]})
         if not managed_handles:
            push(funs, fundef{
               name: "delete_{sname}", 
               params: [param{
                  name: sname, 
                  type: hix}], 
               returns: []})

      // Accessors
      for(members) m:
         push(funs, fundef{
            name: "set_{sname}_{m.name}", 
            doc: "Sets {sname}.{m.name}",
            params: [
               param{
                  name: sname, 
                  type: hix}, 
               param{
                  name: "v", 
                  type: m.type}
            ],
            returns: []})
         push(funs, fundef{
            name: "get_{sname}_{m.name}", 
            doc: "Gets {sname}.{m.name}",
            params: [
               param{
                  name: sname, 
                  type: hix}
            ],
            returns: [m.type]})

   L.skip_ws()
   while L.chars_left():
      let fd = fundef{}
      L.skip_ws()
      fd.doc = L.expect_string(): error("Expecting doc string.")
      L.skip_ws()
      if L.matched_word("struct"):
         parse_struct_def()
      elif L.matched_word("def"):
         L.skip_ws()
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
            while true:
               L.skip_ws()
               let rty = identifier()
               let ti = find(known_types): _.name == rty
               if ti >= 0:
                  push(fd.returns, ti)
               else:
                  error("unrecognized return type {rty}")
               L.skip_ws()
               if not L.matched_word(","):
                  break

         push(funs, fd)
      else:
         error("Was expecting def|struct")


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
      if length(d.returns) > 0:
         let rstr = join(map(d.returns) ti: known_types[ti].lobster_tyspec, "")
         out.add("\"{rstr}\"")
      else:
         out.add("\"\"")
      out.line(",")

      out.line("\"{d.doc}\",")

      out.line("   [](StackPtr& sp, VM& vm) {{")
      // Pop params off in reverse order
      reverse(d.params) p:
         let loadf = known_types[p.type].loadfn
         out.line(loadf(p.name))

      let param_valnames = map(d.params): _.name

      // If there is more than one return value, create locals to hold the values
      // passed as out parameters.
      for_range(1, length(d.returns)) i:
         let ty = known_types[d.returns[i]]
         let pname = retval_param_name(i)
         out.line("{ty.wbnd_tyname} {pname};")
         push(param_valnames, pname)

      // build up call to wbnd:: function 
      let cout = str_appender{}
      cout.add("wbnd::{d.name}(")
      cout.add(join(param_valnames, ", "))
      cout.add(")")

      if length(d.returns) > 0:
         // Stores the direct return of the function.
         let storefst = known_types[d.returns[0]].storefn
         out.line("{storefst(cout.result())}")

         // If there are multiple returns, this catches the rest.
         for_range(1, length(d.returns)) i:
               let ti = d.returns[i]
               let store = known_types[ti].storefn
               let pname = retval_param_name(i)
               out.line("{store(pname)}")
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
      if length(d.returns) > 0:
         // Just the first return gets to be a return type for the C++ function
         out.add("{known_types[d.returns[0]].wbnd_tyname} ")
      else:
         out.add("void ")

      // this is included in namespace decl, so we don't need qualification.
      out.add("{d.name}(")
      let pdecls = map(d.params): "{_.fun_ptype()} {_.name}"

      // Add return parameters if there are more than one return from the function.
      for_range(1, length(d.returns)) i:
         let ty = known_types[d.returns[i]]
         push(pdecls, "{ty.wbnd_tyname}& {retval_param_name(i)}")

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
