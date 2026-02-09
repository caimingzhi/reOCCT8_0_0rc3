

#include <Geom2dGcc.hpp>

#include <Geom2dGcc_QualifiedCurve.hpp>

Geom2dGcc_QualifiedCurve Geom2dGcc::Unqualified(const Geom2dAdaptor_Curve& Curve)
{
  return Geom2dGcc_QualifiedCurve(Curve, GccEnt_unqualified);
}

Geom2dGcc_QualifiedCurve Geom2dGcc::Enclosing(const Geom2dAdaptor_Curve& Curve)
{
  return Geom2dGcc_QualifiedCurve(Curve, GccEnt_enclosing);
}

Geom2dGcc_QualifiedCurve Geom2dGcc::Enclosed(const Geom2dAdaptor_Curve& Curve)
{
  return Geom2dGcc_QualifiedCurve(Curve, GccEnt_enclosed);
}

Geom2dGcc_QualifiedCurve Geom2dGcc::Outside(const Geom2dAdaptor_Curve& Curve)
{
  return Geom2dGcc_QualifiedCurve(Curve, GccEnt_outside);
}
