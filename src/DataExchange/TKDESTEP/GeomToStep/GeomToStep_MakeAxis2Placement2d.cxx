#include <GeomToStep_MakeAxis2Placement2d.hpp>
#include <GeomToStep_MakeCartesianPoint.hpp>
#include <GeomToStep_MakeDirection.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax22d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeAxis2Placement2d::GeomToStep_MakeAxis2Placement2d(
  const gp_Ax2&           A,
  const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Axis2Placement2d> Axe;
  occ::handle<StepGeom_CartesianPoint>   P;
  occ::handle<StepGeom_Direction>        D;

  GeomToStep_MakeCartesianPoint MkPoint(A.Location(), theLocalFactors.LengthFactor());
  GeomToStep_MakeDirection      MkDir(A.Direction());

  P = MkPoint.Value();
  D = MkDir.Value();

  Axe = new StepGeom_Axis2Placement2d;
  Axe->SetLocation(P);
  Axe->SetRefDirection(D);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Axe->SetName(name);
  theAxis2Placement2d = Axe;
  done                = true;
}

GeomToStep_MakeAxis2Placement2d::GeomToStep_MakeAxis2Placement2d(
  const gp_Ax22d&         A,
  const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Axis2Placement2d> Axe;
  occ::handle<StepGeom_CartesianPoint>   P;
  occ::handle<StepGeom_Direction>        D1;

  GeomToStep_MakeCartesianPoint MkPoint(A.Location(), theLocalFactors.LengthFactor());
  GeomToStep_MakeDirection      MkDir(A.XDirection());

  P  = MkPoint.Value();
  D1 = MkDir.Value();

  Axe = new StepGeom_Axis2Placement2d;
  Axe->SetLocation(P);
  Axe->SetRefDirection(D1);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Axe->SetName(name);
  theAxis2Placement2d = Axe;
  done                = true;
}

const occ::handle<StepGeom_Axis2Placement2d>& GeomToStep_MakeAxis2Placement2d::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeAxis2Placement2d::Value() - no result");
  return theAxis2Placement2d;
}
