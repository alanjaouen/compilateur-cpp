* README

Tiger Abstract Syntax Tree nodes with their principal members.
Incomplete classes are tagged with a `*'.

/Ast/               (Location location)
  /Dec/             (symbol name)
    FunctionDec     (VarDecs formals, NameTy result, Exp body)
      MethodDec     ()
    TypeDec         (Ty ty)
    VarDec          (NameTy type_name, Exp init)

  /Exp/             ()
    /Var/           ()
      CastVar       (Var var, Ty ty)
      FieldVar      (Var lvalue, symbol name)
      SimpleVar     (symbol name)
      SubscriptVar  (Var var, Exp index)

    ArrayExp        (NameTy type, Exp l_exp, Exp r_exp)
    AssignExp       (Var lvalue, Exp exp)
    BreakExp        ()
    CallExp         (symbol name, exps_type seq)
      MethodCallExp (Var lvalue)
    CastExp         (Exp exp, Ty ty)
    ForExp          (VarDec vardec, Exp hi, Exp body)
    IfExp           (Exp test, Exp Bthen, Exp Belse)
    IntExp          (int value)
    LetExp          (DecsList decs, Exp vect)
    NilExp          ()
    ObjectExp       (Exp exp, NameTy type)
    OpExp           (Exp left, Oper oper, Exp right)
    RecordExp       (NameTy id, fieldsinits_type vect)
    SeqExp          (exps_type seq)
    StringExp       (std::string str)
    WhileExp        (Exp test, Exp body)

  /Ty/              ()
    ArrayTy         (NameTy base_type)
    ClassTy         (NameTy super, DecsList decs)
    NameTy          (symbol name)
    RecordTy        (fields_type vect)

  DecsList          (decs_type decs)

  Field             (symbol name, NameTy type_name)

  FieldInit         (symbol name, Exp init)


Some of these classes also inherit from other classes.

/Escapable/
  VarDec            (NameTy type_name, Exp init)

/Typable/
  /Dec/             (symbol name)
  /Exp/             ()
  /Ty/              ()

/TypeConstructor/
  /Ty/              ()
  FunctionDec       (VarDecs formals, NameTy result, Exp body)
  NilExp            ()
  TypeDec           (Ty ty)

