#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GccEnt_Position.hpp>
#include <gp_Lin2d.hpp>
#include <Standard_Boolean.hpp>

class GccEnt_QualifiedLin
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GccEnt_QualifiedLin(const gp_Lin2d& Qualified, const GccEnt_Position Qualifier);

  Standard_EXPORT gp_Lin2d Qualified() const;

  Standard_EXPORT GccEnt_Position Qualifier() const;

  Standard_EXPORT bool IsUnqualified() const;

  Standard_EXPORT bool IsEnclosed() const;

  Standard_EXPORT bool IsOutside() const;

private:
  GccEnt_Position TheQualifier;
  gp_Lin2d        TheQualified;
};
