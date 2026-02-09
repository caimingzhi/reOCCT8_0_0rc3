

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFace.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWFace::RWStepShape_RWFace() = default;

void RWStepShape_RWFace::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach,
                                  const occ::handle<StepShape_Face>&          ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "face"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> aBounds;
  occ::handle<StepShape_FaceBound>                                   anent2;
  int                                                                nsub2;
  if (data->ReadSubList(num, 2, "bounds", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aBounds = new NCollection_HArray1<occ::handle<StepShape_FaceBound>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data
            ->ReadEntity(nsub2, i2, "face_bound", ach, STANDARD_TYPE(StepShape_FaceBound), anent2))
        aBounds->SetValue(i2, anent2);
    }
  }

  ent->Init(aName, aBounds);
}

void RWStepShape_RWFace::WriteStep(StepData_StepWriter&               SW,
                                   const occ::handle<StepShape_Face>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbBounds(); i2++)
  {
    SW.Send(ent->BoundsValue(i2));
  }
  SW.CloseSub();
}

void RWStepShape_RWFace::Share(const occ::handle<StepShape_Face>& ent,
                               Interface_EntityIterator&          iter) const
{

  int nbElem1 = ent->NbBounds();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->BoundsValue(is1));
  }
}
