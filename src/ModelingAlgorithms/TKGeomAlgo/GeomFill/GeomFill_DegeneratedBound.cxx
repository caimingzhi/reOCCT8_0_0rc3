#include <GeomFill_DegeneratedBound.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_DegeneratedBound, GeomFill_Boundary)

//=================================================================================================

GeomFill_DegeneratedBound::GeomFill_DegeneratedBound(const gp_Pnt& Point,
                                                     const double  First,
                                                     const double  Last,
                                                     const double  Tol3d,
                                                     const double  Tolang)
    : GeomFill_Boundary(Tol3d, Tolang),
      myPoint(Point),
      myFirst(First),
      myLast(Last)
{
}

//=================================================================================================

// gp_Pnt GeomFill_DegeneratedBound::Value(const double U) const
gp_Pnt GeomFill_DegeneratedBound::Value(const double) const
{
  return myPoint;
}

//=================================================================================================

// void GeomFill_DegeneratedBound::D1(const double U,
void GeomFill_DegeneratedBound::D1(const double, gp_Pnt& P, gp_Vec& V) const
{
  P = myPoint;
  V.SetCoord(0., 0., 0.);
}

//=================================================================================================

void GeomFill_DegeneratedBound::Reparametrize(const double First,
                                              const double Last,
                                              const bool,
                                              const bool,
                                              const double,
                                              const double,
                                              const bool)
{
  myFirst = First;
  myLast  = Last;
}

//=================================================================================================

void GeomFill_DegeneratedBound::Bounds(double& First, double& Last) const
{
  First = myFirst;
  Last  = myLast;
}

//=================================================================================================

bool GeomFill_DegeneratedBound::IsDegenerated() const
{
  return true;
}
