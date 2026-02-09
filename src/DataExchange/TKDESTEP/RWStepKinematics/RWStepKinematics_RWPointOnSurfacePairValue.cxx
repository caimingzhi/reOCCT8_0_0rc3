

#include "RWStepKinematics_RWPointOnSurfacePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PointOnSurfacePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnSurface.hpp>
#include <StepKinematics_SpatialRotation.hpp>

RWStepKinematics_RWPointOnSurfacePairValue::RWStepKinematics_RWPointOnSurfacePairValue() = default;

void RWStepKinematics_RWPointOnSurfacePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                theData,
  const int                                                  theNum,
  occ::handle<Interface_Check>&                              theArch,
  const occ::handle<StepKinematics_PointOnSurfacePairValue>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theArch, "point_on_surface_pair_value"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  occ::handle<StepKinematics_KinematicPair> aPairValue_AppliesToPair;
  theData->ReadEntity(theNum,
                      2,
                      "pair_value.applies_to_pair",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicPair),
                      aPairValue_AppliesToPair);

  occ::handle<StepGeom_PointOnSurface> aActualPointOnSurface;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_surface",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnSurface),
                      aActualPointOnSurface);

  StepKinematics_SpatialRotation aInputOrientation;
  if (theData->SubListNumber(theNum, 4, true))
  {
    occ::handle<NCollection_HArray1<double>> aItems;
    int                                      nsub = 0;
    if (theData->ReadSubList(theNum, 4, "items", theArch, nsub))
    {
      int nb   = theData->NbParams(nsub);
      aItems   = new NCollection_HArray1<double>(1, nb);
      int num2 = nsub;
      for (int i0 = 1; i0 <= nb; i0++)
      {
        double anIt0;
        theData->ReadReal(num2, i0, "real", theArch, anIt0);
        aItems->SetValue(i0, anIt0);
      }
    }
    aInputOrientation.SetValue(aItems);
  }
  else
    theData->ReadEntity(theNum, 4, "input_orientation", theArch, aInputOrientation);

  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualPointOnSurface,
               aInputOrientation);
}

void RWStepKinematics_RWPointOnSurfacePairValue::WriteStep(
  StepData_StepWriter&                                       theSW,
  const occ::handle<StepKinematics_PointOnSurfacePairValue>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.Send(theEnt->AppliesToPair());

  theSW.Send(theEnt->ActualPointOnSurface());

  if (!theEnt->InputOrientation().YprRotation().IsNull())
  {

    theSW.OpenSub();
    for (int i = 1; i <= theEnt->InputOrientation().YprRotation()->Length(); i++)
    {
      theSW.Send(theEnt->InputOrientation().YprRotation()->Value(i));
    }
    theSW.CloseSub();
  }
  else
    theSW.Send(theEnt->InputOrientation().Value());
}

void RWStepKinematics_RWPointOnSurfacePairValue::Share(
  const occ::handle<StepKinematics_PointOnSurfacePairValue>& theEnt,
  Interface_EntityIterator&                                  iter) const
{

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  iter.AddItem(theEnt->ActualPointOnSurface());

  if (!theEnt->InputOrientation().RotationAboutDirection().IsNull())
    iter.AddItem(theEnt->InputOrientation().Value());
}
