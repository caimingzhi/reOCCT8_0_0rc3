

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWRationalBSplineSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

#include "RWStepGeom_RWBSplineSurfaceForm.hpp"

RWStepGeom_RWRationalBSplineSurface::RWStepGeom_RWRationalBSplineSurface() = default;

void RWStepGeom_RWRationalBSplineSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepGeom_RationalBSplineSurface>& ent) const
{

  if (!data->CheckNbParams(num, 9, ach, "rational_b_spline_surface"))
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

  occ::handle<NCollection_HArray2<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub9;
  if (data->ReadSubList(num, 9, "weights_data", ach, nsub9))
  {
    int nbi9     = data->NbParams(nsub9);
    int nbj9     = data->NbParams(data->ParamNumber(nsub9, 1));
    aWeightsData = new NCollection_HArray2<double>(1, nbi9, 1, nbj9);
    for (int i9 = 1; i9 <= nbi9; i9++)
    {
      int nsi9;
      if (data->ReadSubList(nsub9, i9, "sub-part(weights_data)", ach, nsi9))
      {
        for (int j9 = 1; j9 <= nbj9; j9++)
        {

          if (data->ReadReal(nsi9, j9, "weights_data", ach, aWeightsDataItem))
            aWeightsData->SetValue(i9, j9, aWeightsDataItem);
        }
      }
    }
  }

  ent->Init(aName,
            aUDegree,
            aVDegree,
            aControlPointsList,
            aSurfaceForm,
            aUClosed,
            aVClosed,
            aSelfIntersect,
            aWeightsData);
}

void RWStepGeom_RWRationalBSplineSurface::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepGeom_RationalBSplineSurface>& ent) const
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
  for (int i9 = 1; i9 <= ent->NbWeightsDataI(); i9++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j9 = 1; j9 <= ent->NbWeightsDataJ(); j9++)
    {
      SW.Send(ent->WeightsDataValue(i9, j9));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();
}

void RWStepGeom_RWRationalBSplineSurface::Share(
  const occ::handle<StepGeom_RationalBSplineSurface>& ent,
  Interface_EntityIterator&                           iter) const
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

void RWStepGeom_RWRationalBSplineSurface::Check(
  const occ::handle<StepGeom_RationalBSplineSurface>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  int nbWgtU = ent->NbWeightsDataI();
  int nbWgtV = ent->NbWeightsDataJ();
  int nbCPLU = ent->NbControlPointsListI();
  int nbCPLV = ent->NbControlPointsListJ();
  int i;
  int j;

  if (nbWgtU != nbCPLU)
  {
    ach->AddFail("ERROR: No.of ControlPoints not equal No.of Weights in U");
  }
  if (nbWgtV != nbCPLV)
  {
    ach->AddFail("ERROR: No.of ControlPoints not equal No.of Weights in V");
  }
  for (i = 1; i <= nbWgtU; i++)
  {
    for (j = 1; j <= nbWgtV; j++)
    {
      if (ent->WeightsDataValue(i, j) < RealEpsilon())
      {
        ach->AddFail("ERROR: WeightsData Value not greater than 0.0");
      }
    }
  }
}
