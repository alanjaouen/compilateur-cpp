// -*- C++ -*-

%module tiger_tree

%import ast/tiger_ast.i

%{
#  include <sstream>
#  include <tree/fragment.hh>
#  include <tree/fragments.hh>
#  include <tree/libtree.hh>
%}

template <typename T>
class std::list
{};
%template (FragmentList) std::list<tree::Fragment * >;

%include "tree/fragments.hh"
%extend tree::Fragments
{

  std::string
  __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }

}
%include "tree/libtree.hh"

