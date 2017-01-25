/**
 ** \file  misc/escape.cc
 ** \brief Implementation for misc/escape.hh.
 **/

#include <ios>
#include <iomanip>
#include <cctype>
#include <misc/escape.hh>

namespace misc
{
  std::ostream&
  escaped::print(std::ostream& ostr) const
  {
    return escape_(ostr, pobj_str_);
  }

  std::ostream&
  escaped::escape_(std::ostream& o, const std::string& es) const
  {
    // For some reason yet to be found, when we use the locale for
    // std::isprint, Valgrind goes berzerk.  So we no longer do the
    // following:
    //
    // static std::locale locale("");
    //
    // if (std::isprint(*p, locale))
    std::ios_base::fmtflags flags = o.flags(std::ios_base::oct);
    char fill = o.fill('0');

    for (const auto& p : es)
      switch (p)
        {
          /* The GNU Assembler does not recognize `\a' as a valid
             escape sequence, hence this explicit conversion to the
             007 octal character.  For more information, see
             http://sourceware.org/binutils/docs/as/Strings.html.  */
        case '\a': o << "\\007"; break;
        case '\b': o << "\\b"; break;
        case '\f': o << "\\f"; break;
        case '\n': o << "\\n"; break;
        case '\r': o << "\\r"; break;
        case '\t': o << "\\t"; break;
        case '\v': o << "\\v"; break;

        case '\\': o << "\\\\"; break;
        case '\"': o << "\\\""; break;
        default:
          if (std::isprint(p))
            o << p;
          else
            o << "\\" << std::setw(3) << (int)(unsigned char) p;
        }

    o.fill(fill);
    o.flags(flags);
    return o;
  }
} // namespace misc
