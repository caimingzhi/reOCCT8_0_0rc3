

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWAdvancedFace.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Surface.hpp>
#include <StepShape_AdvancedFace.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWAdvancedFace::RWStepShape_RWAdvancedFace() = default;

void RWStepShape_RWAdvancedFace::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepShape_AdvancedFace>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "advanced_face"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> aBounds;
  occ::handle<StepShape_FaceBound>                                   anent2;
  int                                                                nsub2;
  if (data->ReadSubList(num, 2, "bounds", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    if (nb2)
    {
      aBounds = new NCollection_HArray1<occ::handle<StepShape_FaceBound>>(1, nb2);
      for (int i2 = 1; i2 <= nb2; i2++)
      {

        if (data->ReadEntity(nsub2,
                             i2,
                             "face_bound",
                             ach,
                             STANDARD_TYPE(StepShape_FaceBound),
                             anent2))
          aBounds->SetValue(i2, anent2);
      }
    }
  }

  occ::handle<StepGeom_Surface> aFaceGeometry;

  data->ReadEntity(num, 3, "face_geometry", ach, STANDARD_TYPE(StepGeom_Surface), aFaceGeometry);

  bool aSameSense = true;

  data->ReadBoolean(num, 4, "same_sense", ach, aSameSense);

  ent->Init(aName, aBounds, aFaceGeometry, aSameSense);
}

void RWStepShape_RWAdvancedFace::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepShape_AdvancedFace>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbBounds(); i2++)
  {
    SW.Send(ent->BoundsValue(i2));
  }
  SW.CloseSub();

  SW.Send(ent->FaceGeometry());

  SW.SendBoolean(ent->SameSense());
}

void RWStepShape_RWAdvancedFace::Share(const occ::handle<StepShape_AdvancedFace>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  int nbElem1 = ent->NbBounds();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->BoundsValue(is1));
  }

  iter.GetOneItem(ent->FaceGeometry());
}
