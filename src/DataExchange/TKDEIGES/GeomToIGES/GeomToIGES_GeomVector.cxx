

#include <Geom_Direction.hpp>
#include <Geom_Vector.hpp>
#include <Geom_VectorWithMagnitude.hpp>
#include <GeomToIGES_GeomVector.hpp>
#include <gp_XYZ.hpp>
#include <IGESGeom_CopiousData.hpp>
#include <IGESGeom_Direction.hpp>
#include <MoniTool_Macros.hpp>

GeomToIGES_GeomVector::GeomToIGES_GeomVector()

  = default;

GeomToIGES_GeomVector::GeomToIGES_GeomVector(const GeomToIGES_GeomEntity& GE)
    : GeomToIGES_GeomEntity(GE)
{
}

occ::handle<IGESGeom_Direction> GeomToIGES_GeomVector::TransferVector(
  const occ::handle<Geom_Vector>& start)
{
  occ::handle<IGESGeom_Direction> res;
  if (start.IsNull())
  {
    return res;
  }

  if (start->IsKind(STANDARD_TYPE(Geom_VectorWithMagnitude)))
  {
    DeclareAndCast(Geom_VectorWithMagnitude, VMagn, start);
    res = TransferVector(VMagn);
  }
  else if (start->IsKind(STANDARD_TYPE(Geom_Direction)))
  {
    DeclareAndCast(Geom_Direction, Direction, start);
    res = TransferVector(Direction);
  }

  return res;
}

occ::handle<IGESGeom_Direction> GeomToIGES_GeomVector::TransferVector(
  const occ::handle<Geom_VectorWithMagnitude>& start)
{
  occ::handle<IGESGeom_Direction> Dir = new IGESGeom_Direction;
  if (start.IsNull())
  {
    return Dir;
  }

  double X, Y, Z;
  start->Coord(X, Y, Z);
  double M = start->Magnitude();
  Dir->Init(gp_XYZ(X / (M * GetUnit()), Y / (M * GetUnit()), Z / (M * GetUnit())));
  return Dir;
}

occ::handle<IGESGeom_Direction> GeomToIGES_GeomVector::TransferVector(
  const occ::handle<Geom_Direction>& start)
{
  occ::handle<IGESGeom_Direction> Dir = new IGESGeom_Direction;
  if (start.IsNull())
  {
    return Dir;
  }

  double X, Y, Z;
  start->Coord(X, Y, Z);
  Dir->Init(gp_XYZ(X / GetUnit(), Y / GetUnit(), Z / GetUnit()));
  return Dir;
}
