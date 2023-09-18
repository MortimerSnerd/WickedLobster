// Some simple lexing support. So I don't have to keep repeating common
// functions in parsers built into a single function.

// Minimal buffer position support that can be used in a function. 
// Intentionally avoid having an error() function, because in a lot of
// cases, you'll want to do a return from on errors, and that doesn't work 
// well if done from a vtable method. 
class lex_base:
    buf = ""
    p = 0
    line = 1
    srcname: string = "<UNKNOWN>"

    // Returns a standard error message format with line and source name. 
    def format_error(context: string, msg: string) -> string:
        return "{srcname}({line},{column()}): error {context} {msg}"

    // Calculates the column number the current position is at.
    def column():
        var i = p
        var c = 0
        while i >= 0:
            if buf[i] == '\n' or buf[i] == '\r':
                return c
            else:
                i--
                c++
        return c

    // Returns current char, or \0 if at EOF.
    def cur_char():
        if p < length(buf):
            return buf[p]
        else:
            return 0

    // Returns current char unconditionally.
    def char():
        return buf[p]

    // Returns character at +n position, or 0 if that would be past eof.
    def lookahead(n: int):
       let pl = n + p
       if pl < length(buf):
          return buf[pl]
       else:
          return 0

    // If the current char is a EOL sequence, skips past it and
    // updates "line", returns true.
    def ate_eol() -> bool:
        let c = cur_char()
        if c == '\r':
            p++
            if cur_char() == '\n':
                p++
            line++
            return true
        elif c == '\n':
            p++
            line++
            return true
        return false

    // Expects the given character, calls body with an error message if it's
    // not there.
    def expect(c: int, body):
        if p < length(buf):
            if c == buf[p]:
                p++
            else:
                body("was expecting \'{unicode_to_string([c])}\' but got \'{unicode_to_string([buf[p]])}\'")
        else:
            body("was expecting \'{unicode_to_string([c])}\' but got EOF")
 
    // Expects a string literal, call errbody(err message) if it's not there.
    def expect_string(errbody) -> string:
        expect('\"', errbody)
        let spos = p
        skip_while(): _ != '\"'
        expect('\"', errbody)
        return substring(buf, spos, p - spos - 1)            

    def expect_int(body):
        let start = p
        if char() == '-' or char() == '+':
            p++
        skip_while(): is_num_ascii(_)
        let istr = substring(buf, start, p - start)
        let v, all = string_to_int(istr, 10)
        if all:
            return v
        else:
            body("expected int, but got {istr}")
            return 0

    def expect_float(body):
        let start = p
        // loose, but string_to_float will notice if we're wrong.
        skip_while(): is_num_ascii(_) or _ == '.' or _ == '-' or _ == 'e' or _ == 'E'
        let fs = substring(buf, start, p - start)
        let v, all = string_to_float(fs)
        if all:
            return v
        else:
            body("expecting a float, got {fs}")
            return 0.0

    def matched_word(word: string) -> bool:
        if (p+length(word)) < length(buf) and compare_substring(word, 0, buf, p, length(word)) == 0:
            p += length(word)         
            return true
        else:
            return false

    def matched_char_from(chars: string) -> bool:
       if chars_left():
          let c = buf[p]
          for(length(chars)) ci:
            if chars[ci] == c:
               return true
       return false

    def matched_char(c: int) -> bool:
       if p+1 < length(buf) and c == buf[p]:
          p++
          return true
       else:
          return false

    def ignore_ws(body):
        skip_ws()
        body()
        skip_ws()

    def expect_word(word: string, errbody):
        let bleft = length(buf) - p
        if length(word) > bleft:
            errbody("expecting \'{word}\' but hit EOF")
        else:
            if not matched_word(word):
                errbody("expecting \'{word}\' but got: {substring(buf, p, length(word))}")
        
    def skip_while(sbod):
        while p < length(buf) and sbod(buf[p]):
            p++

    def skip_ws():
        while p < length(buf):
            if ate_eol():
                pass()
            elif buf[p] == ' ' or buf[p] == '\t':
                p++
            else:
                return

    def at_eof():
        return p >= length(buf)

    def chars_left():
        return p < length(buf)

def is_alpha_ascii(i: int):
    return (i >= 'a' and i <= 'z') or (i >= 'A' and i <= 'Z')

def is_num_ascii(i: int):
    return i >= '0' and i <= '9'

