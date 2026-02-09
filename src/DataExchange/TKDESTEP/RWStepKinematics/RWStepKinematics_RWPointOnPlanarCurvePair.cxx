

#include "RWStepKinematics_RWPointOnPlanarCurvePair.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PointOnPlanarCurvePair.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Curve.hpp>

RWStepKinematics_RWPointOnPlanarCurvePair::RWStepKinematics_RWPointOnPlanarCurvePair() = default;

void RWStepKinematics_RWPointOnPlanarCurvePair::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theArch,
  const occ::handle<StepKinematics_PointOnPlanarCurvePair>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 8, theArch, "point_on_planar_curve_pair"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<TCollection_HAsciiString> aItemDefinedTransformation_Name;
  theData->ReadString(theNum,
                      2,
                      "item_defined_transformation.name",
                      theArch,
                      aItemDefinedTransformation_Name);

  occ::handle<TCollection_HAsciiString> aItemDefinedTransformation_Description;
  bool                                  hasItemDefinedTransformation_Description = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadString(theNum,
                        3,
                        "item_defined_transformation.description",
                        theArch,
                        aItemDefinedTransformation_Description);
  }
  else
  {
    hasItemDefinedTransformation_Description = false;
    aItemDefinedTransformation_Description.Nullify();
  }

  occ::handle<StepRepr_RepresentationItem> aItemDefinedTransformation_TransformItem1;
  theData->ReadEntity(theNum,
                      4,
                      "item_defined_transformation.transform_item1",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationItem),
                      aItemDefinedTransformation_TransformItem1);

  occ::handle<StepRepr_RepresentationItem> aItemDefinedTransformation_TransformItem2;
  theData->ReadEntity(theNum,
                      5,
                      "item_defined_transformation.transform_item2",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationItem),
                      aItemDefinedTransformation_TransformItem2);

  occ::handle<StepKinematics_KinematicJoint> aKinematicPair_Joint;
  theData->ReadEntity(theNum,
                      6,
                      "kinematic_pair.joint",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicJoint),
                      aKinematicPair_Joint);

  occ::handle<StepGeom_Curve> aPairCurve;
  theData->ReadEntity(theNum, 7, "pair_curve", theArch, STANDARD_TYPE(StepGeom_Curve), aPairCurve);

  bool aOrientation;
  theData->ReadBoolean(theNum, 8, "orientation", theArch, aOrientation);

  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aPairCurve,
               aOrientation);
}

void RWStepKinematics_RWPointOnPlanarCurvePair::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepKinematics_PointOnPlanarCurvePair>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->ItemDefinedTransformation()->Name());

  if (theEnt->ItemDefinedTransformation()->HasDescription())
  {
    theSW.Send(theEnt->ItemDefinedTransformation()->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem1());

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem2());

  theSW.Send(theEnt->Joint());

  theSW.Send(theEnt->PairCurve());

  theSW.SendBoolean(theEnt->Orientation());
}

void RWStepKinematics_RWPointOnPlanarCurvePair::Share(
  const occ::handle<StepKinematics_PointOnPlanarCurvePair>& theEnt,
  Interface_EntityIterator&                                 iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());

  iter.AddItem(theEnt->PairCurve());
}
