/**
 ** \file llvmtranslate/translator.cc
 ** \brief Implementation of llvmtranslate::Translator
 */

#include <ast/all.hh>
#include <llvmtranslate/translator.hh>

#include <llvm/IR/TypeBuilder.h>
#include <llvm/ADT/Triple.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/Host.h> // llvm::sys
#include <llvm/IR/Verifier.h> // llvm::verifyFunction
#include <llvm/Config/llvm-config.h> // LLVM_VERSION_*

namespace llvmtranslate
{

  using namespace std::string_literals;

  namespace
  {

    // Shorthands for integer type and pointer to integer type.
    inline
    llvm::IntegerType*
    i32_t(llvm::LLVMContext& ctx)
    {
      return llvm::TypeBuilder<int32_t, false>::get(ctx);
    }

    inline
    llvm::PointerType*
    i32p_t(llvm::LLVMContext& ctx)
    {
      return llvm::TypeBuilder<int32_t*, false>::get(ctx);
    }

    llvm::AllocaInst*
    create_alloca(llvm::Function* ll_function, llvm::Type* ll_type,
                  const std::string& name)
    {
      // Create an IRBuilder starting at the beginning of the current entry
      // block. LLVM treats allocas as local variables only if they occur at the
      // beginning of a function.
      llvm::IRBuilder<> tmp(&ll_function->getEntryBlock(),
                            ll_function->getEntryBlock().begin());
      return tmp.CreateAlloca(ll_type, nullptr, name);
    }

    // Set default attributes to the functions
    void
    set_default_attributes(llvm::Function& the_function,
                           const ast::FunctionDec& e)
    {
      the_function.addFnAttr(llvm::Attribute::NoUnwind); // No exceptions in TC
      if (!e.body_get()) // Inline primitives
        the_function.addFnAttr(llvm::Attribute::InlineHint);
    }

  }

  Translator::Translator(llvm::Module& module, escaped_map_type&& escaped)
    : module_{module}
    , ctx_{module_.getContext()}
    , builder_{ctx_}
    , escaped_{std::move(escaped)}
    , type_visitor_{ctx_}
  {
    // The current process triple.
    auto process_triple = llvm::Triple(llvm::sys::getProcessTriple());
    // Set the 32-bit version of the triple.
    module_.setTargetTriple(process_triple.get32BitArchVariant().str());
  }

  void
  Translator::operator()(const ast::Ast& e)
  {
    translate(e);
    value_ = nullptr;
  }

  llvm::Value*
  Translator::translate(const ast::Ast& node)
  {
    node.accept(*this);
    return value_;
  }

  llvm::Value*
  Translator::access_var(const ast::Var& e)
  {
    if (auto var_ast = dynamic_cast<const ast::SimpleVar*>(&e))
      {
  // FIXME: Some code was deleted here.
      }
    else if (auto arr_ast = dynamic_cast<const ast::SubscriptVar*>(&e))
      {
  // FIXME: Some code was deleted here.
      }
    else if (auto field_ast = dynamic_cast<const ast::FieldVar*>(&e))
      {
        const ast::Var* var = nullptr;
  // FIXME: Some code was deleted here.
        auto var_val = translate(*var);
        const type::Record* record_type = nullptr;
  // FIXME: Some code was deleted here.
        misc::symbol field_name;
  // FIXME: Some code was deleted here.
        int index = -1;
  // FIXME: Some code was deleted here (Get the index of the field).

        // The GEP instruction provides us with safe pointer arithmetics,
        // usually used with records or arrays.
        llvm::Type* record_ltype = nullptr;
  // FIXME: Some code was deleted here (Get a pointer to this structure).
        return builder_.CreateStructGEP(record_ltype, var_val, index,
                                        "fieldptr_"s + field_name.get());
      }
    else
      unreachable();
  }

  llvm::Value*
  Translator::init_array(llvm::Value* count_val, llvm::Value* init_val)
  {
    // Cast everything so that it is conform to the signature of init_array
    // int *init_array(int, int)

    // We need to separate the pointers and the ints.
    // LLVM requires a ptrtoint instruction for pointers
    // and a bitcast for others.
    auto init_val_cast = init_val->getType()->isPointerTy()
          ? builder_.CreatePtrToInt(init_val, i32_t(ctx_), "init_array_ptrtoint")
          : builder_.CreateBitCast(init_val, i32_t(ctx_), "init_array_bitcast");

    // Create the init_array function:
    // First, the arguments (int*, int, int)
    std::vector<llvm::Type*> arg_type{i32_t(ctx_), init_val_cast->getType()};

    // Then, create the FunctionType.
    auto init_array_ltype = llvm::FunctionType::get(i32p_t(ctx_), arg_type, false);

    // Get the llvm::Function from the module related to the name and type
    auto init_array_function = module_.getOrInsertFunction("tc_init_array",
                                                           init_array_ltype);

    // Prepare the arguments.
    std::vector<llvm::Value*> arg_vals{count_val, init_val_cast};

    // Create the call.
    auto init_array_call = builder_.CreateCall(init_array_function, arg_vals,
                                               "init_array_call");

    // Cast the result of the call in the desired type.
    return builder_.CreateBitCast(init_array_call,
                                  init_val->getType()->getPointerTo(),
                                  "init_array_call_cast");
  }

  llvm::Type*
  Translator::llvm_type(const type::Type& type)
  {
    type_visitor_(type);
    return type_visitor_.llvm_type_get();
  }

  llvm::FunctionType*
  Translator::llvm_function_type(const type::Function& function_type)
  {
    // Prepare the arguments
    std::vector<llvm::Type*> args_types;
    // First, if there are any escaped vars, create ptr arguments for it
    // (Lambda lifting)

    // c++1z - if (init; condition)
    /* if (auto escapes_it = escaped_.find(&function_type);
     *     escapes_it != std::end(escaped_))
     * { ... }
     */
    auto escapes_it = escaped_.find(&function_type);
    if (escapes_it != std::end(escaped_))
      {
        auto& escapes = escapes_it->second;
        for (const auto dec : escapes)
          {
            llvm::Type* var_ltype = nullptr;
  // FIXME: Some code was deleted here (Get the llvm type of the VarDec).
            args_types.emplace_back(llvm::PointerType::getUnqual(var_ltype));
          }
      }

    // Then, the actual arguments
    for (const auto field : function_type.formals_get())
      args_types.emplace_back(llvm_type(field.type_get()));

    auto result_ltype = llvm_type(function_type.result_get());

    return llvm::FunctionType::get(result_ltype, args_types, false);
  }

  void
  Translator::operator()(const ast::SimpleVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::FieldVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::SubscriptVar& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::CastVar& e)
  {
    auto var_val = translate(e.var_get());
    llvm::Type* ltype = nullptr;
  // FIXME: Some code was deleted here (Destination llvm type).
    value_ = builder_.CreateBitCast(var_val, ltype, "castvar");
  }

  void
  Translator::operator()(const ast::NilExp& e)
  {
  // FIXME: Some code was deleted here (Get the record_type of the Nil type, and create a null pointer).
  }

  void
  Translator::operator()(const ast::IntExp& e)
  {
  // FIXME: Some code was deleted here (Integers in Tiger are all 32bit signed).
  }

  void
  Translator::operator()(const ast::StringExp& e)
  {
  // FIXME: Some code was deleted here (Strings are translated as `i8*` values, like C's `char*`).
  }

  void
  Translator::operator()(const ast::RecordExp& e)
  {
    // Get the record type
    const type::Record* record_type = nullptr;
  // FIXME: Some code was deleted here.

    // Get a pointer to the structure represented by the record type
    // then get the structure from this pointer using getElementType()
    auto struct_ltype = llvm_type(*record_type)->getPointerElementType();

    // The current basic block
    auto current_bb = builder_.GetInsertBlock();

    // The size of the structure and cast it to int
    auto sizeof_val = llvm::ConstantExpr::getSizeOf(struct_ltype);
    sizeof_val = llvm::ConstantExpr::getTruncOrBitCast(sizeof_val, i32_t(ctx_));

    // Generate the instruction calling Malloc
    auto malloc_val =
      llvm::CallInst::CreateMalloc(current_bb, i32_t(ctx_), struct_ltype,
                                   sizeof_val, nullptr, nullptr, "malloccall");

    // Add it using the IR builder
    builder_.Insert(malloc_val, "malloccall");

    // Init the fields
  // FIXME: Some code was deleted here.

    value_ = malloc_val;
  }

  void
  Translator::operator()(const ast::OpExp& e)
  {
  // FIXME: Some code was deleted here.
    // The comparison instructions returns an i1, and we need an i32, since everything
    // is an i32 in Tiger. Use a zero-extension to avoid this.
    value_ = builder_.CreateZExtOrTrunc(value_, i32_t(ctx_), "op_zext");
  }

  void
  Translator::operator()(const ast::SeqExp& e)
  {
    // An empty SeqExp is an empty expression, so we should return an int
    // containing 0, since its type is void.
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::AssignExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::IfExp& e)
  {
  // FIXME: Some code was deleted here (IfExps are handled in a similar way to Kaleidoscope (see LangImpl5.html)).
  }

  void
  Translator::operator()(const ast::WhileExp& e)
  {
    // Bb containing the test and the branching
    auto test_bb = llvm::BasicBlock::Create(ctx_, "test", current_function_);
    auto body_bb = llvm::BasicBlock::Create(ctx_, "body", current_function_);
    auto after_bb = llvm::BasicBlock::Create(ctx_, "afterloop", current_function_);

    // Save the after block for breaks
    loop_end_[&e] = after_bb;

    // Explicitly fall through from the current block
    builder_.CreateBr(test_bb);

    // Start inside the test BasicBlock
    builder_.SetInsertPoint(test_bb);

    auto cond_val = translate(e.test_get());
    auto zero_val = llvm::ConstantInt::getSigned(cond_val->getType(), 0);
    auto cmp_val = builder_.CreateICmpNE(cond_val, zero_val, "loopcond");

    // Create the branching
    builder_.CreateCondBr(cmp_val, body_bb, after_bb);

    // Translate the body inside the body BasicBlock
    builder_.SetInsertPoint(body_bb);
    // Don't store the return value, is should be void.
    translate(e.body_get());

    // Go back to the Test BasicBlock
    builder_.CreateBr(test_bb);

    // Continue after the loop BasicBlock
    builder_.SetInsertPoint(after_bb);
  }

  void
  Translator::operator()(const ast::BreakExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::ArrayExp& e)
  {
    // Translate the number of elements,
    // fill the array with the default value, then
    // return the pointer to the allocated zone.
  // FIXME: Some code was deleted here (Use `init_array`).
  }

  void
  Translator::operator()(const ast::CastExp& e)
  {
    auto exp_val = translate(e.exp_get());
    llvm::Type* ltype = nullptr;
  // FIXME: Some code was deleted here (Destination llvm type).
    value_ = builder_.CreateBitCast(exp_val, ltype, "cast_exp");
  }

  void
  Translator::operator()(const ast::FunctionDecs& e)
  {
    for (const auto& i : e.decs_get())
      visit_function_dec_header(*i);

    for (const auto& i : e.decs_get())
      // There is nothing to translate for primitives.
      if (i->body_get())
        visit_function_dec_body(*i);
  }

  void
  Translator::visit_function_dec_header(const ast::FunctionDec& e)
  {
    bool is_main = e.name_get() == "_main";
    bool is_primitive = e.body_get() == nullptr;

    // Rename "_main" to "tc_main"
    // FIXME : Quick and dirty
    auto name = is_main ? "tc_main" : e.name_get();

    // Prefix all the primitives with "tc_"
    // FIXME : Quick and dirty
    if (is_primitive)
      name = "tc_" + name.get();

    const type::Type* node_type = nullptr;
  // FIXME: Some code was deleted here.
    auto& function_type = static_cast<const type::Function&>(*node_type);
    auto function_ltype = llvm_function_type(function_type);

    // Main and primitives have External linkage.
    // Other Tiger functions are treated as "static" functions in C.
    auto linkage = is_main || is_primitive
                   ? llvm::Function::ExternalLinkage
                   : llvm::Function::InternalLinkage;

    auto the_function = llvm::Function::Create(function_ltype, linkage,
                                               name.get(), &module_);
    set_default_attributes(*the_function, e);

    auto& escaped = escaped_[&function_type];

    // Name each argument of the function
    for (auto arg_it = the_function->arg_begin();
         arg_it != the_function->arg_end(); ++arg_it)
      {
        auto i = std::distance(the_function->arg_begin(), arg_it);
        auto var = escaped.size() && static_cast<size_t>(i) < escaped.size()
                   ? *std::next(escaped_[&function_type].begin(), i)
                   : e.formals_get().decs_get()[i - escaped.size()];

        arg_it->setName(var->name_get().get());
      }
  }

  void
  Translator::visit_function_dec_body(const ast::FunctionDec& e)
  {
    bool is_main = e.name_get() == "_main";

    auto the_function = module_.getFunction(is_main
                                            ? "tc_main"
                                            : e.name_get().get());

    // Save the old function in case a nested function occurs.
    auto old_insert_point = builder_.saveIP();
    auto old_function = current_function_;
    current_function_ = the_function;

    // Create a new basic block to start the function.
    auto bb = llvm::BasicBlock::Create(ctx_, "entry_"s + e.name_get().get(),
                                       the_function);
    builder_.SetInsertPoint(bb);

    const type::Type* node_type = nullptr;
  // FIXME: Some code was deleted here.
    auto& function_type = static_cast<const type::Function&>(*node_type);
    auto& escaped = escaped_[&function_type];
    auto& decs = e.formals_get().decs_get();

    auto arg_it = the_function->arg_begin();

    for (const auto var : escaped)
      {
        locals_[current_function_][var] = &*arg_it;
        ++arg_it;
      }

  // FIXME: Some code was deleted here (Create alloca instructions for each variable).

  // FIXME: Some code was deleted here (Create a return instruction).

    // Validate the generated code, checking for consistency.
    llvm::verifyFunction(*the_function);

    // Restore the context of the old function.
    current_function_ = old_function;
    builder_.restoreIP(old_insert_point);
  }

  void
  Translator::operator()(const ast::CallExp& e)
  {
    // Look up the name in the global module table.
    // If it's a primitive, rename the call to tc_name.
    //
    // Then, add the escaped variables and the rest of the arguments to the
    // list of arguments, and return the correct value.
  // FIXME: Some code was deleted here.
  }

  void
  Translator::operator()(const ast::VarDec& e)
  {
    // Void var types are actually Ints represented by a 0
  // FIXME: Some code was deleted here.
  }
} // namespace llvmtranslate
