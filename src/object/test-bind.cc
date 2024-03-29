/// Test the binding with object extensions.

#include <cstdlib>
#include <iostream>
#include <ast/libast.hh>
#include <ast/exp.hh>
#include <ast/decs-list.hh>
#include <parse/libparse.hh>
#include <object/libobject.hh>

const char* program_name = "test-bind";

// Return true on correct binding.
inline static
bool
bound(const std::string& s)
{
  ast::DecsList* d = parse::parse_unit(s, true);
  misc::error e = object::bind(*d);
  std::cout << *d << std::endl;
  if (e)
    std::cerr << "error-->" << e << std::endl;
  delete d;
  return !e;
}


int
main()
{
  ast::bindings_display(std::cout) = true;
  /*assertion(bound(" let"
                  "   class C"
                  "   {"
                  "     var a := 0"
                  "   }"
                  "   var c := new C"
                  " in"
                  "   c.a := 2"
                  " end"));
  assertion(!bound(" let"
                   "   class C"
                   "   {"
                   "     var a := 0"
                   "   }"
                   "   class D extends C"
                   "   {"
                   "     method print() : int ="
                   "       a"
                   "   }"
                   "   var d := new D"
                   " in"
                   "   d.a := 2;"
                   "   d.print()"
                   " end"));
  assertion(bound(" let"
                  "   class C"
                  "   {"
                  "     var a := 0"
                  "   }"
                  "   class D extends C"
                  "   {"
                  "     method inc_a() ="
                  "       self.a := self.a + 1"
                  "     method add_a(x : int) : int ="
                  "       if x > 0 then"
                  "       ("
                  "         self.inc_a();"
                  "         self.add_a(x - 1)"
                  "       )"
                  "   }"
                  "   var d : D := new D"
                  " in"
                  "   d.a := 2;"
                  "   d.print()"
                  " end"));*/
}
