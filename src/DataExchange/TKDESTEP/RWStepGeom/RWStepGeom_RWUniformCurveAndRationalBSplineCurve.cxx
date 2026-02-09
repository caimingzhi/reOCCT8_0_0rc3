

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWUniformCurveAndRationalBSplineCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <StepGeom_UniformCurve.hpp>
#include <StepGeom_UniformCurveAndRationalBSplineCurve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <RWStepGeom_RWBSplineCurveForm.hpp>

RWStepGeom_RWUniformCurveAndRationalBSplineCurve::
  RWStepGeom_RWUniformCurveAndRationalBSplineCurve() = default;

void RWStepGeom_RWUniformCurveAndRationalBSplineCurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&                      data,
  const int                                                        num0,
  occ::handle<Interface_Check>&                                    ach,
  const occ::handle<StepGeom_UniformCurveAndRationalBSplineCurve>& ent) const
{

  int num = num0;

  if (!data->CheckNbParams(num, 0, ach, "bounded_curve"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 5, ach, "b_spline_curve"))
    return;

  int aDegree;

  data->ReadInteger(num, 1, "degree", ach, aDegree);

  occ::handle<NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>> aControlPointsList;
  occ::handle<StepGeom_CartesianPoint>                                   anent2;
  int                                                                    nsub2;
  if (data->ReadSubList(num, 2, "control_points_list", ach, nsub2))
  {
    int nb2            = data->NbParams(nsub2);
    aControlPointsList = new NCollection_HArray1<occ::handle<StepGeom_CartesianPoint>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {

      if (data->ReadEntity(nsub2,
                           i2,
                           "cartesian_point",
                           ach,
                           STANDARD_TYPE(StepGeom_CartesianPoint),
                           anent2))
        aControlPointsList->SetValue(i2, anent2);
    }
  }

  StepGeom_BSplineCurveForm aCurveForm = StepGeom_bscfPolylineForm;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (!RWStepGeom_RWBSplineCurveForm::ConvertToEnum(text, aCurveForm))
    {
      ach->AddFail("Enumeration b_spline_curve_form has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (curve_form) is not an enumeration");

  StepData_Logical aClosedCurve;

  data->ReadLogical(num, 4, "closed_curve", ach, aClosedCurve);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 5, "self_intersect", ach, aSelfIntersect);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "curve"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "geometric_representation_item"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "rational_b_spline_curve"))
    return;

  occ::handle<NCollection_HArray1<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub6;
  if (data->ReadSubList(num, 1, "weights_data", ach, nsub6))
  {
    int nb6      = data->NbParams(nsub6);
    aWeightsData = new NCollection_HArray1<double>(1, nb6);
    for (int i6 = 1; i6 <= nb6; i6++)
    {

      if (data->ReadReal(nsub6, i6, "weights_data", ach, aWeightsDataItem))
        aWeightsData->SetValue(i6, aWeightsDataItem);
    }
  }

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "uniform_curve"))
    return;

  ent->Init(aName,
            aDegree,
            aControlPointsList,
            aCurveForm,
            aClosedCurve,
            aSelfIntersect,
            aWeightsData);
}

void RWStepGeom_RWUniformCurveAndRationalBSplineCurve::WriteStep(
  StepData_StepWriter&                                             SW,
  const occ::handle<StepGeom_UniformCurveAndRationalBSplineCurve>& ent) const
{

  SW.StartEntity("BOUNDED_CURVE");

  SW.StartEntity("B_SPLINE_CURVE");

  SW.Send(ent->Degree());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbControlPointsList(); i2++)
  {
    SW.Send(ent->ControlPointsListValue(i2));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWBSplineCurveForm::ConvertToString(ent->CurveForm()));

  SW.SendLogical(ent->ClosedCurve());

  SW.SendLogical(ent->SelfIntersect());

  SW.StartEntity("CURVE");

  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("RATIONAL_B_SPLINE_CURVE");

  SW.OpenSub();
  for (int i6 = 1; i6 <= ent->NbWeightsData(); i6++)
  {
    SW.Send(ent->WeightsDataValue(i6));
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());

  SW.StartEntity("UNIFORM_CURVE");
}

void RWStepGeom_RWUniformCurveAndRationalBSplineCurve::Share(
  const occ::handle<StepGeom_UniformCurveAndRationalBSplineCurve>& ent,
  Interface_EntityIterator&                                        iter) const
{

  int nbElem1 = ent->NbControlPointsList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ControlPointsListValue(is1));
  }
}
