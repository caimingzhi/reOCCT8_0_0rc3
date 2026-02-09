

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWClosedShell.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWClosedShell::RWStepShape_RWClosedShell() = default;

void RWStepShape_RWClosedShell::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepShape_ClosedShell>&   ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "closed_shell"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> aCfsFaces;
  occ::handle<StepShape_Face>                                   anent2;
  int                                                           nsub2;
  if (data->ReadSubList(num, 2, "cfs_faces", ach, nsub2))
  {
    int nb2   = data->NbParams(nsub2);
    aCfsFaces = new NCollection_HArray1<occ::handle<StepShape_Face>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2, i2, "face", ach, STANDARD_TYPE(StepShape_Face), anent2))
        aCfsFaces->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aCfsFaces);
}

void RWStepShape_RWClosedShell::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepShape_ClosedShell>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbCfsFaces(); i2++)
  {
    SW.Send(ent->CfsFacesValue(i2));
  }
  SW.CloseSub();
}

void RWStepShape_RWClosedShell::Share(const occ::handle<StepShape_ClosedShell>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  int nbElem1 = ent->NbCfsFaces();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->CfsFacesValue(is1));
  }
}
