/**
 ** Checking `for' loops desugaring.
 */

#include <ostream>
#include <string>

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <parse/libparse.hh>
#include <misc/file-library.hh>

using namespace ast;
using namespace desugar;

const char* program_name = "test-for-loops-desugar";

int
main()
{
  Exp* tree = parse::parse("for i := 0 to 42 do "
                           "  for j := 0 to 51 do (i;j)");

  std::cout << "/* === Original tree...  */\n"
            << *tree << std::endl;

  DesugarVisitor desugar(true, false);
  desugar(tree);
  delete tree;
  tree = nullptr;
  std::cout << "/* === Desugared tree...  */\n"
            << *desugar.result_get() << std::endl;
  delete desugar.result_get();
}
