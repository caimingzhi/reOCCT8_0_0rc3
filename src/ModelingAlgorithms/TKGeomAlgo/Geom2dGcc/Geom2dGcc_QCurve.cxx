

#include <Geom2dGcc_QCurve.hpp>

Geom2dAdaptor_Curve Geom2dGcc_QCurve::Qualified() const
{
  return TheQualified;
}

GccEnt_Position Geom2dGcc_QCurve::Qualifier() const
{
  return TheQualifier;
}

bool Geom2dGcc_QCurve::IsUnqualified() const
{
  return TheQualifier == GccEnt_unqualified;
}

bool Geom2dGcc_QCurve::IsEnclosing() const
{
  return TheQualifier == GccEnt_enclosing;
}

bool Geom2dGcc_QCurve::IsEnclosed() const
{
  return TheQualifier == GccEnt_enclosed;
}

bool Geom2dGcc_QCurve::IsOutside() const
{
  return TheQualifier == GccEnt_outside;
}

Geom2dGcc_QCurve::Geom2dGcc_QCurve(const Geom2dAdaptor_Curve& Curve,
                                   const GccEnt_Position      Qualifier)
{
  TheQualified = Curve;
  TheQualifier = Qualifier;
}
