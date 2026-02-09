

#include <GccEnt_QualifiedLin.hpp>
#include <gp_Lin2d.hpp>

gp_Lin2d GccEnt_QualifiedLin::Qualified() const
{
  return TheQualified;
}

GccEnt_Position GccEnt_QualifiedLin::Qualifier() const
{
  return TheQualifier;
}

bool GccEnt_QualifiedLin::IsUnqualified() const
{
  return TheQualifier == GccEnt_unqualified;
}

bool GccEnt_QualifiedLin::IsEnclosed() const
{
  return (TheQualifier == GccEnt_enclosed);
}

bool GccEnt_QualifiedLin::IsOutside() const
{
  return TheQualifier == GccEnt_outside;
}

GccEnt_QualifiedLin::GccEnt_QualifiedLin(const gp_Lin2d& Qualified, const GccEnt_Position Qualifier)
{
  TheQualified = Qualified;
  TheQualifier = Qualifier;
}
