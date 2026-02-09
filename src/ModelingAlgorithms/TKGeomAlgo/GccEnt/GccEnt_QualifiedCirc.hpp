#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Circ2d.hpp>
#include <GccEnt_Position.hpp>
#include <Standard_Boolean.hpp>

class GccEnt_QualifiedCirc
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccEnt_QualifiedCirc(const gp_Circ2d& Qualified, const GccEnt_Position Qualifier);

  Standard_EXPORT gp_Circ2d Qualified() const;

  Standard_EXPORT GccEnt_Position Qualifier() const;

  Standard_EXPORT bool IsUnqualified() const;

  Standard_EXPORT bool IsEnclosing() const;

  Standard_EXPORT bool IsEnclosed() const;

  Standard_EXPORT bool IsOutside() const;

private:
  gp_Circ2d       TheQualified;
  GccEnt_Position TheQualifier;
};
