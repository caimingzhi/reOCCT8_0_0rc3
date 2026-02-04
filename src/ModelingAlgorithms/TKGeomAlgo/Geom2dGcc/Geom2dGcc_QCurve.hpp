#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GccEnt_Position.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Standard_Boolean.hpp>

//! Creates a qualified 2d line.
class Geom2dGcc_QCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_QCurve(const Geom2dAdaptor_Curve& Curve,
                                   const GccEnt_Position      Qualifier);

  Standard_EXPORT Geom2dAdaptor_Curve Qualified() const;

  Standard_EXPORT GccEnt_Position Qualifier() const;

  //! Returns true if the solution is unqualified and false in the
  //! other cases.
  Standard_EXPORT bool IsUnqualified() const;

  //! Returns true if the solution is Enclosing the Curv and false in
  //! the other cases.
  Standard_EXPORT bool IsEnclosing() const;

  //! Returns true if the solution is Enclosed in the Curv and false in
  //! the other cases.
  Standard_EXPORT bool IsEnclosed() const;

  //! Returns true if the solution is Outside the Curv and false in
  //! the other cases.
  Standard_EXPORT bool IsOutside() const;

private:
  GccEnt_Position     TheQualifier;
  Geom2dAdaptor_Curve TheQualified;
};

