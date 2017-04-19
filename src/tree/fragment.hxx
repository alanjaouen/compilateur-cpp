/**
 ** \file tree/fragment.hxx
 ** \brief Inline methods for tree/fragment.hh.
 **/

#pragma once

#include <temp/temp.hh>
#include <tree/fwd.hh>
#include <tree/fragment.hh>
#include <temp/label.hh>

namespace tree
{

  inline std::ostream&
  operator<<(std::ostream& o, const Fragment& f)
  {
    return f.dump(o);
  }


  /*--------------------.
  | DataFrag: strings.  |
  `--------------------*/

  inline temp::Label
  DataFrag::label_get() const
  {
    return label_;
  }

  inline const std::string&
  DataFrag::data_get() const
  {
    return data_;
  }


  /*-----------------------.
  | ProcFrag: procedures.  |
  `-----------------------*/

  inline temp::Label
  ProcFrag::label_get() const
  {
    return label_;
  }

  inline const misc::symbol&
  ProcFrag::name_get() const
  {
    return name_;
  }

  inline rStm
  ProcFrag::body_get() const
  {
    return body_;
  }

  inline void
  ProcFrag::body_set(const rStm& body)
  {
    body_ = body;
  }

  inline const frame::Frame&
  ProcFrag::frame_get() const
  {
    return *frame_;
  }


} // namespace tree
