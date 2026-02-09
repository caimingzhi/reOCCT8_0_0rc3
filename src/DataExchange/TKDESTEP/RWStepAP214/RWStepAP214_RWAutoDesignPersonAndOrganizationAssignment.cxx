

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.hpp"
#include <StepAP214_AutoDesignPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::
  RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment() = default;

void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::ReadStep(
  const occ::handle<StepData_StepReaderData>&                             data,
  const int                                                               num,
  occ::handle<Interface_Check>&                                           ach,
  const occ::handle<StepAP214_AutoDesignPersonAndOrganizationAssignment>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "auto_design_person_and_organization_assignment"))
    return;

  occ::handle<StepBasic_PersonAndOrganization> aAssignedPersonAndOrganization;
  data->ReadEntity(num,
                   1,
                   "assigned_person_and_organization",
                   ach,
                   STANDARD_TYPE(StepBasic_PersonAndOrganization),
                   aAssignedPersonAndOrganization);

  occ::handle<StepBasic_PersonAndOrganizationRole> aRole;
  data->ReadEntity(num, 2, "role", ach, STANDARD_TYPE(StepBasic_PersonAndOrganizationRole), aRole);

  occ::handle<NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>> aItems;
  StepAP214_AutoDesignGeneralOrgItem                                   aItemsItem;
  int                                                                  nsub3;
  if (data->ReadSubList(num, 3, "items", ach, nsub3))
  {
    int nb3 = data->NbParams(nsub3);
    aItems  = new NCollection_HArray1<StepAP214_AutoDesignGeneralOrgItem>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {
      bool stat3 = data->ReadEntity(nsub3, i3, "items", ach, aItemsItem);
      if (stat3)
        aItems->SetValue(i3, aItemsItem);
    }
  }

  ent->Init(aAssignedPersonAndOrganization, aRole, aItems);
}

void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::WriteStep(
  StepData_StepWriter&                                                    SW,
  const occ::handle<StepAP214_AutoDesignPersonAndOrganizationAssignment>& ent) const
{

  SW.Send(ent->AssignedPersonAndOrganization());

  SW.Send(ent->Role());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbItems(); i3++)
  {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}

void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::Share(
  const occ::handle<StepAP214_AutoDesignPersonAndOrganizationAssignment>& ent,
  Interface_EntityIterator&                                               iter) const
{

  iter.GetOneItem(ent->AssignedPersonAndOrganization());

  iter.GetOneItem(ent->Role());

  int nbElem3 = ent->NbItems();
  for (int is3 = 1; is3 <= nbElem3; is3++)
  {
    iter.GetOneItem(ent->ItemsValue(is3).Value());
  }
}
