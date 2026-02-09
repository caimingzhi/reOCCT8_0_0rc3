#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
class Expr_NamedUnknown;
class TCollection_AsciiString;

class Expr_GeneralFunction : public Standard_Transient
{

public:
  Standard_EXPORT virtual int NbOfVariables() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_NamedUnknown> Variable(const int index) const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralFunction> Copy() const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var) const = 0;

  Standard_EXPORT virtual occ::handle<Expr_GeneralFunction> Derivative(
    const occ::handle<Expr_NamedUnknown>& var,
    const int                             deg) const = 0;

  Standard_EXPORT virtual double Evaluate(
    const NCollection_Array1<occ::handle<Expr_NamedUnknown>>& vars,
    const NCollection_Array1<double>&                         vals) const = 0;

  Standard_EXPORT virtual bool IsIdentical(const occ::handle<Expr_GeneralFunction>& func) const = 0;

  Standard_EXPORT virtual bool IsLinearOnVariable(const int index) const = 0;

  Standard_EXPORT virtual TCollection_AsciiString GetStringName() const = 0;

  DEFINE_STANDARD_RTTIEXT(Expr_GeneralFunction, Standard_Transient)
};
