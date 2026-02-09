

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWRationalBSplineCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include "RWStepGeom_RWBSplineCurveForm.hpp"

RWStepGeom_RWRationalBSplineCurve::RWStepGeom_RWRationalBSplineCurve() = default;

void RWStepGeom_RWRationalBSplineCurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepGeom_RationalBSplineCurve>& ent) const
{

  if (!data->CheckNbParams(num, 7, ach, "rational_b_spline_curve"))
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

  occ::handle<NCollection_HArray1<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub7;
  if (data->ReadSubList(num, 7, "weights_data", ach, nsub7))
  {
    int nb7      = data->NbParams(nsub7);
    aWeightsData = new NCollection_HArray1<double>(1, nb7);
    for (int i7 = 1; i7 <= nb7; i7++)
    {

      if (data->ReadReal(nsub7, i7, "weights_data", ach, aWeightsDataItem))
        aWeightsData->SetValue(i7, aWeightsDataItem);
    }
  }

  ent->Init(aName,
            aDegree,
            aControlPointsList,
            aCurveForm,
            aClosedCurve,
            aSelfIntersect,
            aWeightsData);
}

void RWStepGeom_RWRationalBSplineCurve::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepGeom_RationalBSplineCurve>& ent) const
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

  SW.OpenSub();
  for (int i7 = 1; i7 <= ent->NbWeightsData(); i7++)
  {
    SW.Send(ent->WeightsDataValue(i7));
  }
  SW.CloseSub();
}

void RWStepGeom_RWRationalBSplineCurve::Share(const occ::handle<StepGeom_RationalBSplineCurve>& ent,
                                              Interface_EntityIterator& iter) const
{

  int nbElem1 = ent->NbControlPointsList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ControlPointsListValue(is1));
  }
}

void RWStepGeom_RWRationalBSplineCurve::Check(const occ::handle<StepGeom_RationalBSplineCurve>& ent,
                                              const Interface_ShareTool&,
                                              occ::handle<Interface_Check>& ach) const
{
  int nbWght = ent->NbWeightsData();
  int nbCPL  = ent->NbControlPointsList();

  if (nbWght != nbCPL)
  {
    ach->AddFail("ERROR: No.of ControlPoints not equal No.of Weights");
  }
  for (int i = 1; i <= nbWght; i++)
  {
    if (ent->WeightsDataValue(i) < RealEpsilon())
    {
      ach->AddFail("ERROR: WeightsData Value not greater than 0.0");
    }
  }
}
