/** \file translate/level.cc
 ** \brief Implementation of translate::Level.
 **/

#include <iostream>

#include <misc/algorithm.hh>
#include <misc/indent.hh>
#include <temp/label.hh>
#include <temp/temp.hh>
#include <tree/all.hh>
#include <frame/frame.hh>
#include <frame/access.hh>
#include <translate/level.hh>
#include <translate/access.hh>

namespace translate
{

  // Install a slot for the static link if needed.
  Level::Level(const misc::symbol& name,
               const Level* parent,
               frame::bool_list_type formal_escapes)
    : parent_(parent)
    , frame_(new frame::Frame(name))
  {
  // FIXED forest_b
    if (parent_)
      formal_alloc(true);
    
    // Install translate::Accesses for all the formals.
    for (const bool b : formal_escapes)
      formal_alloc(true);
  }

  Level::~Level()
  {
    misc::deep_clear(formals_);
    misc::deep_clear(locals_);
  }


  // In .cc because requires frame/frame.hh.
  temp::Label
  Level::label_get() const
  {
    return frame_get().label_get();
  }


  // In .cc because requires frame/frame.hh.
  int
  Level::frame_size_get() const
  {
    return frame_->get_current_frame_size();
  }


  // Higher level interface to frame::local_alloc.
  const Access*
  Level::local_alloc(bool escapes)
  {
    const Access* access = new Access(*this,
                                      frame_->local_alloc(escapes));
    locals_.emplace_back(access);
    return access;
  }

  const Access*
  Level::formal_alloc(bool escapes)
  {
    const Access* access = new Access(*this,
                                      frame_->formal_alloc(escapes));
    formals_.emplace_back(access);
    return access;
  }


  tree::rExp
  Level::sl() const
  {
    // An access to the first formal, hopefully the static link.
    return (*frame_get().formals_get().begin())->exp();
  }


  tree::rExp
  Level::fp(const Level& use_level) const
  {
    if (&use_level == this)
      return new tree::Temp("fp");

    // Use the static link to retrieve the frame pointer.
    // An access to the first formal, hopefully the static link.
    tree::rExp res = use_level.sl();
    // Loop until we find it.
    for (const Level* temp = use_level.parent_get();
         temp != this && temp != nullptr;
         temp = temp->parent_get())
      res = new tree::Mem(res);

    return res;
  }




  std::ostream&
  Level::dump(std::ostream& o) const
  {
    o << "translate::Level (" << misc::incendl
      << "formals = (" << formals_ << "), "
      << "parent = ";
    if (parent_)
      o << parent_->label_get();
    else
      o << "NONE";

    return o << ", " << frame_ << ')' << misc::decindent;
  }

} // namespace translate
