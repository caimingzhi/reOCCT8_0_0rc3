// Created on : Sat May 02 12:41:16 2020

#include "RWStepKinematics_RWSurfacePairWithRange.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_SurfacePairWithRange.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <Standard_Real.hpp>

//=================================================================================================

RWStepKinematics_RWSurfacePairWithRange::RWStepKinematics_RWSurfacePairWithRange() = default;

//=================================================================================================

void RWStepKinematics_RWSurfacePairWithRange::ReadStep(
  const occ::handle<StepData_StepReaderData>&             theData,
  const int                                               theNum,
  occ::handle<Interface_Check>&                           theArch,
  const occ::handle<StepKinematics_SurfacePairWithRange>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 13, theArch, "surface_pair_with_range"))
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

  // Inherited fields of SurfacePair

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

  // Own fields of SurfacePairWithRange

  occ::handle<StepGeom_RectangularTrimmedSurface> aRangeOnSurface1;
  theData->ReadEntity(theNum,
                      10,
                      "range_on_surface1",
                      theArch,
                      STANDARD_TYPE(StepGeom_RectangularTrimmedSurface),
                      aRangeOnSurface1);

  occ::handle<StepGeom_RectangularTrimmedSurface> aRangeOnSurface2;
  theData->ReadEntity(theNum,
                      11,
                      "range_on_surface2",
                      theArch,
                      STANDARD_TYPE(StepGeom_RectangularTrimmedSurface),
                      aRangeOnSurface2);

  double aLowerLimitActualRotation;
  bool   hasLowerLimitActualRotation = true;
  if (theData->IsParamDefined(theNum, 12))
  {
    theData->ReadReal(theNum,
                      12,
                      "lower_limit_actual_rotation",
                      theArch,
                      aLowerLimitActualRotation);
  }
  else
  {
    hasLowerLimitActualRotation = false;
    aLowerLimitActualRotation   = 0;
  }

  double aUpperLimitActualRotation;
  bool   hasUpperLimitActualRotation = true;
  if (theData->IsParamDefined(theNum, 13))
  {
    theData->ReadReal(theNum,
                      13,
                      "upper_limit_actual_rotation",
                      theArch,
                      aUpperLimitActualRotation);
  }
  else
  {
    hasUpperLimitActualRotation = false;
    aUpperLimitActualRotation   = 0;
  }

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aItemDefinedTransformation_Name,
               hasItemDefinedTransformation_Description,
               aItemDefinedTransformation_Description,
               aItemDefinedTransformation_TransformItem1,
               aItemDefinedTransformation_TransformItem2,
               aKinematicPair_Joint,
               aSurfacePair_Surface1,
               aSurfacePair_Surface2,
               aSurfacePair_Orientation,
               aRangeOnSurface1,
               aRangeOnSurface2,
               hasLowerLimitActualRotation,
               aLowerLimitActualRotation,
               hasUpperLimitActualRotation,
               aUpperLimitActualRotation);
}

//=================================================================================================

void RWStepKinematics_RWSurfacePairWithRange::WriteStep(
  StepData_StepWriter&                                    theSW,
  const occ::handle<StepKinematics_SurfacePairWithRange>& theEnt) const
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

  // Own fields of SurfacePair

  theSW.Send(theEnt->Surface1());

  theSW.Send(theEnt->Surface2());

  theSW.SendBoolean(theEnt->Orientation());

  // Own fields of SurfacePairWithRange

  theSW.Send(theEnt->RangeOnSurface1());

  theSW.Send(theEnt->RangeOnSurface2());

  if (theEnt->HasLowerLimitActualRotation())
  {
    theSW.Send(theEnt->LowerLimitActualRotation());
  }
  else
    theSW.SendUndef();

  if (theEnt->HasUpperLimitActualRotation())
  {
    theSW.Send(theEnt->UpperLimitActualRotation());
  }
  else
    theSW.SendUndef();
}

//=================================================================================================

void RWStepKinematics_RWSurfacePairWithRange::Share(
  const occ::handle<StepKinematics_SurfacePairWithRange>& theEnt,
  Interface_EntityIterator&                               iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of ItemDefinedTransformation

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem1());

  iter.AddItem(theEnt->ItemDefinedTransformation()->TransformItem2());

  // Inherited fields of KinematicPair

  iter.AddItem(theEnt->StepKinematics_KinematicPair::Joint());

  // Inherited fields of SurfacePair

  iter.AddItem(theEnt->StepKinematics_SurfacePair::Surface1());

  iter.AddItem(theEnt->StepKinematics_SurfacePair::Surface2());

  // Own fields of SurfacePairWithRange

  iter.AddItem(theEnt->RangeOnSurface1());

  iter.AddItem(theEnt->RangeOnSurface2());
}
