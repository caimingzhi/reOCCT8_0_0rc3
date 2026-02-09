

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWBSplineCurveWithKnots.hpp"
#include "RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.hpp"
#include "RWStepGeom_RWRationalBSplineCurve.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_KnotType.hpp>
#include <StepGeom_RationalBSplineCurve.hpp>
#include <Standard_Integer.hpp>

#include "RWStepGeom_RWBSplineCurveForm.hpp"
#include "RWStepGeom_RWKnotType.hpp"

RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::
  RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve() = default;

void RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::ReadStep(
  const occ::handle<StepData_StepReaderData>&                               data,
  const int                                                                 num0,
  occ::handle<Interface_Check>&                                             ach,
  const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& ent) const
{

  int num = 0;
  data->NamedForComplex("BOUNDED_CURVE", "BNDCRV", num0, num, ach);

  data->NamedForComplex("B_SPLINE_CURVE", "BSPCR", num0, num, ach);

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

  data->NamedForComplex("B_SPLINE_CURVE_WITH_KNOTS", "BSCWK", num0, num, ach);

  if (!data->CheckNbParams(num, 3, ach, "b_spline_curve_with_knots"))
    return;

  occ::handle<NCollection_HArray1<int>> aKnotMultiplicities;
  int                                   aKnotMultiplicitiesItem;
  int                                   nsub6;
  if (data->ReadSubList(num, 1, "knot_multiplicities", ach, nsub6))
  {
    int nb6             = data->NbParams(nsub6);
    aKnotMultiplicities = new NCollection_HArray1<int>(1, nb6);
    for (int i6 = 1; i6 <= nb6; i6++)
    {

      if (data->ReadInteger(nsub6, i6, "knot_multiplicities", ach, aKnotMultiplicitiesItem))
        aKnotMultiplicities->SetValue(i6, aKnotMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aKnots;
  double                                   aKnotsItem;
  int                                      nsub7;
  if (data->ReadSubList(num, 2, "knots", ach, nsub7))
  {
    int nb7 = data->NbParams(nsub7);
    aKnots  = new NCollection_HArray1<double>(1, nb7);
    for (int i7 = 1; i7 <= nb7; i7++)
    {

      if (data->ReadReal(nsub7, i7, "knots", ach, aKnotsItem))
        aKnots->SetValue(i7, aKnotsItem);
    }
  }

  StepGeom_KnotType aKnotSpec = StepGeom_ktUniformKnots;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (!RWStepGeom_RWKnotType::ConvertToEnum(text, aKnotSpec))
    {
      ach->AddFail("Enumeration knot_type has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #3 (knot_spec) is not an enumeration");

  data->NamedForComplex("CURVE", num0, num, ach);

  data->NamedForComplex("GEOMETRIC_REPRESENTATION_ITEM", "GMRPIT", num0, num, ach);

  data->NamedForComplex("RATIONAL_B_SPLINE_CURVE", "RBSC", num0, num, ach);

  if (!data->CheckNbParams(num, 1, ach, "rational_b_spline_curve"))
    return;

  occ::handle<NCollection_HArray1<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub9;
  if (data->ReadSubList(num, 1, "weights_data", ach, nsub9))
  {
    int nb9      = data->NbParams(nsub9);
    aWeightsData = new NCollection_HArray1<double>(1, nb9);
    for (int i9 = 1; i9 <= nb9; i9++)
    {

      if (data->ReadReal(nsub9, i9, "weights_data", ach, aWeightsDataItem))
        aWeightsData->SetValue(i9, aWeightsDataItem);
    }
  }

  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName,
            aDegree,
            aControlPointsList,
            aCurveForm,
            aClosedCurve,
            aSelfIntersect,
            aKnotMultiplicities,
            aKnots,
            aKnotSpec,
            aWeightsData);
}

void RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::WriteStep(
  StepData_StepWriter&                                                      SW,
  const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& ent) const
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

  SW.StartEntity("B_SPLINE_CURVE_WITH_KNOTS");

  SW.OpenSub();
  for (int i6 = 1; i6 <= ent->NbKnotMultiplicities(); i6++)
  {
    SW.Send(ent->KnotMultiplicitiesValue(i6));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i7 = 1; i7 <= ent->NbKnots(); i7++)
  {
    SW.Send(ent->KnotsValue(i7));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWKnotType::ConvertToString(ent->KnotSpec()));

  SW.StartEntity("CURVE");

  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("RATIONAL_B_SPLINE_CURVE");

  SW.OpenSub();
  for (int i9 = 1; i9 <= ent->NbWeightsData(); i9++)
  {
    SW.Send(ent->WeightsDataValue(i9));
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());
}

void RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::Share(
  const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& ent,
  Interface_EntityIterator&                                                 iter) const
{

  int nbElem1 = ent->NbControlPointsList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ControlPointsListValue(is1));
  }
}

void RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve::Check(
  const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& ent,
  const Interface_ShareTool&                                                aShto,
  occ::handle<Interface_Check>&                                             ach) const
{
  const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& aRationalBSC = ent;
  occ::handle<StepGeom_BSplineCurveWithKnots> aBSCWK = aRationalBSC->BSplineCurveWithKnots();
  RWStepGeom_RWBSplineCurveWithKnots          t1;
  t1.Check(aBSCWK, aShto, ach);
  occ::handle<StepGeom_RationalBSplineCurve> aRBSC = aRationalBSC->RationalBSplineCurve();
  RWStepGeom_RWRationalBSplineCurve          t2;
  t2.Check(aRBSC, aShto, ach);
}
