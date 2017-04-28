/** \file translate/translation.cc
 ** \brief Implementation for translate/translation.hh.
 **/

#include <ast/op-exp.hh>
#include <temp/temp.hh>
#include <temp/label.hh>
#include <translate/exp.hh>
#include <tree/fragment.hh>
#include <translate/access.hh>
#include <translate/level.hh>
#include <translate/translation.hh>

namespace translate
{

  /*--------.
  | /Var/.  |
  `--------*/

  rExp
  simple_var(const Access& access, const Level& use_level)
  {
    return new Ex(access.exp(use_level));
  }

  rExp
  field_var(rExp var_exp, int index)
  {
    tree::rExp address =
      index == 0
      ? var_exp->un_ex()
      : new tree::Binop(tree::Binop::add,
                        var_exp->un_ex(),
                        new tree::Const(frame::word_size * index));
    return new Ex(new tree::Mem(address));
  }

  rExp
  subscript_var(rExp var_exp, rExp index_exp)
  {// FIXMED by caradi_c
    tree::rExp address = new tree::Binop(tree::Binop::add,
                                         var_exp->un_ex(),
                                         new tree::Binop(tree::Binop::mul,
                                                         new tree::Const
                                                         (frame::word_size),
                                                         index_exp->un_ex()));
    return new Ex(new tree::Mem(address));
  }


  /*--------.
  | /Exp/.  |
  `--------*/

  rExp
  nil_exp()
  {
    return new Ex(new tree::Const(0));
  }

  rExp
  int_exp(int i)
  {
  // FIXED forest_b
    return new Ex(new tree::Const(i));
  }

  rExp
  string_exp(const std::string& s, tree::Fragment*& f)
  {
  // FIXED: alan et clyde
    auto label = temp::Label();
    f = new tree::DataFrag(label, s);
    return  new Ex(new tree::Name(label));
  }

  rExp
  record_exp(std::vector<rExp> fields)
  {
    // The record being built.
    tree::rTemp rec = new tree::Temp(temp::Temp());

    // Store the initialization.
    tree::rSeq init = new tree::Seq;

    // First allocate the memory.
    int record_size = fields.size() * frame::word_size;
    rExp malloc_call = call_exp("malloc", int_exp(record_size));
    init->emplace_back(new tree::Move(rec, malloc_call->un_ex()));
\
  // FIXME: Some code was deleted here (Issue a move for each field of the record).

    return new Ex(new tree::Eseq(init, rec));
  }

  rExp
  static_link(const Level* decl, const Level* use)
  {
    assertion(decl);
    assertion(use);
    return new Ex(decl->parent_get()->fp(*use));
  }

  rExp
  call_exp(const temp::Label& label, std::vector<rExp> args)
  {// FIXMED by caradi_c
    std::vector<tree::rExp> res;
    for (auto i : args)
      res.emplace_back(i->un_ex());
    tree::Call* cres = new tree::Call(new tree::Name(label), res);
    return new Ex(cres);
  }

  rExp
  call_exp(const std::string& label, rExp arg1, rExp arg2)
  {
    std::vector<rExp> args = { arg1 };
    if (arg2)
      args.emplace_back(arg2);
    return call_exp(label, args);
  }


  // Operations on words, i.e., arithmetics, ordered comparison of
  // Integer, and object equality for Integers, Arrays and Records.
  rExp
  op_exp(const ast::OpExp::Oper oper, rExp left, rExp right)
  {// FIXMED by caradi_c
    switch (oper)
      {
      case ast::OpExp::add:
        return new Ex(new tree::Binop(tree::Binop::add, left->un_ex(), right->un_ex()));
      case ast::OpExp::sub:
        return new Ex(new tree::Binop(tree::Binop::sub, left->un_ex(), right->un_ex()));
      case ast::OpExp::mul:
        return new Ex(new tree::Binop(tree::Binop::mul, left->un_ex(), right->un_ex()));
      case ast::OpExp::div:
        return new Ex(new tree::Binop(tree::Binop::div, left->un_ex(), right->un_ex()));
      case ast::OpExp::eq:
        return new Cx(tree::Cjump::eq, left->un_ex(), right->un_ex());
      case ast::OpExp::ne:
        return new Cx(tree::Cjump::ne, left->un_ex(), right->un_ex());
      case ast::OpExp::lt:
        return new Cx(tree::Cjump::lt, left->un_ex(), right->un_ex());
      case ast::OpExp::le:
        return new Cx(tree::Cjump::le, left->un_ex(), right->un_ex());
      case ast::OpExp::gt:
        return new Cx(tree::Cjump::gt, left->un_ex(), right->un_ex());
      case ast::OpExp::ge:
        return new Cx(tree::Cjump::ge, left->un_ex(), right->un_ex());
      default:
        unreachable();
      }
  }

  // Avoid useless structures.
  rExp
  seq_exp(std::vector<rExp>& exps)
  {
    switch (exps.size())
      {
      case 0:
        return new Nx(new tree::Sxp(new tree::Const(0)));
      case 1:
        return exps.back();
      default:
        tree::rSeq seq = new tree::Seq;
        for (const rExp& exp : exps)
          seq->emplace_back(exp->un_nx());
        return new Nx(seq);
      }
  }


  // Try to produce simple code for simple cases.
  rExp
  eseq_exp(std::vector<rExp>& exps)
  {// FIXED by caradi_c
    if (exps.size() != 0)
      {
        std::vector<tree::rTree> eres;
        for (auto i : exps)
          eres.emplace_back(i->un_nx());
        rExp res = exps.back();
        tree::Eseq* e = new tree::Eseq(new tree::Seq(eres), res->un_ex());
        return new Ex(e);
      }
  }

  rExp
  assign_exp(rExp dst, rExp src)
  {// FIXMED by caradi_c
    tree::rMove a = new tree::Move(dst->un_ex(), src->un_ex());
    return new Nx(a);
  }

  rExp
  if_exp(rExp test, rExp then_clause, rExp else_clause)
  {
    return new Ix(test, then_clause, else_clause);
  }



  rExp
  while_exp(rExp test, rExp body, const temp::Label& ldone)
  {
    temp::Label start;
    tree::Seq* while_stm = new tree::Seq
      {
        new tree::Label(start),
        body->un_nx(),
        Cx(tree::Cjump::ne, test->un_ex(), new tree::Const(0)).un_cx(ldone, start)
      };
    return Ex(*while_stm);
  }

  // FIXME: Some code was deleted here (for_exp -- "for" loop translation).

  rExp
  break_exp(const temp::Label& loop_end)
  {
    return new Nx(new tree::Jump(new tree::Name(loop_end)));
  }

  rExp
  array_exp(rExp array_size, rExp init_val)
  {
    // Call the runtime function which mallocs and initializes the
    // array.  This function returns a pointer to its result.
    rExp content = call_exp("init_array", array_size, init_val);

    temp::Temp array;
    return new Ex(new tree::Eseq(new tree::Move(new tree::Temp(array),
                                 content->un_ex()),
                                 new tree::Temp(array)));
  }



  /*--------.
  | /Dec/.  |
  `--------*/

  tree::ProcFrag*
  procedure_dec(const temp::Label& label, const misc::symbol& name,
                rExp body, frame::Frame* frame)
  {
    return new tree::ProcFrag(label, name, body->un_nx(), frame);
  }

  tree::ProcFrag*
  function_dec(const temp::Label& label, const misc::symbol& name,
               rExp value, frame::Frame* frame)
  {
    temp::Temp rv("rv");
    rExp body = new Nx(new tree::Move(new tree::Temp(rv),
                                      value->un_ex()));
    return procedure_dec(label, name, body, frame);
  }

} // namespace translate
