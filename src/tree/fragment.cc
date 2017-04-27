/**
 ** \file tree/fragment.cc
 ** \brief Implementation of tree::Fragment.
 **/

#include <misc/escape.hh>
#include <misc/algorithm.hh>
#include <misc/indent.hh>

#include <frame/access.hh>
#include <tree/fragment.hh>
#include <tree/exp.hh>
#include <tree/stm.hh>

namespace tree
{

  /*--------------------.
  | DataFrag: strings.  |
  `--------------------*/

  DataFrag::DataFrag(const temp::Label& label, const std::string& data)
    : label_(label)
    , data_(data)
  {}

  std::ostream&
  DataFrag::dump(std::ostream& o) const
  {
    return o << "label " << label_ << std::endl
             << "\t\"" << misc::escape(data_) << "\"";
  }

  void
  DataFrag::accept(Visitor& v)
  {
    v(*this);
  }

  void
  DataFrag::accept(ConstVisitor& v) const
  {
    v(*this);
  }


  /*-----------------------.
  | ProcFrag: procedures.  |
  `-----------------------*/

  ProcFrag::ProcFrag(const temp::Label& label,
                     const misc::symbol& name,
                     const rStm& body,
                     const frame::Frame* frame)
    : label_(label)
    , name_(name)
    , body_(body)
    , frame_(frame)
    , save_fp_(temp::Temp())
  {}

  /* Display this fragment.

  Given that we use this output as an input for our VM, it needs
  to include more information than what suggests Appel (e.g., the
  size of the frame).  Since this information will be needed in
  the sequel, it seems better to exhibit it: (i) HAVM is simpler,
  (ii) students can check their results more easily (more things
  are visible), and (iii) it shows more things about the calling
  conventions, which is better when teaching calling
  conventions...

  There are three parts:

  1. prologue (saving fp, moving fp, allocating the frame, moving
  the arguments to the right place)

  2. body (run the content of the fragment)

  3. epilogue (reestablishing the caller's frame).  */

  std::ostream&
  ProcFrag::dump(std::ostream& o) const
  {
  // FIXME: Some code was deleted here.
    o << "# Routine: _main" << misc::iendl
      << "label main" << misc::iendl 
      << "# Prologue" << misc::iendl
      << "#body"  << misc::iendl
      << *body_ << misc::iendl
      << "#epilogue" << misc::iendl
      << "label end" << misc::iendl;
    return o;
  }

  void
  ProcFrag::accept(Visitor& v)
  {
    v(*this);
  }

  void
  ProcFrag::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  /// We cannot inline the destructor in the .hxx file. Defining it here is
  /// a way to avoid internal compiler error from gcc. This ICE has been
  /// reported here : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=68220.
  ProcFrag::~ProcFrag()
  {
    delete frame_;
  }


} // namespace tree
