

#include <GccEnt_QualifiedCirc.hpp>
#include <gp_Circ2d.hpp>

gp_Circ2d GccEnt_QualifiedCirc::Qualified() const
{
  return TheQualified;
}

GccEnt_Position GccEnt_QualifiedCirc::Qualifier() const
{
  return TheQualifier;
}

bool GccEnt_QualifiedCirc::IsUnqualified() const
{
  return TheQualifier == GccEnt_unqualified;
}

bool GccEnt_QualifiedCirc::IsEnclosing() const
{
  return TheQualifier == GccEnt_enclosing;
}

bool GccEnt_QualifiedCirc::IsEnclosed() const
{
  return TheQualifier == GccEnt_enclosed;
}

bool GccEnt_QualifiedCirc::IsOutside() const
{
  return TheQualifier == GccEnt_outside;
}

GccEnt_QualifiedCirc::GccEnt_QualifiedCirc(const gp_Circ2d&      theQualified,
                                           const GccEnt_Position theQualifier)
    : TheQualified(theQualified),
      TheQualifier(theQualifier)
{
}
