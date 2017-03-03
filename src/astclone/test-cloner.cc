/**
 ** Checking astclone::Cloner.
 */

#include <ostream>
#include <list>

#include <astclone/cloner.hh>
#include <ast/libast.hh>
#include <parse/libparse.hh>
#include <misc/file-library.hh>

using namespace ast;
using namespace astclone;

const char* program_name = "test-cloner";

static
void
clone_ast(const std::string& s)
{
  ast::Exp* e = parse::parse(s);

  std::cout << *e << std::endl;

  Cloner clone;
  clone(e);
  delete e;
  std::cout << *clone.result_get() << std::endl;
  delete clone.result_get();
}

int
main()
{
  std::cout << "First test...\n";
  clone_ast("( (a := 5); (a + 1) )");

  std::cout << "Second test...\n";
  clone_ast("let function f() : int = g(a) in f() end");
}
