// Created on : Sat May 02 12:41:15 2020

#include "RWStepKinematics_RWPointOnPlanarCurvePairValue.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_PointOnPlanarCurvePairValue.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepKinematics_KinematicPair.hpp>
#include <StepGeom_PointOnCurve.hpp>
#include <StepKinematics_SpatialRotation.hpp>

//=================================================================================================

RWStepKinematics_RWPointOnPlanarCurvePairValue::RWStepKinematics_RWPointOnPlanarCurvePairValue() =
  default;

//=================================================================================================

void RWStepKinematics_RWPointOnPlanarCurvePairValue::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    theData,
  const int                                                      theNum,
  occ::handle<Interface_Check>&                                  theArch,
  const occ::handle<StepKinematics_PointOnPlanarCurvePairValue>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 4, theArch, "point_on_planar_curve_pair_value"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theArch, aRepresentationItem_Name);

  // Inherited fields of PairValue

  occ::handle<StepKinematics_KinematicPair> aPairValue_AppliesToPair;
  theData->ReadEntity(theNum,
                      2,
                      "pair_value.applies_to_pair",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicPair),
                      aPairValue_AppliesToPair);

  // Own fields of PointOnPlanarCurvePairValue

  occ::handle<StepGeom_PointOnCurve> aActualPointOnCurve;
  theData->ReadEntity(theNum,
                      3,
                      "actual_point_on_curve",
                      theArch,
                      STANDARD_TYPE(StepGeom_PointOnCurve),
                      aActualPointOnCurve);

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

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aPairValue_AppliesToPair,
               aActualPointOnCurve,
               aInputOrientation);
}

//=================================================================================================

void RWStepKinematics_RWPointOnPlanarCurvePairValue::WriteStep(
  StepData_StepWriter&                                           theSW,
  const occ::handle<StepKinematics_PointOnPlanarCurvePairValue>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of PairValue

  theSW.Send(theEnt->AppliesToPair());

  // Own fields of PointOnPlanarCurvePairValue

  theSW.Send(theEnt->ActualPointOnCurve());

  if (!theEnt->InputOrientation().YprRotation().IsNull())
  {
    // Inherited field : YPR
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

//=================================================================================================

void RWStepKinematics_RWPointOnPlanarCurvePairValue::Share(
  const occ::handle<StepKinematics_PointOnPlanarCurvePairValue>& theEnt,
  Interface_EntityIterator&                                      iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of PairValue

  iter.AddItem(theEnt->StepKinematics_PairValue::AppliesToPair());

  // Own fields of PointOnPlanarCurvePairValue

  iter.AddItem(theEnt->ActualPointOnCurve());

  if (!theEnt->InputOrientation().RotationAboutDirection().IsNull())
    iter.AddItem(theEnt->InputOrientation().Value());
}
