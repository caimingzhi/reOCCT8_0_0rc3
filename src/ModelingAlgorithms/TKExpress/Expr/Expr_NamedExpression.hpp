#pragma once


#include <Standard.hpp>

#include <TCollection_AsciiString.hpp>
#include <Expr_GeneralExpression.hpp>

//! Describe an expression used by its name (as constants
//! or variables). A single reference is made to a
//! NamedExpression in every Expression (i.e. a
//! NamedExpression is shared).
class Expr_NamedExpression : public Expr_GeneralExpression
{

public:
  Standard_EXPORT const TCollection_AsciiString& GetName() const;

  Standard_EXPORT void SetName(const TCollection_AsciiString& name);

  //! Tests if <me> can be shared by one or more expressions
  //! or must be copied. This method redefines to a True
  //! value the GeneralExpression method.
  Standard_EXPORT bool IsShareable() const override;

  //! Tests if <me> and <Other> define the same expression.
  //! This method does not include any simplification before
  //! testing.
  Standard_EXPORT bool IsIdentical(const occ::handle<Expr_GeneralExpression>& Other) const override;

  //! returns a string representing <me> in a readable way.
  Standard_EXPORT TCollection_AsciiString String() const override;

  DEFINE_STANDARD_RTTIEXT(Expr_NamedExpression, Expr_GeneralExpression)

private:
  TCollection_AsciiString myName;
};

