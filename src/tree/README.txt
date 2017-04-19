/Tree/
    /Exp/
        Const (int value)
        Name  (const temp::Label& label)
        Temp  (const temp::Temp& temp)
        Binop (Oper oper, Exp& left, Exp& right)
        Mem   (Exp& exp)
        Call  (Exp& func, std::vector<Exp*>& args)
        Eseq  (Stm& stm, Exp& exp)

    /Stm/
        Move  (Exp& dst, Exp& src)
        Sxp   (Exp& exp)
        Jump  (Exp& exp)
        CJump (Relop relop, Exp& left, Exp& right,
               Name& iftrue, Name& iffalse)
        Seq   (std::vector<Stm*>)
        Label (temp::Label& label)
