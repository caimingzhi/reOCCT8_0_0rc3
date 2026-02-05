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

//=============================================================================
// Creation d' un cartesian_point de prostep a partir d' un point3d de gp
//=============================================================================
GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(const gp_Pnt& P, const double aFactor)
{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;
  //  occ::handle<NCollection_HArray1<double>> Acoord = new NCollection_HArray1<double>(1,3);
  double X, Y, Z;

  P.Coord(X, Y, Z);
  //  Acoord->SetValue(1,X);
  //  Acoord->SetValue(2,Y);
  //  Acoord->SetValue(3,Z);
  //  Pstep->SetCoordinates(Acoord);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  //  Pstep->SetName(name);
  Pstep->Init3D(name, X / aFactor, Y / aFactor, Z / aFactor);
  theCartesianPoint = Pstep;
  done              = true;
}

//=============================================================================
// Creation d' un cartesian_point de prostep a partir d' un point 2d de gp
//=============================================================================

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(const gp_Pnt2d& P,
                                                             const double    aFactor)
{
  (void)aFactor;
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;
  //  occ::handle<NCollection_HArray1<double>> Acoord = new NCollection_HArray1<double>(1,2);
  double X, Y;

  P.Coord(X, Y);
  //  Acoord->SetValue(1,X);
  //  Acoord->SetValue(2,Y);
  //  Pstep->SetCoordinates(Acoord);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  //  Pstep->SetName(name);
  Pstep->Init2D(name, X, Y);
  theCartesianPoint = Pstep;
  done              = true;
}

//=============================================================================
// Creation d' un cartesian_point de prostep a partir d' un point 3d de Geom
//=============================================================================

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(
  const occ::handle<Geom_CartesianPoint>& P,
  const double                            aFactor)

{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;
  //  occ::handle<NCollection_HArray1<double>> Acoord = new NCollection_HArray1<double>(1,3);
  double X, Y, Z;

  P->Coord(X, Y, Z);
  //  Acoord->SetValue(1,X);
  //  Acoord->SetValue(2,Y);
  //  Acoord->SetValue(3,Z);
  //  Pstep->SetCoordinates(Acoord);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  //  Pstep->SetName(name);
  Pstep->Init3D(name, X / aFactor, Y / aFactor, Z / aFactor);
  theCartesianPoint = Pstep;
  done              = true;
}

//=============================================================================
// Creation d' un cartesian_point de prostep a partir d' un point 2d de Geom2d
//=============================================================================

GeomToStep_MakeCartesianPoint::GeomToStep_MakeCartesianPoint(
  const occ::handle<Geom2d_CartesianPoint>& P)

{
  occ::handle<StepGeom_CartesianPoint> Pstep = new StepGeom_CartesianPoint;
  //  occ::handle<NCollection_HArray1<double>> Acoord = new NCollection_HArray1<double>(1,2);
  double X, Y;

  P->Coord(X, Y);
  //  Acoord->SetValue(1,X);
  //  Acoord->SetValue(2,Y);
  //  Pstep->SetCoordinates(Acoord);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  //  Pstep->SetName(name);
  Pstep->Init2D(name, X, Y);
  theCartesianPoint = Pstep;
  done              = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_CartesianPoint>& GeomToStep_MakeCartesianPoint::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeCartesianPoint::Value() - no result");
  return theCartesianPoint;
}
