/**
 ** \file tree/cjump.hxx
 ** \brief Inline implementation of tree::Cjump.
 **/

#pragma once

#include <tree/cjump.hh>
#include <misc/contract.hh>
#include <temp/label.hh>

namespace tree
{

  inline rExp
  Cjump::left_get() const
  {
    return child_get(0).cast<Exp>();
  }

  inline rExp
  Cjump::right_get() const
  {
    return child_get(1).cast<Exp>();
  }

  inline temp::Label
  Cjump::label_true_get() const
  {
    const rName name = child_get(2).cast<Name>();
    return name->label_get();
  }

  inline temp::Label
  Cjump::label_false_get() const
  {
    const rName name = child_get(3).cast<Name>();
    return name->label_get();
  }

  inline void
  Cjump::label_false_set(const temp::Label& false_label)
  {
    children_.pop_back();
    children_.emplace_back(new Name(false_label));
  }

  inline temp::label_list_type
  Cjump::labels_get() const
  {
    temp::label_list_type res(label_true_get(), label_false_get());
    return res;
  }

  inline void
  Cjump::flip()
  {
    precondition(children_.size() == 4);
    rTree iftrue = child_get(2);
    rTree iffalse = child_get(3);
    children_.pop_back();
    children_.pop_back();
    children_.emplace_back(iffalse);
    children_.emplace_back(iftrue);
    switch (relop_)
      {
      case eq:  relop_ = ne;  break;
      case ne:  relop_ = eq;  break;
      case lt:  relop_ = ge;  break;
      case gt:  relop_ = le;  break;
      case le:  relop_ = gt;  break;
      case ge:  relop_ = lt;  break;
      case ult: relop_ = uge; break;
      case ugt: relop_ = ule; break;
      case ule: relop_ = ugt; break;
      case uge: relop_ = ult; break;
      }
  }

  inline const Cjump::Relop&
  Cjump::relop_get() const
  {
    return relop_;
  }

} // namespace tree
