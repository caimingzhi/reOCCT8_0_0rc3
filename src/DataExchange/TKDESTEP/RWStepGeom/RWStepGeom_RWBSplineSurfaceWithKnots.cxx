

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWBSplineSurfaceWithKnots.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_KnotType.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include "RWStepGeom_RWBSplineSurfaceForm.hpp"
#include "RWStepGeom_RWKnotType.hpp"

RWStepGeom_RWBSplineSurfaceWithKnots::RWStepGeom_RWBSplineSurfaceWithKnots() = default;

void RWStepGeom_RWBSplineSurfaceWithKnots::ReadStep(
  const occ::handle<StepData_StepReaderData>&          data,
  const int                                            num,
  occ::handle<Interface_Check>&                        ach,
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& ent) const
{

  if (!data->CheckNbParams(num, 13, ach, "b_spline_surface_with_knots"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  int aUDegree;

  data->ReadInteger(num, 2, "u_degree", ach, aUDegree);

  int aVDegree;

  data->ReadInteger(num, 3, "v_degree", ach, aVDegree);

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aControlPointsList;
  occ::handle<StepGeom_CartesianPoint>                                   anent4;
  int                                                                    nsub4;
  if (data->ReadSubList(num, 4, "control_points_list", ach, nsub4))
  {
    int nbi4 = data->NbParams(nsub4);
    int nbj4 = data->NbParams(data->ParamNumber(nsub4, 1));
    aControlPointsList =
      new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, nbi4, 1, nbj4);
    for (int i4 = 1; i4 <= nbi4; i4++)
    {
      int nsi4;
      if (data->ReadSubList(nsub4, i4, "sub-part(control_points_list)", ach, nsi4))
      {
        for (int j4 = 1; j4 <= nbj4; j4++)
        {

          if (data->ReadEntity(nsi4,
                               j4,
                               "cartesian_point",
                               ach,
                               STANDARD_TYPE(StepGeom_CartesianPoint),
                               anent4))
            aControlPointsList->SetValue(i4, j4, anent4);
        }
      }
    }
  }

  StepGeom_BSplineSurfaceForm aSurfaceForm = StepGeom_bssfPlaneSurf;
  if (data->ParamType(num, 5) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 5);
    if (!RWStepGeom_RWBSplineSurfaceForm::ConvertToEnum(text, aSurfaceForm))
    {
      ach->AddFail("Enumeration b_spline_surface_form has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #5 (surface_form) is not an enumeration");

  StepData_Logical aUClosed;

  data->ReadLogical(num, 6, "u_closed", ach, aUClosed);

  StepData_Logical aVClosed;

  data->ReadLogical(num, 7, "v_closed", ach, aVClosed);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 8, "self_intersect", ach, aSelfIntersect);

  occ::handle<NCollection_HArray1<int>> aUMultiplicities;
  int                                   aUMultiplicitiesItem;
  int                                   nsub9;
  if (data->ReadSubList(num, 9, "u_multiplicities", ach, nsub9))
  {
    int nb9          = data->NbParams(nsub9);
    aUMultiplicities = new NCollection_HArray1<int>(1, nb9);
    for (int i9 = 1; i9 <= nb9; i9++)
    {

      if (data->ReadInteger(nsub9, i9, "u_multiplicities", ach, aUMultiplicitiesItem))
        aUMultiplicities->SetValue(i9, aUMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<int>> aVMultiplicities;
  int                                   aVMultiplicitiesItem;
  int                                   nsub10;
  if (data->ReadSubList(num, 10, "v_multiplicities", ach, nsub10))
  {
    int nb10         = data->NbParams(nsub10);
    aVMultiplicities = new NCollection_HArray1<int>(1, nb10);
    for (int i10 = 1; i10 <= nb10; i10++)
    {

      if (data->ReadInteger(nsub10, i10, "v_multiplicities", ach, aVMultiplicitiesItem))
        aVMultiplicities->SetValue(i10, aVMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aUKnots;
  double                                   aUKnotsItem;
  int                                      nsub11;
  if (data->ReadSubList(num, 11, "u_knots", ach, nsub11))
  {
    int nb11 = data->NbParams(nsub11);
    aUKnots  = new NCollection_HArray1<double>(1, nb11);
    for (int i11 = 1; i11 <= nb11; i11++)
    {

      if (data->ReadReal(nsub11, i11, "u_knots", ach, aUKnotsItem))
        aUKnots->SetValue(i11, aUKnotsItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aVKnots;
  double                                   aVKnotsItem;
  int                                      nsub12;
  if (data->ReadSubList(num, 12, "v_knots", ach, nsub12))
  {
    int nb12 = data->NbParams(nsub12);
    aVKnots  = new NCollection_HArray1<double>(1, nb12);
    for (int i12 = 1; i12 <= nb12; i12++)
    {

      if (data->ReadReal(nsub12, i12, "v_knots", ach, aVKnotsItem))
        aVKnots->SetValue(i12, aVKnotsItem);
    }
  }

  StepGeom_KnotType aKnotSpec = StepGeom_ktUniformKnots;
  if (data->ParamType(num, 13) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 13);
    if (!RWStepGeom_RWKnotType::ConvertToEnum(text, aKnotSpec))
    {
      ach->AddFail("Enumeration knot_type has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #13 (knot_spec) is not an enumeration");

  ent->Init(aName,
            aUDegree,
            aVDegree,
            aControlPointsList,
            aSurfaceForm,
            aUClosed,
            aVClosed,
            aSelfIntersect,
            aUMultiplicities,
            aVMultiplicities,
            aUKnots,
            aVKnots,
            aKnotSpec);
}

void RWStepGeom_RWBSplineSurfaceWithKnots::WriteStep(
  StepData_StepWriter&                                 SW,
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->UDegree());

  SW.Send(ent->VDegree());

  SW.OpenSub();
  for (int i4 = 1; i4 <= ent->NbControlPointsListI(); i4++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j4 = 1; j4 <= ent->NbControlPointsListJ(); j4++)
    {
      SW.Send(ent->ControlPointsListValue(i4, j4));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWBSplineSurfaceForm::ConvertToString(ent->SurfaceForm()));

  SW.SendLogical(ent->UClosed());

  SW.SendLogical(ent->VClosed());

  SW.SendLogical(ent->SelfIntersect());

  SW.OpenSub();
  for (int i9 = 1; i9 <= ent->NbUMultiplicities(); i9++)
  {
    SW.Send(ent->UMultiplicitiesValue(i9));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i10 = 1; i10 <= ent->NbVMultiplicities(); i10++)
  {
    SW.Send(ent->VMultiplicitiesValue(i10));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i11 = 1; i11 <= ent->NbUKnots(); i11++)
  {
    SW.Send(ent->UKnotsValue(i11));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i12 = 1; i12 <= ent->NbVKnots(); i12++)
  {
    SW.Send(ent->VKnotsValue(i12));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWKnotType::ConvertToString(ent->KnotSpec()));
}

void RWStepGeom_RWBSplineSurfaceWithKnots::Share(
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& ent,
  Interface_EntityIterator&                            iter) const
{

  int nbiElem1 = ent->NbControlPointsListI();
  int nbjElem1 = ent->NbControlPointsListJ();
  for (int is1 = 1; is1 <= nbiElem1; is1++)
  {
    for (int js1 = 1; js1 <= nbjElem1; js1++)
    {
      iter.GetOneItem(ent->ControlPointsListValue(is1, js1));
    }
  }
}

void RWStepGeom_RWBSplineSurfaceWithKnots::Check(
  const occ::handle<StepGeom_BSplineSurfaceWithKnots>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  int nbCPLU  = ent->NbControlPointsListI();
  int nbCPLV  = ent->NbControlPointsListJ();
  int dgBSSU  = ent->UDegree();
  int dgBSSV  = ent->VDegree();
  int nbMulU  = ent->NbUMultiplicities();
  int nbMulV  = ent->NbVMultiplicities();
  int nbKnoU  = ent->NbUKnots();
  int nbKnoV  = ent->NbVKnots();
  int sumMulU = 0;
  int sumMulV = 0;
  int i;

  if (nbMulU != nbKnoU)
  {
    ach->AddFail("ERROR: No.of KnotMultiplicities not equal No.of Knots in U");
  }
  if (nbMulV != nbKnoV)
  {
    ach->AddFail("ERROR: No.of KnotMultiplicities not equal No.of Knots in V");
  }
  if (nbMulU == 0)
  {
    ach->AddWarning("WARNING: No.of KnotMultiplicities in U is zero");
    return;
  }
  if (nbMulV == 0)
  {
    ach->AddWarning("WARNING: No.of KnotMultiplicities in V is zero");
    return;
  }

  for (i = 1; i <= nbMulU - 1; i++)
  {
    sumMulU = sumMulU + ent->UMultiplicitiesValue(i);
  }
  int sumNonPU = nbCPLU + dgBSSU + 1;
  int mult1U   = ent->UMultiplicitiesValue(1);
  int multNU   = ent->UMultiplicitiesValue(nbMulU);

  if ((sumMulU + multNU) == sumNonPU)
  {
  }
  else if ((sumMulU == nbCPLU) && (mult1U == multNU))
  {
  }
  else
  {
    ach->AddFail("ERROR: wrong number of Knot Multiplicities in U");
  }
  for (i = 2; i <= nbKnoU; i++)
  {
    double distKn = ent->UKnotsValue(i - 1) - ent->UKnotsValue(i);
    if (std::abs(distKn) <= RealEpsilon())
      ach->AddWarning("WARNING: Surface contains identical KnotsValues in U");
    else if (distKn > RealEpsilon())
      ach->AddFail("ERROR: Surface contains descending KnotsValues in U");
  }

  for (i = 1; i <= nbMulV - 1; i++)
  {
    sumMulV = sumMulV + ent->VMultiplicitiesValue(i);
  }
  int sumNonPV = nbCPLV + dgBSSV + 1;
  int mult1V   = ent->VMultiplicitiesValue(1);
  int multNV   = ent->VMultiplicitiesValue(nbMulV);

  if ((sumMulV + multNV) == sumNonPV)
  {
  }
  else if ((sumMulV == nbCPLV) && (mult1V == multNV))
  {
  }
  else
  {
    ach->AddFail("ERROR: wrong number of Knot Multiplicities in V");
  }
  for (i = 2; i <= nbKnoV; i++)
  {
    double distKn = ent->VKnotsValue(i - 1) - ent->VKnotsValue(i);
    if (std::abs(distKn) <= RealEpsilon())
      ach->AddWarning("WARNING: Surface contains identical KnotsValues in V");
    else if (distKn > RealEpsilon())
      ach->AddFail("ERROR: Surface contains descending KnotsValues in V");
  }
}
