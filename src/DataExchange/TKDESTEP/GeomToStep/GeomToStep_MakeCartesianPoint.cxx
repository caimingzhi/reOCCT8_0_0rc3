#include <Geom2d_CartesianPoint.hpp>
#include <Geom_CartesianPoint.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(const gp_Pnt& P, const double aFactor)
{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;

  double X, Y, Z;

  P.Coord(X, Y, Z);

  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");

  Pstep->Init3D(name, X / aFactor, Y / aFactor, Z / aFactor);
  theCartesianPoint = Pstep;
  done              = true;
}

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(const gp_Pnt2d& P,
                                                             const double    aFactor)
{
  (void)aFactor;
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;

  double X, Y;

  P.Coord(X, Y);

  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");

  Pstep->Init2D(name, X, Y);
  theCartesianPoint = Pstep;
  done              = true;
}

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(
  const occ::handle<Geom_CartesianPoint>& P,
  const double                            aFactor)

{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;

  double X, Y, Z;

  P->Coord(X, Y, Z);

  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");

  Pstep->Init3D(name, X / aFactor, Y / aFactor, Z / aFactor);
  theCartesianPoint = Pstep;
  done              = true;
}

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(
  const occ::handle<Geom2d_CartesianPoint>& P)

{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;

  double X, Y;

  P->Coord(X, Y);

  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");

  Pstep->Init2D(name, X, Y);
  theCartesianPoint = Pstep;
  done              = true;
}

const occ::handle<StepGeom_CartesianPoint>& GeomToStep_MakeCartesianPoint::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeCartesianPoint::Value() - no result");
  return theCartesianPoint;
}
