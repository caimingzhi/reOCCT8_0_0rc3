

#include "RWStepKinematics_RWRigidLinkRepresentation.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepKinematics_RigidLinkRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepKinematics_KinematicLink.hpp>

RWStepKinematics_RWRigidLinkRepresentation::RWStepKinematics_RWRigidLinkRepresentation() = default;

void RWStepKinematics_RWRigidLinkRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                theData,
  const int                                                  theNum,
  occ::handle<Interface_Check>&                              theArch,
  const occ::handle<StepKinematics_RigidLinkRepresentation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theArch, "rigid_link_representation"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentation_Name;
  theData->ReadString(theNum, 1, "representation.name", theArch, aRepresentation_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aRepresentation_Items;
  int                                                                        sub2 = 0;
  if (theData->ReadSubList(theNum, 2, "representation.items", theArch, sub2))
  {
    int nb0 = theData->NbParams(sub2);
    aRepresentation_Items =
      new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepRepr_RepresentationItem> anIt0;
      theData->ReadEntity(num2,
                          i0,
                          "representation_item",
                          theArch,
                          STANDARD_TYPE(StepRepr_RepresentationItem),
                          anIt0);
      aRepresentation_Items->SetValue(i0, anIt0);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aRepresentation_ContextOfItems;
  theData->ReadEntity(theNum,
                      3,
                      "representation.context_of_items",
                      theArch,
                      STANDARD_TYPE(StepRepr_RepresentationContext),
                      aRepresentation_ContextOfItems);

  occ::handle<StepKinematics_KinematicLink> aKinematicLinkRepresentation_RepresentedLink;
  theData->ReadEntity(theNum,
                      4,
                      "kinematic_link_representation.represented_link",
                      theArch,
                      STANDARD_TYPE(StepKinematics_KinematicLink),
                      aKinematicLinkRepresentation_RepresentedLink);

  theEnt->Init(aRepresentation_Name,
               aRepresentation_Items,
               aRepresentation_ContextOfItems,
               aKinematicLinkRepresentation_RepresentedLink);
}

void RWStepKinematics_RWRigidLinkRepresentation::WriteStep(
  StepData_StepWriter&                                       theSW,
  const occ::handle<StepKinematics_RigidLinkRepresentation>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.OpenSub();
  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 = theEnt->Items()->Value(i1);
    theSW.Send(Var0);
  }
  theSW.CloseSub();

  theSW.Send(theEnt->ContextOfItems());

  theSW.Send(theEnt->RepresentedLink());
}

void RWStepKinematics_RWRigidLinkRepresentation::Share(
  const occ::handle<StepKinematics_RigidLinkRepresentation>& theEnt,
  Interface_EntityIterator&                                  iter) const
{

  for (int i1 = 1; i1 <= theEnt->StepRepr_Representation::Items()->Length(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 =
      theEnt->StepRepr_Representation::Items()->Value(i1);
    iter.AddItem(Var0);
  }

  iter.AddItem(theEnt->StepRepr_Representation::ContextOfItems());

  iter.AddItem(theEnt->StepKinematics_KinematicLinkRepresentation::RepresentedLink());
}
