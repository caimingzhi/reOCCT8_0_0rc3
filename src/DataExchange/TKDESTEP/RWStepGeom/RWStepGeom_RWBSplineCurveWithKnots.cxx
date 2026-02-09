

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWBSplineCurveWithKnots.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_KnotType.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>

#include "RWStepGeom_RWBSplineCurveForm.hpp"
#include "RWStepGeom_RWKnotType.hpp"

RWStepGeom_RWBSplineCurveWithKnots::RWStepGeom_RWBSplineCurveWithKnots() = default;

void RWStepGeom_RWBSplineCurveWithKnots::ReadStep(
  const occ::handle<StepData_StepReaderData>&        data,
  const int                                          num,
  occ::handle<Interface_Check>&                      ach,
  const occ::handle<StepGeom_BSplineCurveWithKnots>& ent) const
{

  if (!data->CheckNbParams(num, 9, ach, "b_spline_curve_with_knots"))
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
    int nb3 = data->NbParams(nsub3);
    if (nb3 < 1)
      ach->AddFail("Number of control points of the b_spline_curve_form is equal to 0");
    else
    {
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

  occ::handle<NCollection_HArray1<int>> aKnotMultiplicities;
  int                                   aKnotMultiplicitiesItem;
  int                                   nsub7;
  if (data->ReadSubList(num, 7, "knot_multiplicities", ach, nsub7))
  {
    int nb7             = data->NbParams(nsub7);
    aKnotMultiplicities = new NCollection_HArray1<int>(1, nb7);
    for (int i7 = 1; i7 <= nb7; i7++)
    {

      if (data->ReadInteger(nsub7, i7, "knot_multiplicities", ach, aKnotMultiplicitiesItem))
        aKnotMultiplicities->SetValue(i7, aKnotMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aKnots;
  double                                   aKnotsItem;
  int                                      nsub8;
  if (data->ReadSubList(num, 8, "knots", ach, nsub8))
  {
    int nb8 = data->NbParams(nsub8);
    aKnots  = new NCollection_HArray1<double>(1, nb8);
    for (int i8 = 1; i8 <= nb8; i8++)
    {

      if (data->ReadReal(nsub8, i8, "knots", ach, aKnotsItem))
        aKnots->SetValue(i8, aKnotsItem);
    }
  }

  StepGeom_KnotType aKnotSpec = StepGeom_ktUniformKnots;
  if (data->ParamType(num, 9) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 9);
    if (!RWStepGeom_RWKnotType::ConvertToEnum(text, aKnotSpec))
    {
      ach->AddFail("Enumeration knot_type has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #9 (knot_spec) is not an enumeration");

  ent->Init(aName,
            aDegree,
            aControlPointsList,
            aCurveForm,
            aClosedCurve,
            aSelfIntersect,
            aKnotMultiplicities,
            aKnots,
            aKnotSpec);
}

void RWStepGeom_RWBSplineCurveWithKnots::WriteStep(
  StepData_StepWriter&                               SW,
  const occ::handle<StepGeom_BSplineCurveWithKnots>& ent) const
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
  for (int i7 = 1; i7 <= ent->NbKnotMultiplicities(); i7++)
  {
    SW.Send(ent->KnotMultiplicitiesValue(i7));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i8 = 1; i8 <= ent->NbKnots(); i8++)
  {
    SW.Send(ent->KnotsValue(i8));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWKnotType::ConvertToString(ent->KnotSpec()));
}

void RWStepGeom_RWBSplineCurveWithKnots::Share(
  const occ::handle<StepGeom_BSplineCurveWithKnots>& ent,
  Interface_EntityIterator&                          iter) const
{

  int nbElem1 = ent->NbControlPointsList();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->ControlPointsListValue(is1));
  }
}

void RWStepGeom_RWBSplineCurveWithKnots::Check(
  const occ::handle<StepGeom_BSplineCurveWithKnots>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  int nbCPL   = ent->NbControlPointsList();
  int dgBSC   = ent->Degree();
  int nbMult  = ent->NbKnotMultiplicities();
  int nbKno   = ent->NbKnots();
  int sumMult = 0;

  if (nbMult != nbKno)
  {
    ach->AddFail("ERROR: No.of KnotMultiplicities not equal No.of Knots");
  }
  if (nbMult == 0)
  {
    ach->AddFail("ERROR: No.of KnotMultiplicities is equal to 0");
    return;
  }

  int i;
  for (i = 1; i <= nbMult - 1; i++)
  {
    sumMult = sumMult + ent->KnotMultiplicitiesValue(i);
  }
  int sumNonP = nbCPL + dgBSC + 1;
  int mult1   = ent->KnotMultiplicitiesValue(1);
  int multN   = ent->KnotMultiplicitiesValue(nbMult);

  if ((sumMult + multN) == sumNonP)
  {
  }
  else if ((sumMult == nbCPL) && (mult1 == multN))
  {
  }
  else
  {
    ach->AddFail("ERROR: wrong number of Knot Multiplicities");
  }
  for (i = 2; i <= nbKno; i++)
  {
    double distKn = ent->KnotsValue(i - 1) - ent->KnotsValue(i);
    if (std::abs(distKn) <= RealEpsilon())
      ach->AddWarning("WARNING: Curve contains identical KnotsValues");
    else if (distKn > RealEpsilon())
      ach->AddFail("ERROR: Curve contains descending KnotsValues");
  }
}
