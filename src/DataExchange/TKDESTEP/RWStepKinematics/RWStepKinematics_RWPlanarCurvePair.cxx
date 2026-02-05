// Created on : Sat May 02 12:41:15 2020

#include "RWStepKinematics_RWPlanarCurvePair.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PlanarCurvePair.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Curve.hpp>

//=================================================================================================

RWStepKinematics_RWPlanarCurvePair::RWStepKinematics_RWPlanarCurvePair() = default;

//=================================================================================================

void RWStepKinematics_RWPlanarCurvePair::ReadStep(
  const occ::handle<StepData_StepReaderData>&        theData,
  const int                                          theNum,
  occ::handle<Interface_Check>&                      theArch,
  const occ::handle<StepKinematics_PlanarCurvePair>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 9, theArch, "planar_curve_pair"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  // Inherited fields of ItemDefinedTransformation

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

  // Inherited fields of KinematicPair

  occ::handle<StepKinematics_KinematicJoint> aKinematicPair_Joint;
  theData->ReadEntity(theNum,
                      6,
                      "kinematic_pair.joint",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicJoint),
                      aKinematicPair_Joint);

  // Own fields of PlanarCurvePair

  occ::handle<StepGeom_Curve> aCurve1;
  theData->ReadEntity(theNum, 7, "curve1", theArch, STANDARD_TYPE(StepGeom_Curve), aCurve1);

  occ::handle<StepGeom_Curve> aCurve2;
  theData->ReadEntity(theNum, 8, "curve2", theArch, STANDARD_TYPE(StepGeom_Curve), aCurve2);

  bool aOrientation;
  theData->ReadBoolean(theNum, 9, "orientation", theArch, aOrientation);

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aCurve1,
               aCurve2,
               aOrientation);
}

//=================================================================================================

void RWStepKinematics_RWPlanarCurvePair::WriteStep(
  StepData_StepWriter&                               theSW,
  const occ::handle<StepKinematics_PlanarCurvePair>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Inherited fields of ItemDefinedTransformation

  theSW.Send(theEnt->ItemDefinedTransformation()->Name());

  if (theEnt->ItemDefinedTransformation()->HasDescription())
  {
    theSW.Send(theEnt->ItemDefinedTransformation()->Description());
  }
  else
    theSW.SendUndef();

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem1());

  theSW.Send(theEnt->ItemDefinedTransformation()->TransformItem2());

  // Own fields of KinematicPair

  theSW.Send(theEnt->Joint());

  // Own fields of PlanarCurvePair

  theSW.Send(theEnt->Curve1());

  theSW.Send(theEnt->Curve2());

  theSW.SendBoolean(theEnt->Orientation());
}

//=================================================================================================

void RWStepKinematics_RWPlanarCurvePair::Share(
  const occ::handle<StepKinematics_PlanarCurvePair>& theEnt,
  Interface_EntityIterator&                          iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of ItemDefinedTransformation

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  // Inherited fields of KinematicPair

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());

  // Own fields of PlanarCurvePair

  iter.AddItem(theEnt->Curve1());

  iter.AddItem(theEnt->Curve2());
}
