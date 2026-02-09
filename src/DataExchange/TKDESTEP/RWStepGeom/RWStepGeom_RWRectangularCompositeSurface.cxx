

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWRectangularCompositeSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_RectangularCompositeSurface.hpp>
#include <StepGeom_SurfacePatch.hpp>

RWStepGeom_RWRectangularCompositeSurface::RWStepGeom_RWRectangularCompositeSurface() = default;

void RWStepGeom_RWRectangularCompositeSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&              data,
  const int                                                num,
  occ::handle<Interface_Check>&                            ach,
  const occ::handle<StepGeom_RectangularCompositeSurface>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "rectangular_composite_surface"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>> aSegments;
  occ::handle<StepGeom_SurfacePatch>                                   anent2;
  int                                                                  nsub2;
  if (data->ReadSubList(num, 2, "segments", ach, nsub2))
  {
    int nbi2  = data->NbParams(nsub2);
    int nbj2  = data->NbParams(data->ParamNumber(nsub2, 1));
    aSegments = new NCollection_HArray2<occ::handle<StepGeom_SurfacePatch>>(1, nbi2, 1, nbj2);
    for (int i2 = 1; i2 <= nbi2; i2++)
    {
      int nsi2;
      if (data->ReadSubList(nsub2, i2, "sub-part(segments)", ach, nsi2))
      {
        for (int j2 = 1; j2 <= nbj2; j2++)
        {

          if (data->ReadEntity(nsi2,
                               j2,
                               "surface_patch",
                               ach,
                               STANDARD_TYPE(StepGeom_SurfacePatch),
                               anent2))
            aSegments->SetValue(i2, j2, anent2);
        }
      }
    }
  }

  ent->Init(aName, aSegments);
}

void RWStepGeom_RWRectangularCompositeSurface::WriteStep(
  StepData_StepWriter&                                     SW,
  const occ::handle<StepGeom_RectangularCompositeSurface>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbSegmentsI(); i2++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j2 = 1; j2 <= ent->NbSegmentsJ(); j2++)
    {
      SW.Send(ent->SegmentsValue(i2, j2));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();
}

void RWStepGeom_RWRectangularCompositeSurface::Share(
  const occ::handle<StepGeom_RectangularCompositeSurface>& ent,
  Interface_EntityIterator&                                iter) const
{

  int nbiElem1 = ent->NbSegmentsI();
  int nbjElem1 = ent->NbSegmentsJ();
  for (int is1 = 1; is1 <= nbiElem1; is1++)
  {
    for (int js1 = 1; js1 <= nbjElem1; js1++)
    {
      iter.GetOneItem(ent->SegmentsValue(is1, js1));
    }
  }
}
