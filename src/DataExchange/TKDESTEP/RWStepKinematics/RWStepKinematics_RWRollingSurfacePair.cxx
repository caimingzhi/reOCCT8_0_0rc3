

#include "RWStepKinematics_RWRollingSurfacePair.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RollingSurfacePair.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>

RWStepKinematics_RWRollingSurfacePair::RWStepKinematics_RWRollingSurfacePair() = default;

void RWStepKinematics_RWRollingSurfacePair::ReadStep(
  const occ::handle<StepData_StepReaderData>&           theData,
  const int                                             theNum,
  occ::handle<Interface_Check>&                         theArch,
  const occ::handle<StepKinematics_RollingSurfacePair>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 9, theArch, "rolling_surface_pair"))
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

  occ::handle<StepGeom_Surface> aSurfacePair_Surface1;
  theData->ReadEntity(theNum,
                      7,
                      "surface_pair.surface1",
                      theArch,
                      STANDARD_TYPE(StepGeom_Surface),
                      aSurfacePair_Surface1);

  occ::handle<StepGeom_Surface> aSurfacePair_Surface2;
  theData->ReadEntity(theNum,
                      8,
                      "surface_pair.surface2",
                      theArch,
                      STANDARD_TYPE(StepGeom_Surface),
                      aSurfacePair_Surface2);

  bool aSurfacePair_Orientation;
  theData->ReadBoolean(theNum, 9, "surface_pair.orientation", theArch, aSurfacePair_Orientation);

  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aSurfacePair_Surface1,
               aSurfacePair_Surface2,
               aSurfacePair_Orientation);
}

void RWStepKinematics_RWRollingSurfacePair::WriteStep(
  StepData_StepWriter&                                  theSW,
  const occ::handle<StepKinematics_RollingSurfacePair>& theEnt) const
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

  theSW.Send(theEnt->Surface1());

  theSW.Send(theEnt->Surface2());

  theSW.SendBoolean(theEnt->Orientation());
}

void RWStepKinematics_RWRollingSurfacePair::Share(
  const occ::handle<StepKinematics_RollingSurfacePair>& theEnt,
  Interface_EntityIterator&                             iter) const
{

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());

  iter.AddItem(theEnt->StepKinematics_SurfacePair::Surface1());

  iter.AddItem(theEnt->StepKinematics_SurfacePair::Surface2());
}
