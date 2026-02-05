#include <GeomFill_Boundary.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(GeomFill_Boundary, Standard_Transient)

//=================================================================================================

GeomFill_Boundary::GeomFill_Boundary(const double Tol3d, const double Tolang)
    : myT3d(Tol3d),
      myTang(Tolang)
{
}

//=================================================================================================

bool GeomFill_Boundary::HasNormals() const
{
  return false;
}

//=================================================================================================

gp_Vec GeomFill_Boundary::Norm(const double) const
{
  throw Standard_Failure("GeomFill_Boundary::Norm : Undefined normals");
}

//=================================================================================================

void GeomFill_Boundary::D1Norm(const double, gp_Vec&, gp_Vec&) const
{
  throw Standard_Failure("GeomFill_Boundary::Norm : Undefined normals");
}

//=================================================================================================

void GeomFill_Boundary::Points(gp_Pnt& PFirst, gp_Pnt& PLast) const
{
  double f, l;
  Bounds(f, l);
  PFirst = Value(f);
  PLast  = Value(l);
}

//=================================================================================================

double GeomFill_Boundary::Tol3d() const
{
  return myT3d;
}

//=================================================================================================

void GeomFill_Boundary::Tol3d(const double Tol)
{
  myT3d = Tol;
}

//=================================================================================================

double GeomFill_Boundary::Tolang() const
{
  return myTang;
}

//=================================================================================================

void GeomFill_Boundary::Tolang(const double Tol)
{
  myTang = Tol;
}
