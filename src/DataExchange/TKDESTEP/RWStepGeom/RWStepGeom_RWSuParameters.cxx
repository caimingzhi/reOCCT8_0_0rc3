// Created on : Sat May 02 12:41:14 2020

#include "RWStepGeom_RWSuParameters.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_SuParameters.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Real.hpp>

//=================================================================================================

RWStepGeom_RWSuParameters::RWStepGeom_RWSuParameters() = default;

//=================================================================================================

void RWStepGeom_RWSuParameters::ReadStep(const occ::handle<StepData_StepReaderData>& theData,
                                         const int                                   theNum,
                                         occ::handle<Interface_Check>&               theAch,
                                         const occ::handle<StepGeom_SuParameters>&   theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 7, theAch, "su_parameters"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theAch, aRepresentationItem_Name);

  // Own fields of SuParameters

  double aA;
  theData->ReadReal(theNum, 2, "a", theAch, aA);

  double aAlpha;
  theData->ReadReal(theNum, 3, "alpha", theAch, aAlpha);

  double aB;
  theData->ReadReal(theNum, 4, "b", theAch, aB);

  double aBeta;
  theData->ReadReal(theNum, 5, "beta", theAch, aBeta);

  double aC;
  theData->ReadReal(theNum, 6, "c", theAch, aC);

  double aGamma;
  theData->ReadReal(theNum, 7, "gamma", theAch, aGamma);

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name, aA, aAlpha, aB, aBeta, aC, aGamma);
}

//=================================================================================================

void RWStepGeom_RWSuParameters::WriteStep(StepData_StepWriter&                      theSW,
                                          const occ::handle<StepGeom_SuParameters>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of SuParameters

  theSW.Send(theEnt->A());

  theSW.Send(theEnt->Alpha());

  theSW.Send(theEnt->B());

  theSW.Send(theEnt->Beta());

  theSW.Send(theEnt->C());

  theSW.Send(theEnt->Gamma());
}

//=================================================================================================

void RWStepGeom_RWSuParameters::Share(const occ::handle<StepGeom_SuParameters>& /*theEnt*/,
                                      Interface_EntityIterator& /*iter*/) const
{

  // Inherited fields of RepresentationItem

  // Own fields of SuParameters
}
