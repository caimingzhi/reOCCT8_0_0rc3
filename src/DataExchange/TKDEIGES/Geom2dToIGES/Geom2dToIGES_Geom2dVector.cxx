#include <Geom2d_Direction.hpp>
#include <Geom2d_Vector.hpp>
#include <Geom2d_VectorWithMagnitude.hpp>
#include <Geom2dToIGES_Geom2dVector.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_Direction.hpp>
#include <MoniTool_Macros.hpp>

Geom2dToIGES_Geom2dVector::Geom2dToIGES_Geom2dVector()

  = default;

Geom2dToIGES_Geom2dVector::Geom2dToIGES_Geom2dVector(const Geom2dToIGES_Geom2dEntity& G2dE)
    : Geom2dToIGES_Geom2dEntity(G2dE)
{
}

occ::handle<IGESGeom_Direction> Geom2dToIGES_Geom2dVector::Transfer2dVector(
  const occ::handle<Geom2d_Vector>& start)
{
  occ::handle<IGESGeom_Direction> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom2d_VectorWithMagnitude)))
  {
    DeclareAndCast(Geom2d_VectorWithMagnitude, VMagn, start);
    res = Transfer2dVector(VMagn);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom2d_Direction)))
  {
    DeclareAndCast(Geom2d_Direction, Direction, start);
    res = Transfer2dVector(Direction);
  }

  return res;
}

occ::handle<IGESGeom_Direction> Geom2dToIGES_Geom2dVector::Transfer2dVector(
  const occ::handle<Geom2d_VectorWithMagnitude>& start)
{
  occ::handle<IGESGeom_Direction> Dir = new IGESGeom_Direction;
  if (start.IsNull())
  {
    return Dir;
  }

  double X, Y;
  start->Coord(X, Y);
  double M = start->Magnitude();
  Dir->Init(gp_XYZ(X / M, Y / M, 0.));
  return Dir;
}

occ::handle<IGESGeom_Direction> Geom2dToIGES_Geom2dVector::Transfer2dVector(
  const occ::handle<Geom2d_Direction>& start)
{
  occ::handle<IGESGeom_Direction> Dir = new IGESGeom_Direction;
  if (start.IsNull())
  {
    return Dir;
  }

  double X, Y;
  start->Coord(X, Y);
  Dir->Init(gp_XYZ(X, Y, 0.));
  return Dir;
}
