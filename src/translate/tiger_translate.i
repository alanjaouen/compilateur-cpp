// -*- C++ -*-

%module tiger_translate

%import ast/tiger_ast.i

%{
  #include <tree/fragments.hh>
  #include <translate/libtranslate.hh>
%}

%import "translate/fwd.hh"
%include "translate/libtranslate.hh"
