/// Checking the removal of object constructs.

#include <cstdlib>
#include <iostream>

#include <ast/libast.hh>
#include <ast/exp.hh>
#include <ast/decs-list.hh>
#include <parse/libparse.hh>
#include <bind/libbind.hh>
#include <type/libtype.hh>
#include <object/libobject.hh>
#include <object/desugar-visitor.hh>


const char* program_name = "test-desugar";

int
main()
{
  std::cout << "/* Test 1.  */\n";
}
