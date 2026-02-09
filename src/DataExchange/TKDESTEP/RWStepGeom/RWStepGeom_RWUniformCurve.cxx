

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWUniformCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_UniformCurve.hpp>

#include "RWStepGeom_RWBSplineCurveForm.hpp"

RWStepGeom_RWUniformCurve::RWStepGeom_RWUniformCurve() = default;

void RWStepGeom_RWUniformCurve::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepGeom_UniformCurve>&   ent) const
{

  if (!data->CheckNbParams(num, 6, ach, "uniform_curve"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  int aDegree;

  data->ReadInteger(num, 2, "degree", ach, aDegree);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aControlPointsList;
  occ::handle<StepGeom_CartesianPoint>                                   anent3;
  int                                                                    nsub3;
  if (data->ReadSubList(num, 3, "control_points_list", ach, nsub3))
  {
    int nb3            = data->NbParams(nsub3);
    aControlPointsList = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, nb3);
    for (int i3 = 1; i3 <= nb3; i3++)
    {

      if (data->ReadEntity(nsub3,
                           i3,
                           "cartesian_point",
                           ach,
                           STANDARD_TYPE(StepGeom_CartesianPoint),
                           anent3))
        aControlPointsList->SetValue(i3, anent3);
    }
  }

  StepGeom_BSplineCurveForm aCurveForm = StepGeom_bscfPolylineForm;
  if (data->ParamType(num, 4) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 4);
    if (!RWStepGeom_RWBSplineCurveForm::ConvertToEnum(text, aCurveForm))
    {
      ach->AddFail("Enumeration b_spline_curve_form has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #4 (curve_form) is not an enumeration");

  StepData_Logical aClosedCurve;

  data->ReadLogical(num, 5, "closed_curve", ach, aClosedCurve);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 6, "self_intersect", ach, aSelfIntersect);

  ent->Init(aName, aDegree, aControlPointsList, aCurveForm, aClosedCurve, aSelfIntersect);
}

void RWStepGeom_RWUniformCurve::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepGeom_UniformCurve>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Degree());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbControlPointsList(); i3++)
  {
    SW.Send(ent->ControlPointsListValue(i3));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWBSplineCurveForm::ConvertToString(ent->CurveForm()));

  SW.SendLogical(ent->ClosedCurve());

  SW.SendLogical(ent->SelfIntersect());
}

void RWStepGeom_RWUniformCurve::Share(const occ::handle<StepGeom_UniformCurve>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  int nbElem1 = ent->NbControlPointsList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ControlPointsListValue(is1));
  }
}
