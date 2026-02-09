

#include <Geom_Axis2Placement.hpp>
#include <Geom_CartesianPoint.hpp>
#include <gp_Ax3.hpp>
#include <gp_Trsf.hpp>
#include <gp_TrsfForm.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_MappedItem.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS_MakeTransformed.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>

StepToTopoDS_MakeTransformed::StepToTopoDS_MakeTransformed() = default;

bool StepToTopoDS_MakeTransformed::Compute(const occ::handle<StepGeom_Axis2Placement3d>& Origin,
                                           const occ::handle<StepGeom_Axis2Placement3d>& Target,
                                           const StepData_Factors& theLocalFactors)
{
  theTrsf = gp_Trsf();
  if (Origin.IsNull() || Target.IsNull())
    return false;

  occ::handle<Geom_Axis2Placement> theOrig =
    StepToGeom::MakeAxis2Placement(Origin, theLocalFactors);
  if (theOrig.IsNull())
    return false;
  occ::handle<Geom_Axis2Placement> theTarg =
    StepToGeom::MakeAxis2Placement(Target, theLocalFactors);
  if (theTarg.IsNull())
    return false;

  const gp_Ax3 ax3Orig(theOrig->Ax2());
  const gp_Ax3 ax3Targ(theTarg->Ax2());

  theTrsf.SetTransformation(ax3Targ, ax3Orig);
  return true;
}

bool StepToTopoDS_MakeTransformed::Compute(
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& Operator,
  const StepData_Factors&                                        theLocalFactors)
{
  return StepToGeom::MakeTransformation3d(Operator, theTrsf, theLocalFactors);
}

const gp_Trsf& StepToTopoDS_MakeTransformed::Transformation() const
{
  return theTrsf;
}

bool StepToTopoDS_MakeTransformed::Transform(TopoDS_Shape& shape) const
{
  if (theTrsf.Form() == gp_Identity)
    return false;
  TopLoc_Location theLoc(theTrsf);
  shape.Move(theLoc);
  return true;
}

TopoDS_Shape StepToTopoDS_MakeTransformed::TranslateMappedItem(
  const occ::handle<StepRepr_MappedItem>&       mapit,
  const occ::handle<Transfer_TransientProcess>& TP,
  const StepData_Factors&                       theLocalFactors,
  const Message_ProgressRange&                  theProgress)
{
  TopoDS_Shape theResult;

  occ::handle<StepGeom_Axis2Placement3d> Origin =
    occ::down_cast<StepGeom_Axis2Placement3d>(mapit->MappingSource()->MappingOrigin());
  occ::handle<StepGeom_Axis2Placement3d> Target =
    occ::down_cast<StepGeom_Axis2Placement3d>(mapit->MappingTarget());

  occ::handle<StepGeom_CartesianTransformationOperator3d> CartOp =
    occ::down_cast<StepGeom_CartesianTransformationOperator3d>(mapit->MappingTarget());

  bool ok = false;
  if (!Origin.IsNull() && !Target.IsNull())
    ok = Compute(Origin, Target, theLocalFactors);
  else if (!CartOp.IsNull())
    ok = Compute(CartOp, theLocalFactors);

  if (!ok)
    TP->AddWarning(mapit, "Mapped Item, case not recognized, location ignored");

  occ::handle<StepRepr_Representation> maprep = mapit->MappingSource()->MappedRepresentation();
  occ::handle<Transfer_Binder>         binder = TP->Find(maprep);
  if (binder.IsNull())
    binder = TP->Transferring(maprep, theProgress);
  occ::handle<TransferBRep_ShapeBinder> shbinder = occ::down_cast<TransferBRep_ShapeBinder>(binder);
  if (shbinder.IsNull())
    TP->AddWarning(mapit, "No Shape Produced");
  else
  {
    theResult = shbinder->Result();
    Transform(theResult);
  }

  return theResult;
}
