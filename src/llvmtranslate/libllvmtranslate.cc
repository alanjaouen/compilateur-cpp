/**
 ** \file llvmtranslate/libllvmtranslate.hh
 ** \brief Public llvmtranslate module interface implementation.
 **/

#include <llvmtranslate/fwd.hh>
#include <llvmtranslate/libllvmtranslate.hh>
#include <llvmtranslate/translator.hh>
#include <llvmtranslate/escapes-collector.hh>
#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>
#include <common.hh> // program_name

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/SourceMgr.h> // llvm::SMDiagnostic
#include <llvm/IR/LLVMContext.h>
#include <llvm/AsmParser/Parser.h>

namespace llvmtranslate
{

  std::pair<std::unique_ptr<llvm::LLVMContext>, std::unique_ptr<llvm::Module>>
  translate(const ast::Ast& the_program)
  {
    auto ctx = std::make_unique<llvm::LLVMContext>();
    auto module = std::make_unique<llvm::Module>(program_name, *ctx);

    Translator translate{*module, collect_escapes(the_program)};
    translate(the_program);

    llvm::verifyModule(*module);

    return { std::move(ctx), std::move(module) };
  }

  std::unique_ptr<llvm::Module>
  runtime_get(llvm::LLVMContext& ctx)
  {
    llvm::SMDiagnostic diag;
    return llvm::parseAssemblyString(runtime_string(), diag, ctx);
  }

} // namespace llvmtranslate
