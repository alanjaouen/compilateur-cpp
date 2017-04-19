/**
 ** \file frame/frame.cc
 ** \brief Implementation of frame::Frame.
 */

#include <misc/contract.hh>
#include <misc/algorithm.hh>

#include <frame/frame.hh>
#include <frame/access.hh>
#include <temp/label.hh>

namespace frame
{

  Frame::Frame(const temp::Label& label)
    : label_(label)
  {}

  Frame::Frame(const temp::Label& label,
               const bool_list_type& formal_escapes)
    : label_(label)
  {
    formal_alloc(formal_escapes);
  }

  Frame::Frame(const Frame& src)
    : label_(src.label_)
    , offset_(src.offset_)
    , arg_offset_(src.arg_offset_)
  {
    for (const Access* acs : src.formals_)
      formals_.emplace_back(acs->clone());
    for (const Access* acs : src.locals_)
      locals_.emplace_back(acs->clone());
  }

  Frame::~Frame()
  {
    misc::deep_clear(formals_);
    misc::deep_clear(locals_);
  }

  Frame&
  Frame::operator= (const Frame& src)
  {
    if (this == &src)
      return *this;
    new(this) Frame(src);
    return *this;
  }

  /*------------.
  | Accessors.  |
  `------------*/

  temp::Label
  Frame::label_get() const
  {
    return label_;
  }

  const access_list_type&
  Frame::formals_get() const
  {
    return formals_;
  }

  int
  Frame::get_current_frame_size() const
  {
    // the current frame size is always the current offset +
    // argument offset from the frame pointer
    return offset_ + arg_offset_;
  }



  /*-------------.
  | Allocation.  |
  `-------------*/

  const InFrame*
  Frame::frame_alloc()
  {
    int offset = - offset_;
    offset_ += word_size;
    return new InFrame(offset);
  }

  const Access*
  Frame::alloc(bool escapes)
  {
    if (escapes)
      return frame_alloc();
    else
      return new InRegister();
  }

  const Access*
  Frame::local_alloc(bool escapes)
  {
    const Access* access = alloc(escapes);
    locals_.emplace_back(access);
    return access;
  }

  const Access*
  Frame::formal_alloc(bool escapes_p)
  {
    const Access* access = alloc(escapes_p);
    formals_.emplace_back(access);
    return access;
  }

  void
  Frame::formal_alloc(const bool_list_type& l)
  {
    for (const bool b : l)
      formal_alloc(b);
  }

  void
  Frame::arg_add(size_t n)
  {
    if (arg_offset_ < n * word_size)
      arg_offset_ = n * word_size;
  }


  // Global word size (4 by default).
  size_t word_size = 4;



  std::ostream&
  operator<< (std::ostream& o, const Frame& f)
  {
    return o << "frame::Frame (" << f.label_get() << ")";
  }


} // namespace frame
