* README

Hierarchy of types for the Tiger language, with (most of) their
interfaces.


ostream& operator<< (ostream& ostr, const Type& t)
bool operator== (const Type& lhs, const Type& rhs);
bool operator!= (const Type& lhs, const Type& rhs);

/Type/
    virtual ~Type() {}
    virtual const Type& actual () const;
    virtual bool compatible_with (const Type& other) const;
    virtual void accept(ConstVisitor& v) const;
    virtual void accept(Visitor& v);

  Nil
    const Type* record_type_get() const;

  Void

  Int

  String

  Named (const misc::symbol& name, const Type* type)
    void type_set (const Type *type)
    void type_set (const Type *type) const
    const bool sound () const

  Array (const Type& type)
    const Type& type_get () const

  Record (const list<Field*> &fields)
    const list<Field*>& fields_get () const
    const Type* field_type (const misc::symbol &key) const
    void field_add (Field *field)
    void field_add (const misc::symbol& name, const Type& type)

  Class (const Class* super = nullptr)
    const Type* attr_type (const misc::symbol& key) const
    const Method* meth_type (const misc::symbol& key) const
    const attrs_type& attrs_get () const
    const meths_type& meths_get () const
    void attr_add (const Attribute& attr)
    void attr_add (const misc::symbol& name, const Type& type, const VarDec* def)
    const Class* super_get () const
    void super_set (const Class* type)
    bool sound () const
    static const Class& object_instance ()

  Function (const Record* formals, const Type& result)

    Method (const misc::symbol& name, const Record* formals,
            const Type& result, MethodDec* def)
      misc::symbol name_get () const
      const MethodDec* def_get () const
      MethodDec* def_get ()
      void name_set (const misc::symbol& name)
      void def_set (MethodDec* def)

Field (const misc::symbol& name, const Type& type)
    const misc::symbol& name_get() const
    void name_set(const misc::symbol&)
    const NameTy& type_name_get() const
    NameTy& type_name_get()

Attribute (const ast::VarDec* def)
    misc::symbol name_get() const
    const Type& type_get() const
    const ast::VarDec* def_get() const
    void def_set(const ast::VarDec* def)
