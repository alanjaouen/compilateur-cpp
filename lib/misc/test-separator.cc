/**
 ** Test code for misc/separator.hh features.
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <misc/contract.hh>
#include <misc/separator.hh>
#include <misc/pair.hh>

int main()
{
  {
    std::vector<int> v(4);
    std::fill(v.begin(), v.end(), 51);

    std::ostringstream s;
    s << misc::separate(v, ", ");
    assertion(s.str() == "51, 51, 51, 51");
  }

  {
    std::vector<int> v(4);
    std::fill(v.begin(), v.end(), 51);

    std::ostringstream s;
    s << misc::separate(v, misc::make_pair(",", " "));
    assertion(s.str() == "51, 51, 51, 51");
  }

  {
    int p = 51;
    std::vector<int*> v(4);
    std::fill(v.begin(), v.end(), &p);

    std::ostringstream s;
    s << misc::separate(v, ", ");
    assertion(s.str() == "51, 51, 51, 51");
  }
}
