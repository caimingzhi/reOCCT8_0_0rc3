

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAppliedOrganizationAssignment.hpp"
#include <StepAP214_AppliedOrganizationAssignment.hpp>
#include <StepAP214_OrganizationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_OrganizationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAppliedOrganizationAssignment::RWStepAP214_RWAppliedOrganizationAssignment() =
  default;

void RWStepAP214_RWAppliedOrganizationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepAP214_AppliedOrganizationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "applied_organization_assignment"))
    return;

  occ::handle<StepBasic_Organization> aAssignedOrganization;
  data->ReadEntity(num,
                   1,
                   "assigned_organization",
                   ach,
                   STANDARD_TYPE(StepBasic_Organization),
                   aAssignedOrganization);

  occ::handle<StepBasic_OrganizationRole> aRole;
  data->ReadEntity(num, 2, "role", ach, STANDARD_TYPE(StepBasic_OrganizationRole), aRole);

  occ::handle<NCollection_HArray1<StepAP214_OrganizationItem>> aItems;
  StepAP214_OrganizationItem                                   aItemsItem;
  int                                                          nsub3;
  if (data->ReadSubList(num, 3, "items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aItems  = new NCollection_HArray1<StepAP214_OrganizationItem>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      bool stat3 = data->ReadEntity(nsub3, i3, "items", ach, aItemsItem);
      if (stat3)
        aItems->SetValue(i3, aItemsItem);
    }
  }

  ent->Init(aAssignedOrganization, aRole, aItems);
}

void RWStepAP214_RWAppliedOrganizationAssignment::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepAP214_AppliedOrganizationAssignment>& ent) const
{

  SW.Send(ent->AssignedOrganization());

  SW.Send(ent->Role());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
  {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAppliedOrganizationAssignment::Share(
  const occ::handle<StepAP214_AppliedOrganizationAssignment>& ent,
  Interface_EntityIterator&                                   iter) const
{

  iter.GetOneItem(ent->AssignedOrganization());
  iter.GetOneItem(ent->Role());
  int nbElem3 = ent->NbItems();
  for (int is3 = 1; is3 <= nbElem3; is3++)
  {
    iter.GetOneItem(ent->ItemsValue(is3).Value());
  }
}
