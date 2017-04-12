// -*- C++ -*-

%module tiger_temp

%{
  #include <temp/libtemp.hh>
  #include <misc/endomap.hh>
%}

%include "temp/libtemp.hh"

// Show only a simplified version of TempMap.
// We need it to instantiate easily a TempMap object in Python.

namespace temp {

  class TempMap
  {};

}
