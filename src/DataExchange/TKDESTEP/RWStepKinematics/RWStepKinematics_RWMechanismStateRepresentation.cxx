#include "RWStepKinematics_RWMechanismStateRepresentation.hpp"

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_MechanismStateRepresentation.hpp>
#include <StepKinematics_MechanismRepresentation.hpp>

RWStepKinematics_RWMechanismStateRepresentation::RWStepKinematics_RWMechanismStateRepresentation() =
  default;

void RWStepKinematics_RWMechanismStateRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                     theData,
  const int                                                       theNum,
  occ::handle<Interface_Check>&                                   theArch,
  const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theArch, "mechanism_state_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(theNum, 1, "name", theArch, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aItems;
  occ::handle<StepRepr_RepresentationItem>                                   anEnt;
  int                                                                        nsub;
  if (theData->ReadSubList(theNum, 2, "items", theArch, nsub))
  {
    int nb = theData->NbParams(nsub);
    aItems = new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      if (theData->ReadEntity(nsub,
                              i,
                              "representation_item",
                              theArch,
                              STANDARD_TYPE(StepRepr_RepresentationItem),
                              anEnt))
        aItems->SetValue(i, anEnt);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aContextOfItems;
  theData->ReadEntity(theNum,
                      3,
                      "context_of_items",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationContext),
                      aContextOfItems);

  occ::handle<StepKinematics_MechanismRepresentation> aRepresentedMechanism;
  theData->ReadEntity(theNum,
                      4,
                      "represented_mechanism",
                      theArch,
                      STANDARD_TYPE(StepKinematics_MechanismRepresentation),
                      aRepresentedMechanism);

  theEnt->Init(aName, aItems, aContextOfItems, aRepresentedMechanism);
}

void RWStepKinematics_RWMechanismStateRepresentation::WriteStep(
  StepData_StepWriter&                                            theSW,
  const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.OpenSub();
  for (int i = 1; i <= theEnt->NbItems(); i++)
  {
    theSW.Send(theEnt->ItemsValue(i));
  }
  theSW.CloseSub();

  theSW.Send(theEnt->ContextOfItems());

  theSW.Send(theEnt->Mechanism());
}

void RWStepKinematics_RWMechanismStateRepresentation::Share(
  const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt,
  Interface_EntityIterator&                                       iter) const
{
  int nbElem = theEnt->NbItems();
  for (int i = 1; i <= nbElem; i++)
  {
    iter.GetOneItem(theEnt->ItemsValue(i));
  }
  iter.GetOneItem(theEnt->ContextOfItems());
  iter.GetOneItem(theEnt->Mechanism());
}
