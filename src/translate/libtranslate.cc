/**
 ** \file translate/libtranslate.cc
 ** \brief Public translate module interface implementation.
 **/

#include <translate/libtranslate.hh>
#include <tree/fragments.hh>
#include <translate/translator.hh>


namespace translate
{
  std::unique_ptr<tree::Fragments>
  translate(ast::Ast& ast
           )
  {
    Translator translate;
    translate(ast);
    return std::unique_ptr<tree::Fragments>(translate.fragments_get());
  }

} // namespace translate
