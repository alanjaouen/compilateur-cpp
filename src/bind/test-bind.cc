// We really want to run the tests.
#undef NDEBUG
#include <iostream>
#include <cassert>
#include <ast/libast.hh>
#include <ast/decs-list.hh>
#include <parse/libparse.hh>
#include <bind/libbind.hh>

const char* program_name = "test-parse";

// Return true on correct binding.
static
bool
bound(const std::string& s)
{
  ast::DecsList* d = parse::parse_unit(s);
  misc::error e = bind::bind(*d);
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

  assert(!bound("a"));
  assert(bound("let var a := 0 in a end"));
  assert(bound("let var a := 0 in let var a := a in a end; a end"));
  assert(bound("let function f(a : int, b : string) : int = a in "
               " 5 "
               "end"));
  assert(!bound("let function f(a : int, a : string) : int = a in "
                " 5 "
                "end"));
}
