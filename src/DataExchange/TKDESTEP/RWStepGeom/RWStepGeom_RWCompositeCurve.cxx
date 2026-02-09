

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWCompositeCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CompositeCurve.hpp>
#include <StepGeom_CompositeCurveSegment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepGeom_RWCompositeCurve::RWStepGeom_RWCompositeCurve() = default;

void RWStepGeom_RWCompositeCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepGeom_CompositeCurve>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "composite_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>> aSegments;
  occ::handle<StepGeom_CompositeCurveSegment>                                   anent2;
  int                                                                           nsub2;
  if (data->ReadSubList(num, 2, "segments", ach, nsub2))
  {
    int nb2   = data->NbParams(nsub2);
    aSegments = new NCollection_HArray1<occ::handle<StepGeom_CompositeCurveSegment>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "composite_curve_segment",
                           ach,
                           STANDARD_TYPE(StepGeom_CompositeCurveSegment),
                           anent2))
        aSegments->SetValue(i2, anent2);
    }
  }

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 3, "self_intersect", ach, aSelfIntersect);

  ent->Init(aName, aSegments, aSelfIntersect);
}

void RWStepGeom_RWCompositeCurve::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepGeom_CompositeCurve>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbSegments(); i2++)
  {
    SW.Send(ent->SegmentsValue(i2));
  }
  SW.CloseSub();

  SW.SendLogical(ent->SelfIntersect());
}

void RWStepGeom_RWCompositeCurve::Share(const occ::handle<StepGeom_CompositeCurve>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  int nbElem1 = ent->NbSegments();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->SegmentsValue(is1));
  }
}
