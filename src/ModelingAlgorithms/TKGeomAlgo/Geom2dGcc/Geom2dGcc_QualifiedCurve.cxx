

#include <Geom2dGcc_QualifiedCurve.hpp>

Geom2dGcc_QualifiedCurve::Geom2dGcc_QualifiedCurve(const Geom2dAdaptor_Curve& Curve,
                                                   const GccEnt_Position      Qualifier)
{
  TheQualified = Curve;
  TheQualifier = Qualifier;
}

Geom2dAdaptor_Curve Geom2dGcc_QualifiedCurve::Qualified() const
{
  return TheQualified;
}

GccEnt_Position Geom2dGcc_QualifiedCurve::Qualifier() const
{
  return TheQualifier;
}

bool Geom2dGcc_QualifiedCurve::IsUnqualified() const
{
  return TheQualifier == GccEnt_unqualified;
}

bool Geom2dGcc_QualifiedCurve::IsEnclosing() const
{
  return TheQualifier == GccEnt_enclosing;
}

bool Geom2dGcc_QualifiedCurve::IsEnclosed() const
{
  return TheQualifier == GccEnt_enclosed;
}

bool Geom2dGcc_QualifiedCurve::IsOutside() const
{
  return TheQualifier == GccEnt_outside;
}
