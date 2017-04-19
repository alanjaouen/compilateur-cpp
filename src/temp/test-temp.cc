/**
 ** Testing labels and temporaries.
 */

#include <iostream>
#include <sstream>
#include <misc/contract.hh>
#include <temp/temp.hh>
#include <temp/label.hh>

using namespace temp;

using TempList = temp_list_type;
using LabelList = label_list_type;

#define EXERCISE(What)                                  \
{                                                       \
  std::cout << "Testing " << #What << std::endl;        \
  const What t1("foo");                                 \
  const What t2;                                        \
                                                        \
  /* They are different. */                             \
  assertion(t1 != t2);                                  \
  assertion(!(t1 == t2));                               \
  /* Named are first. */                                \
  assertion(t1 < t2);                                   \
  assertion(t1 <= t2);                                  \
  /* Anonymous are last. */                             \
  assertion(t2 > t1);                                   \
  assertion(t2 >= t1);                                  \
  /* Named are not last. */                             \
  assertion(!(t1 > t2));                                \
  assertion(!(t1 >= t2));                               \
  /* Anonymous are not first. */                        \
  assertion(!(t2 < t1));                                \
  assertion(!(t2 <= t1));                               \
                                                        \
  std::cout << "Testing " << #What                      \
            << "Lists\n";                               \
                                                        \
  std::ostringstream s;                                 \
                                                        \
  What ## List list0;                                   \
  What ## List list1(t1);                               \
  What ## List list2(t1, What("bar"));                  \
  What ## List list3(t1, list2);                        \
                                                        \
  /* Check the sizes. */                                \
  assertion (list0.size() == 0                          \
             && list1.size() == 1                       \
             && list2.size() == 2                       \
             && list3.size() == 3);                     \
                                                        \
  /* Print the last list. */                            \
  s << list3;                                           \
  std::string output = s.str();                         \
  std::string expected = "foo, foo, bar";               \
  assertion(output == expected);                        \
}

int
main()
{
  EXERCISE(Temp);
  EXERCISE(Label);

  std::cout << "Testing TempMaps\n";
  TempMap map1;
  TempMap map2;
  TempMap *clone;

  // Insert some temps.
  map1[Temp("foo")] = Temp("1");
  map1["bar"] = "2";
  map1["foobar"] = Temp("3");

  map2["foo2"] = "4";
  map2["bar2"] = "5";
  map2["foobar"] = "6";

  // Is the size good?
  assertion(map1.size() == 3);

  // Does it insert known stuff?
  map1["foo"];
  assertion(map1.size() == 3);

  // Clone and destroy the clone.
  clone = map1.clone();

  // Is the data good in the clone?
  assertion((*clone)["bar"] == "2");

  // Is the original still alive?
  delete clone;
  assertion(map1["bar"] == "2");

  // Search.
  assertion(map1("foobar") == "3");
  assertion(map1.find("barfoo") == map1.end());
  map1.insert(map2);

  // Insertion.
  assertion(map1["foobar"] == "3");
  assertion(map1["foo2"] == "4");

  std::cout << "Testing TempSets\n";

  std::vector<Temp> list1 = { "foo", "bar" };

  // Different versions of the constructor.
  temp_set_type set1;
  temp_set_type set2(list1.begin(), list1.end());
  temp_set_type set3(list1);

  // Check "has".
  assertion(set2.has("foo"));
  assertion(!set2.has("foofoo"));

  // set1 = {foofoo, foobar}.
  set1 += "foofoo";
  set1 += "foobar";
  assertion(set1.has("foofoo"));

  // set1 = {foobar}.
  set1 -= "foofoo";
  assertion(!set1.has("foofoo"));

  // set2 = {foo, bar, foobar}
  set2 |= set1;
  assertion(set2.has("foobar"));

  // set2 = {foobar}.
  set2 &= set1;
  assertion(set1.has("foobar"));
}
