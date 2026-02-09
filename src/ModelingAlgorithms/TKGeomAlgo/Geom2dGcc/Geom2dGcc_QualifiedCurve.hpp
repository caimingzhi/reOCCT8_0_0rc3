#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GccEnt_Position.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Standard_Boolean.hpp>

class Geom2dGcc_QualifiedCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dGcc_QualifiedCurve(const Geom2dAdaptor_Curve& Curve,
                                           const GccEnt_Position      Qualifier);

  Standard_EXPORT Geom2dAdaptor_Curve Qualified() const;

  Standard_EXPORT GccEnt_Position Qualifier() const;

  Standard_EXPORT bool IsUnqualified() const;

  Standard_EXPORT bool IsEnclosing() const;

  Standard_EXPORT bool IsEnclosed() const;

  Standard_EXPORT bool IsOutside() const;

private:
  GccEnt_Position     TheQualifier;
  Geom2dAdaptor_Curve TheQualified;
};
