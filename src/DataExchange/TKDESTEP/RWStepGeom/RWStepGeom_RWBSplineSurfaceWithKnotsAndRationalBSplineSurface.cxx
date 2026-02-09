

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include "RWStepGeom_RWBSplineSurfaceWithKnots.hpp"
#include "RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp"
#include "RWStepGeom_RWRationalBSplineSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepGeom_KnotType.hpp>
#include <StepGeom_RationalBSplineSurface.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include "RWStepGeom_RWBSplineSurfaceForm.hpp"
#include "RWStepGeom_RWKnotType.hpp"

RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::
  RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface() = default;

void RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                   data,
  const int                                                                     num0,
  occ::handle<Interface_Check>&                                                 ach,
  const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>& ent) const
{

  int num = 0;
  data->NamedForComplex("BOUNDED_SURFACE", "BNDSRF", num0, num, ach);

  data->NamedForComplex("B_SPLINE_SURFACE", "BSPSR", num0, num, ach);

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
      int nsi3temp;
      if (data->ReadSubList(nsub3, i3, "sub-part(control_points_list)", ach, nsi3temp))
      {
        int nsi3 = data->ParamNumber(nsub3, i3);
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

  data->NamedForComplex("B_SPLINE_SURFACE_WITH_KNOTS", "BSSWK", num0, num, ach);

  if (!data->CheckNbParams(num, 5, ach, "b_spline_surface_with_knots"))
    return;

  occ::handle<NCollection_HArray1<int>> aUMultiplicities;
  int                                   aUMultiplicitiesItem;
  int                                   nsub8;
  if (data->ReadSubList(num, 1, "u_multiplicities", ach, nsub8))
  {
    int nb8          = data->NbParams(nsub8);
    aUMultiplicities = new NCollection_HArray1<int>(1, nb8);
    for (int i8 = 1; i8 <= nb8; i8++)
    {

      if (data->ReadInteger(nsub8, i8, "u_multiplicities", ach, aUMultiplicitiesItem))
        aUMultiplicities->SetValue(i8, aUMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<int>> aVMultiplicities;
  int                                   aVMultiplicitiesItem;
  int                                   nsub9;
  if (data->ReadSubList(num, 2, "v_multiplicities", ach, nsub9))
  {
    int nb9          = data->NbParams(nsub9);
    aVMultiplicities = new NCollection_HArray1<int>(1, nb9);
    for (int i9 = 1; i9 <= nb9; i9++)
    {

      if (data->ReadInteger(nsub9, i9, "v_multiplicities", ach, aVMultiplicitiesItem))
        aVMultiplicities->SetValue(i9, aVMultiplicitiesItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aUKnots;
  double                                   aUKnotsItem;
  int                                      nsub10;
  if (data->ReadSubList(num, 3, "u_knots", ach, nsub10))
  {
    int nb10 = data->NbParams(nsub10);
    aUKnots  = new NCollection_HArray1<double>(1, nb10);
    for (int i10 = 1; i10 <= nb10; i10++)
    {

      if (data->ReadReal(nsub10, i10, "u_knots", ach, aUKnotsItem))
        aUKnots->SetValue(i10, aUKnotsItem);
    }
  }

  occ::handle<NCollection_HArray1<double>> aVKnots;
  double                                   aVKnotsItem;
  int                                      nsub11;
  if (data->ReadSubList(num, 4, "v_knots", ach, nsub11))
  {
    int nb11 = data->NbParams(nsub11);
    aVKnots  = new NCollection_HArray1<double>(1, nb11);
    for (int i11 = 1; i11 <= nb11; i11++)
    {

      if (data->ReadReal(nsub11, i11, "v_knots", ach, aVKnotsItem))
        aVKnots->SetValue(i11, aVKnotsItem);
    }
  }

  StepGeom_KnotType aKnotSpec = StepGeom_ktUniformKnots;
  if (data->ParamType(num, 5) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 5);
    if (!RWStepGeom_RWKnotType::ConvertToEnum(text, aKnotSpec))
    {
      ach->AddFail("Enumeration knot_type has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #5 (knot_spec) is not an enumeration");

  data->NamedForComplex("GEOMETRIC_REPRESENTATION_ITEM", "GMRPIT", num0, num, ach);

  data->NamedForComplex("RATIONAL_B_SPLINE_SURFACE", "RBSS", num0, num, ach);

  if (!data->CheckNbParams(num, 1, ach, "rational_b_spline_surface"))
    return;

  occ::handle<NCollection_HArray2<double>> aWeightsData;
  double                                   aWeightsDataItem;
  int                                      nsub13;
  if (data->ReadSubList(num, 1, "weights_data", ach, nsub13))
  {
    int nbi13    = data->NbParams(nsub13);
    int nbj13    = data->NbParams(data->ParamNumber(nsub13, 1));
    aWeightsData = new NCollection_HArray2<double>(1, nbi13, 1, nbj13);
    for (int i13 = 1; i13 <= nbi13; i13++)
    {
      int nsi13temp;
      if (data->ReadSubList(nsub13, i13, "sub-part(weights_data)", ach, nsi13temp))
      {
        int nsi13 = data->ParamNumber(nsub13, i13);
        for (int j13 = 1; j13 <= nbj13; j13++)
        {

          if (data->ReadReal(nsi13, j13, "weights_data", ach, aWeightsDataItem))
            aWeightsData->SetValue(i13, j13, aWeightsDataItem);
        }
      }
    }
  }

  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);

  occ::handle<TCollection_HAsciiString> aName;

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
  {
    aName = new TCollection_HAsciiString("");
  }
  else
  {

    data->ReadString(num, 1, "name", ach, aName);
  }

  data->NamedForComplex("SURFACE", "SRFC", num0, num, ach);

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
            aKnotSpec,
            aWeightsData);
}

void RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::WriteStep(
  StepData_StepWriter&                                                          SW,
  const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>& ent) const
{

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

  SW.StartEntity("B_SPLINE_SURFACE_WITH_KNOTS");

  SW.OpenSub();
  for (int i8 = 1; i8 <= ent->NbUMultiplicities(); i8++)
  {
    SW.Send(ent->UMultiplicitiesValue(i8));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i9 = 1; i9 <= ent->NbVMultiplicities(); i9++)
  {
    SW.Send(ent->VMultiplicitiesValue(i9));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i10 = 1; i10 <= ent->NbUKnots(); i10++)
  {
    SW.Send(ent->UKnotsValue(i10));
  }
  SW.CloseSub();

  SW.OpenSub();
  for (int i11 = 1; i11 <= ent->NbVKnots(); i11++)
  {
    SW.Send(ent->VKnotsValue(i11));
  }
  SW.CloseSub();

  SW.SendEnum(RWStepGeom_RWKnotType::ConvertToString(ent->KnotSpec()));

  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("RATIONAL_B_SPLINE_SURFACE");

  SW.OpenSub();
  for (int i13 = 1; i13 <= ent->NbWeightsDataI(); i13++)
  {
    SW.NewLine(false);
    SW.OpenSub();
    for (int j13 = 1; j13 <= ent->NbWeightsDataJ(); j13++)
    {
      SW.Send(ent->WeightsDataValue(i13, j13));
      SW.JoinLast(false);
    }
    SW.CloseSub();
  }
  SW.CloseSub();

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());

  SW.StartEntity("SURFACE");
}

void RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::Share(
  const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>& ent,
  Interface_EntityIterator&                                                     iter) const
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

void RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface::Check(
  const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>& ent,
  const Interface_ShareTool&                                                    aShto,
  occ::handle<Interface_Check>&                                                 ach) const
{
  const occ::handle<StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface>& aRationalBSS = ent;
  occ::handle<StepGeom_BSplineSurfaceWithKnots> aBSSWK = aRationalBSS->BSplineSurfaceWithKnots();
  RWStepGeom_RWBSplineSurfaceWithKnots          t1;
  t1.Check(aBSSWK, aShto, ach);
  occ::handle<StepGeom_RationalBSplineSurface> aRBSS = aRationalBSS->RationalBSplineSurface();
  RWStepGeom_RWRationalBSplineSurface          t2;
  t2.Check(aRBSS, aShto, ach);
}
