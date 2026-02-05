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

//=============================================================================
// Creation d' un axis2_placement_2d de prostep a partir d' un Ax2 de gp
//=============================================================================
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

//=============================================================================
// Creation d' un axis2_placement_2d de prostep a partir d' un Ax22d de gp
//=============================================================================

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

//=============================================================================
// Creation d' un axis2_placement_2d de prostep a partir d' un Axis2Placement
// de Geom
//=============================================================================

// GeomToStep_MakeAxis2Placement2d::GeomToStep_MakeAxis2Placement2d
//   ( const occ::handle<Geom_Axis2Placement>& Axis2)
//{
//   occ::handle<StepGeom_Axis2Placement2d> Axe;
//   occ::handle<StepGeom_CartesianPoint> P;
//   occ::handle<StepGeom_Direction> D1, D2;
//   gp_Ax2 A;

//  A = Axis2->Ax2();
//  P = GeomToStep_MakeCartesianPoint(A.Location());
//  D1 = GeomToStep_MakeDirection(A.Direction());
//  D2 = GeomToStep_MakeDirection(A.XDirection());
//  Axe = new StepGeom_Axis2Placement2d;
//  Axe->SetLocation(P);
//  Axe->SetAxis(D1);
//  Axe->SetRefDirection(D2);
//  theAxis2Placement2d = Axe;
//  done = true;
//}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Axis2Placement2d>& GeomToStep_MakeAxis2Placement2d::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeAxis2Placement2d::Value() - no result");
  return theAxis2Placement2d;
}
