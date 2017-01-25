/**
 ** Test code for misc/escape.hh.
 */

#include <misc/escape.hh>
#include <misc/contract.hh>
#include <sstream>
#include <iostream>

using misc::escape;

int main()
{
  std::ostringstream s;

  s << escape("\a\b\f\n\r\t\v\\\"") << escape('\a');

  postcondition(s.str() == "\\007\\b\\f\\n\\r\\t\\v\\\\\\\"\\007");
}
