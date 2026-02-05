#include <GeomFill_Fixed.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_Fixed, GeomFill_TrihedronLaw)

GeomFill_Fixed::GeomFill_Fixed(const gp_Vec& Tangent, const gp_Vec& Normal)
{
  if (Tangent.IsParallel(Normal, 0.01))
    throw Standard_ConstructionError("GeomFill_Fixed : Two parallel vectors !");
  T = Tangent;
  T.Normalize();
  N = Normal;
  N.Normalize();
  B = T ^ N;
  B.Normalize();
}

occ::handle<GeomFill_TrihedronLaw> GeomFill_Fixed::Copy() const
{
  occ::handle<GeomFill_Fixed> copy = new (GeomFill_Fixed)(T, N);
  copy->SetCurve(myCurve);
  return copy;
}

bool GeomFill_Fixed::D0(const double, gp_Vec& Tangent, gp_Vec& Normal, gp_Vec& BiNormal)
{
  Tangent  = T;
  Normal   = N;
  BiNormal = B;

  return true;
}

bool GeomFill_Fixed::D1(const double,
                        gp_Vec& Tangent,
                        gp_Vec& DTangent,
                        gp_Vec& Normal,
                        gp_Vec& DNormal,
                        gp_Vec& BiNormal,
                        gp_Vec& DBiNormal)
{
  Tangent  = T;
  Normal   = N;
  BiNormal = B;

  gp_Vec V0(0, 0, 0);
  DTangent = DNormal = DBiNormal = V0;

  return true;
}

bool GeomFill_Fixed::D2(const double,
                        gp_Vec& Tangent,
                        gp_Vec& DTangent,
                        gp_Vec& D2Tangent,
                        gp_Vec& Normal,
                        gp_Vec& DNormal,
                        gp_Vec& D2Normal,
                        gp_Vec& BiNormal,
                        gp_Vec& DBiNormal,
                        gp_Vec& D2BiNormal)
{
  Tangent  = T;
  Normal   = N;
  BiNormal = B;

  gp_Vec V0(0, 0, 0);
  DTangent = D2Tangent = V0;
  DNormal = D2Normal = V0;
  DBiNormal = D2BiNormal = V0;

  return true;
}

int GeomFill_Fixed::NbIntervals(const GeomAbs_Shape) const
{
  return 1;
}

void GeomFill_Fixed::Intervals(NCollection_Array1<double>& theT, const GeomAbs_Shape) const
{
  theT(theT.Lower()) = -Precision::Infinite();
  theT(theT.Upper()) = Precision::Infinite();
}

void GeomFill_Fixed::GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal)
{
  ATangent  = T;
  ANormal   = N;
  ABiNormal = B;
}

bool GeomFill_Fixed::IsConstant() const
{
  return true;
}
