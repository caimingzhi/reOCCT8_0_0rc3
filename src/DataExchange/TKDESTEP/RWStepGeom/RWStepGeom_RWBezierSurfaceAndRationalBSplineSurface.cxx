

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BezierSurfaceAndRationalBSplineSurface.hpp>
#include <StepGeom_BSplineSurfaceForm.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

#include "RWStepGeom_RWBSplineSurfaceForm.hpp"

RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::
  RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface() = default;

void RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&                         data,
  const int                                                           num0,
  occ::handle<Interface_Check>&                                       ach,
  const occ::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface>& ent) const
{

  int num = num0;

  if (!data->CheckNbParams(num, 0, ach, "bezier_surface"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "bounded_surface"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 7, ach, "b_spline_surface"))
    return;

  int aUDegree;

  data->ReadInteger(num, 1, "u_degree", ach, aUDegree);

  int aVDegree;

  data->ReadInteger(num, 2, "v_degree", ach, aVDegree);

  occ::handle<NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>> aControlPointsList;
  occ::handle<StepGeom_CartesianPoint>                                   anent3;
  int                                                                    nsub3;
  if (data->ReadSubList(num, 3, "control_points_list", ach, nsub3))
  {
    int nbi3 = data->NbParams(nsub3);
    int nbj3 = data->NbParams(data->ParamNumber(nsub3, 1));
    aControlPointsList =
      new NCollection_HArray2<occ::handle<StepGeom_CartesianPoint>>(1, nbi3, 1, nbj3);
    for (int i3 = 1; i3 <= nbi3; i3++)
    {
      int nsi3;
      if (data->ReadSubList(nsub3, i3, "sub-part(control_points_list)", ach, nsi3))
      {
        for (int j3 = 1; j3 <= nbj3; j3++)
        {

          if (data->ReadEntity(nsi3,
                               j3,
                               "cartesian_point",
                               ach,
                               STANDARD_TYPE(StepGeom_CartesianPoint),
                               anent3))
            aControlPointsList->SetValue(i3, j3, anent3);
        }
      }
    }
  }

  StepGeom_BSplineSurfaceForm aSurfaceForm = StepGeom_bssfPlaneSurf;
  if (data->ParamType(num, 4) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 4);
    if (!RWStepGeom_RWBSplineSurfaceForm::ConvertToEnum(text, aSurfaceForm))
    {
      ach->AddFail("Enumeration b_spline_surface_form has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #4 (surface_form) is not an enumeration");

  StepData_Logical aUClosed;

  data->ReadLogical(num, 5, "u_closed", ach, aUClosed);

  StepData_Logical aVClosed;

  data->ReadLogical(num, 6, "v_closed", ach, aVClosed);

  StepData_Logical aSelfIntersect;

  data->ReadLogical(num, 7, "self_intersect", ach, aSelfIntersect);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "geometric_representation_item"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "rational_b_spline_surface"))
    return;

  occ::handle<NCollection_HArray2<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub8;
  if (data->ReadSubList(num, 1, "items", ach, nsub8))
  {
    int nbi8     = data->NbParams(nsub8);
    int nbj8     = data->NbParams(data->ParamNumber(nsub8, 1));
    aWeightsData = new NCollection_HArray2<double>(1, nbi8, 1, nbj8);
    for (int i8 = 1; i8 <= nbi8; i8++)
    {
      int nsi8;
      if (data->ReadSubList(nsub8, i8, "sub-part(weights_data)", ach, nsi8))
      {
        for (int j8 = 1; j8 <= nbj8; j8++)
        {

          if (data->ReadReal(nsi8, j8, "weights_data", ach, aWeightsDataItem))
            aWeightsData->SetValue(i8, j8, aWeightsDataItem);
        }
      }
    }
  }

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "surface"))
    return;

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

void RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::WriteStep(
  StepData_StepWriter&                                                SW,
  const occ::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface>& ent) const
{

  SW.StartEntity("BEZIER_SURFACE");

  SW.StartEntity("BOUNDED_SURFACE");

  SW.StartEntity("B_SPLINE_SURFACE");

  SW.Send(ent->UDegree());

  SW.Send(ent->VDegree());

  SW.OpenSub();
  for (int i3 = 1; i3 <= ent->NbControlPointsListI(); i3++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j3 = 1; j3 <= ent->NbControlPointsListJ(); j3++)
    {
      SW.Send(ent->ControlPointsListValue(i3, j3));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWBSplineSurfaceForm::ConvertToString(ent->SurfaceForm()));

  SW.SendLogical(ent->UClosed());

  SW.SendLogical(ent->VClosed());

  SW.SendLogical(ent->SelfIntersect());

  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("RATIONAL_B_SPLINE_SURFACE");

  SW.OpenSub();
  for (int i8 = 1; i8 <= ent->NbWeightsDataI(); i8++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j8 = 1; j8 <= ent->NbWeightsDataJ(); j8++)
    {
      SW.Send(ent->WeightsDataValue(i8, j8));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());

  SW.StartEntity("SURFACE");
}

void RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface::Share(
  const occ::handle<StepGeom_BezierSurfaceAndRationalBSplineSurface>& ent,
  Interface_EntityIterator&                                           iter) const
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
