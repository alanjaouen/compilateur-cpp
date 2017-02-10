/**
 ** Test the string parser.
 **/

#include <cstdlib>
#include <iostream>
#include <ast/libast.hh>
#include <ast/exp.hh>
#include <parse/libparse.hh>

const char* program_name = "test-parse";

int
main()
{
  ast::Exp* e = parse::parse("a + b");
  std::cout << *e << std::endl;
  delete e;
  ast::Exp* f = parse::parse("let "
                             " function f(a : int, b : string) : int = a "
                             "in a end");
  std::cout << *f << std::endl;
  delete f;
  ast::Exp* g = parse::parse("let \
	var a:= 0 \
in \ 
	for i:=0 to 100 do (a:=a+1;())\
end");
  std::cout << *g << std::endl;
  delete g;
}
