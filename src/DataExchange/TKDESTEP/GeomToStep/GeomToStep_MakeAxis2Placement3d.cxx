#include <Geom_Axis2Placement.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <gp_Ax3.hpp>
#include <gp_Trsf.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

static occ::handle<StepGeom_Axis2Placement3d> MakeAxis2Placement3d(const gp_Pnt& O,
                                                                   const gp_Dir& D,
                                                                   const gp_Dir& X,
                                                                   const char*   nom,
                                                                   double        aFactor)
{
  occ::handle<StepGeom_Axis2Placement3d> Axe;
  occ::handle<StepGeom_CartesianPoint>   P;
  occ::handle<StepGeom_Direction>        D1, D2;

  GeomToStep_MakeCartesianPoint MkPoint(O, aFactor);
  GeomToStep_MakeDirection      MkDir1(D);
  GeomToStep_MakeDirection      MkDir2(X);

  P  = MkPoint.Value();
  D1 = MkDir1.Value();
  D2 = MkDir2.Value();

  Axe = new StepGeom_Axis2Placement3d;
  Axe->SetLocation(P);
  Axe->SetAxis(D1);
  Axe->SetRefDirection(D2);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString(nom);
  Axe->SetName(name);
  return Axe;
}

GeomToStep_MakeAxis2Placement3d::GeomToStep_MakeAxis2Placement3d(
  const StepData_Factors& theLocalFactors)
{
  gp_Ax2 A(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));

  occ::handle<StepGeom_Axis2Placement3d> Axe = MakeAxis2Placement3d(A.Location(),
                                                                    A.Direction(),
                                                                    A.XDirection(),
                                                                    "",
                                                                    theLocalFactors.LengthFactor());
  theAxis2Placement3d                        = Axe;
  done                                       = true;
}

GeomToStep_MakeAxis2Placement3d::GeomToStep_MakeAxis2Placement3d(
  const gp_Ax2&           A,
  const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Axis2Placement3d> Axe = MakeAxis2Placement3d(A.Location(),
                                                                    A.Direction(),
                                                                    A.XDirection(),
                                                                    "",
                                                                    theLocalFactors.LengthFactor());
  theAxis2Placement3d                        = Axe;
  done                                       = true;
}

GeomToStep_MakeAxis2Placement3d::GeomToStep_MakeAxis2Placement3d(
  const gp_Ax3&           A,
  const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Axis2Placement3d> Axe = MakeAxis2Placement3d(A.Location(),
                                                                    A.Direction(),
                                                                    A.XDirection(),
                                                                    "",
                                                                    theLocalFactors.LengthFactor());
  theAxis2Placement3d                        = Axe;
  done                                       = true;
}

GeomToStep_MakeAxis2Placement3d::GeomToStep_MakeAxis2Placement3d(
  const gp_Trsf&          T,
  const StepData_Factors& theLocalFactors)
{
  gp_Ax2 A(gp_Pnt(0., 0., 0.), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X));
  A.Transform(T);

  occ::handle<StepGeom_Axis2Placement3d> Axe = MakeAxis2Placement3d(A.Location(),
                                                                    A.Direction(),
                                                                    A.XDirection(),
                                                                    "",
                                                                    theLocalFactors.LengthFactor());
  theAxis2Placement3d                        = Axe;
  done                                       = true;
}

GeomToStep_MakeAxis2Placement3d::GeomToStep_MakeAxis2Placement3d(
  const occ::handle<Geom_Axis2Placement>& Axis2,
  const StepData_Factors&                 theLocalFactors)
{
  gp_Ax2 A;
  A = Axis2->Ax2();

  occ::handle<StepGeom_Axis2Placement3d> Axe = MakeAxis2Placement3d(A.Location(),
                                                                    A.Direction(),
                                                                    A.XDirection(),
                                                                    "",
                                                                    theLocalFactors.LengthFactor());
  theAxis2Placement3d                        = Axe;
  done                                       = true;
}

const occ::handle<StepGeom_Axis2Placement3d>& GeomToStep_MakeAxis2Placement3d::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeAxis2Placement3d::Value() - no result");
  return theAxis2Placement3d;
}
