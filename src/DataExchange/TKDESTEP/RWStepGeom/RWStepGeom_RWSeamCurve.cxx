

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWSeamCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_SeamCurve.hpp>

#include "RWStepGeom_RWPreferredSurfaceCurveRepresentation.hpp"

RWStepGeom_RWSeamCurve::RWStepGeom_RWSeamCurve() = default;

void RWStepGeom_RWSeamCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                      const int                                   num,
                                      occ::handle<Interface_Check>&               ach,
                                      const occ::handle<StepGeom_SeamCurve>&      ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "seam_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Curve> aCurve3d;

  data->ReadEntity(num, 2, "curve_3d", ach, STANDARD_TYPE(StepGeom_Curve), aCurve3d);

  occ::handle<NCollection_HArray1<StepGeom_PcurveOrSurface>> aAssociatedGeometry;
  StepGeom_PcurveOrSurface                                   aAssociatedGeometryItem;
  occ::handle<Standard_Transient>                            assgeomval;
  int                                                        nsub3;
  if (data->ReadSubList(num, 3, "associated_geometry", ach, nsub3))
  {
    int nb3             = data->NbParams(nsub3);
    aAssociatedGeometry = new NCollection_HArray1<StepGeom_PcurveOrSurface>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3, i3, "associated_geometry", ach, aAssociatedGeometryItem))
        aAssociatedGeometry->SetValue(i3, aAssociatedGeometryItem);
      if (i3 == 1)
        assgeomval = aAssociatedGeometryItem.Value();
      else if (assgeomval == aAssociatedGeometryItem.Value())
        ach->AddFail("Seam Curve with twice the same geom");
    }
  }

  StepGeom_PreferredSurfaceCurveRepresentation aMasterRepresentation = StepGeom_pscrCurve3d;
  if (data->ParamType(num, 4) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 4);
    if (!RWStepGeom_RWPreferredSurfaceCurveRepresentation::ConvertToEnum(text,
                                                                         aMasterRepresentation))
    {
      ach->AddFail("Enumeration preferred_surface_curve_representation has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #4 (master_representation) is not an enumeration");

  ent->Init(aName, aCurve3d, aAssociatedGeometry, aMasterRepresentation);
}

void RWStepGeom_RWSeamCurve::WriteStep(StepData_StepWriter&                   SW,
                                       const occ::handle<StepGeom_SeamCurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Curve3d());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbAssociatedGeometry(); i3++)
  {
    SW.Send(ent->AssociatedGeometryValue(i3).Value());
  }
  SW.CloseSub();

  SW.SendEnum(
    RWStepGeom_RWPreferredSurfaceCurveRepresentation::ConvertToString(ent->MasterRepresentation()));
}

void RWStepGeom_RWSeamCurve::Share(const occ::handle<StepGeom_SeamCurve>& ent,
                                   Interface_EntityIterator&              iter) const
{

  iter.GetOneItem(ent->Curve3d());

  int nbElem2 = ent->NbAssociatedGeometry();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->AssociatedGeometryValue(is2).Value());
  }
}
