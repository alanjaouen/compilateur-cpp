/**
 ** Test the use of error.
 **/

#include <iostream>
#include <sstream>
#include <misc/contract.hh>
#include <misc/error.hh>

int
main()
{
  misc::error e;
  std::ostringstream ref;

  e << "Hello, World" << misc::error::bind << std::endl;
  {
    std::ostringstream ostr;

    ostr << e;
    ref << "Hello, World\n";
    assertion(ostr.str() == ref.str());
  }
  postcondition(e.status_get() == misc::error::bind);

  e << 42 << misc::error::parse << std::endl;
  {
    std::ostringstream ostr;
    ostr << e;
    ref << 42 << std::endl;
    assertion(ostr.str() == ref.str());
  }
  postcondition(e.status_get() == misc::error::parse);

  misc::error e2;
  std::ostringstream ref2;
  e2 << 51 << misc::error::scan << std::endl;
  {
    std::ostringstream ostr;
    ref2 << 51 << std::endl;
    ostr << e2;
    assertion(ostr.str() == ref2.str());
  }
  postcondition(e2.status_get() == misc::error::scan);

  e << e2;
  {
    std::ostringstream ostr;
    ostr << e;
    ref << e2;
    assertion(ostr.str() == ref.str());
  }
  postcondition(e.status_get() == misc::error::scan);
}
