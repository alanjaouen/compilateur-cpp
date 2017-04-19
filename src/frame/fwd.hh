/**
 ** \file frame/fwd.hh
 ** \brief Forward declarations for frame:: items.
 */

#pragma once

#include <vector>

namespace frame
{

  // frame.hh.
  class Frame;

  // access.hh.
  class Access;
  class InRegister;
  class InFrame;

  /// Global word size, in byte.
  // FIXME: this is of course very unsatisfying, as it is a global,
  // and should be bound to the target::Cpu.
  extern size_t word_size;

  using bool_list_type = std::vector<bool>;
  using access_list_type = std::vector<const Access*>;

} // namespace frame
