

#include <Geom_BSplineSurface.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp_Ax3.hpp>
#include <gp_Cylinder.hpp>
#include <gp_GTrsf.hpp>
#include <gp_Pln.hpp>
#include <gp_Trsf.hpp>
#include <IGESConvGeom.hpp>
#include <IGESData_ToolLocation.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_SplineSurface.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <IGESToBRep_BasicSurface.hpp>
#include <IGESToBRep_CurveAndSurface.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Msg.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <ShapeConstruct_Curve.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>

static bool checkBSplineSurface(IGESToBRep_BasicSurface*                    theSurface,
                                const occ::handle<IGESGeom_BSplineSurface>& theBSplineSurface,
                                NCollection_Array1<double>&                 SUKnots,
                                NCollection_Array1<double>&                 SVKnots,
                                const NCollection_Array2<double>&           SWeights)
{

  if (!theBSplineSurface->IsPolynomial())
  {
    double aMinValue = SWeights.Value(SWeights.LowerRow(), SWeights.LowerCol());
    double aMaxValue = SWeights.Value(SWeights.LowerRow(), SWeights.LowerCol());
    for (int i = SWeights.LowerRow(); i <= SWeights.UpperRow(); i++)
      for (int j = SWeights.LowerCol(); j <= SWeights.UpperCol(); j++)
      {
        if (SWeights.Value(i, j) < aMinValue)
          aMinValue = SWeights.Value(i, j);
        if (SWeights.Value(i, j) > aMaxValue)
          aMaxValue = SWeights.Value(i, j);

        if (aMaxValue - aMinValue > 1000)
        {
          Message_Msg msg1374("IGES_1374");
          theSurface->SendWarning(theBSplineSurface, msg1374);
        }
      }
  }

  bool aResult = true;

  bool aWrongOrder = false;
  int  i;
  for (i = SUKnots.Lower(); (i < SUKnots.Upper()) && (!aWrongOrder); i++)
    if (SUKnots.Value(i + 1) < SUKnots.Value(i))
      aWrongOrder = true;
  for (i = SVKnots.Lower(); (i < SVKnots.Upper()) && (!aWrongOrder); i++)
    if (SVKnots.Value(i + 1) < SVKnots.Value(i))
      aWrongOrder = true;

  if (aWrongOrder)
  {
    Message_Msg msg1373("IGES_1373");
    theSurface->SendFail(theBSplineSurface, msg1373);
    aResult = false;
  }

  if (aResult)
  {
    ShapeConstruct_Curve::FixKnots(SUKnots);
    ShapeConstruct_Curve::FixKnots(SVKnots);
  }

  return aResult;
}

IGESToBRep_BasicSurface::IGESToBRep_BasicSurface()

{
  SetModeTransfer(false);
}

IGESToBRep_BasicSurface::IGESToBRep_BasicSurface(const IGESToBRep_CurveAndSurface& CS)
    : IGESToBRep_CurveAndSurface(CS)
{
}

IGESToBRep_BasicSurface::IGESToBRep_BasicSurface(const double eps,
                                                 const double epsCoeff,
                                                 const double epsGeom,
                                                 const bool   mode,
                                                 const bool   modeapprox,
                                                 const bool   optimized)
    : IGESToBRep_CurveAndSurface(eps, epsCoeff, epsGeom, mode, modeapprox, optimized)
{
}

occ::handle<Geom_Surface> IGESToBRep_BasicSurface::TransferBasicSurface(
  const occ::handle<IGESData_IGESEntity>& start)
{
  occ::handle<Geom_Surface> resurf;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return resurf;
  }

  try
  {
    OCC_CATCH_SIGNALS

    if (start->IsKind(STANDARD_TYPE(IGESGeom_BSplineSurface)))
    {
      DeclareAndCast(IGESGeom_BSplineSurface, st128, start);
      resurf = TransferBSplineSurface(st128);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESGeom_SplineSurface)))
    {
      DeclareAndCast(IGESGeom_SplineSurface, st114, start);
      resurf = TransferSplineSurface(st114);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESSolid_PlaneSurface)))
    {
      DeclareAndCast(IGESSolid_PlaneSurface, st190, start);
      resurf = TransferPlaneSurface(st190);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESSolid_CylindricalSurface)))
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, st192, start);
      resurf = TransferRigthCylindricalSurface(st192);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESSolid_ConicalSurface)))
    {
      DeclareAndCast(IGESSolid_ConicalSurface, st194, start);
      resurf = TransferRigthConicalSurface(st194);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESSolid_SphericalSurface)))
    {
      DeclareAndCast(IGESSolid_SphericalSurface, st196, start);
      resurf = TransferSphericalSurface(st196);
    }
    else if (start->IsKind(STANDARD_TYPE(IGESSolid_ToroidalSurface)))
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, st198, start);
      resurf = TransferToroidalSurface(st198);
    }
    else
    {

      return resurf;
    }
  }
  catch (Standard_Failure const& anException)
  {
#ifdef OCCT_DEBUG
    std::cout << "\n** Exception in IGESToBRep_BasicSurface::TransferBasicSurface : ";
    anException.Print(std::cout);
#endif
    (void)anException;
  }

  if (resurf.IsNull())
  {
  }
  else
    resurf->Scale(gp_Pnt(0, 0, 0), GetUnitFactor());

  return resurf;
}

occ::handle<Geom_Plane> IGESToBRep_BasicSurface::TransferPlaneSurface(
  const occ::handle<IGESSolid_PlaneSurface>& start)
{
  occ::handle<Geom_Plane> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  gp_Pln                          pln;
  bool                            Param = start->IsParametrised();
  occ::handle<IGESGeom_Point>     Point = start->LocationPoint();
  occ::handle<IGESGeom_Direction> Dir   = start->Normal();

  if (Point.IsNull())
  {
    Message_Msg msg174("XSTEP_174");
    SendFail(start, msg174);

    return res;
  }
  if (Dir.IsNull())
  {
    Message_Msg msg1280("IGES_1280");
    SendFail(start, msg1280);

    return res;
  }

  gp_Pnt Pt      = Point->Value();
  gp_Dir Normale = gp_Dir(Dir->Value());
  if (!Param)
  {
    pln = gp_Pln(Pt, Normale);
  }
  else
  {
    occ::handle<IGESGeom_Direction> refdir = start->ReferenceDir();
    gp_Dir                          Dirgp  = gp_Dir(refdir->Value());
    pln                                    = gp_Pln(gp_Ax3(Pt, Normale, Dirgp));
  }

  return new Geom_Plane(pln);
}

occ::handle<Geom_CylindricalSurface> IGESToBRep_BasicSurface::TransferRigthCylindricalSurface(
  const occ::handle<IGESSolid_CylindricalSurface>& start)
{
  occ::handle<Geom_CylindricalSurface> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  bool                            Param  = start->IsParametrised();
  occ::handle<IGESGeom_Point>     Point  = start->LocationPoint();
  occ::handle<IGESGeom_Direction> Axis   = start->Axis();
  double                          radius = start->Radius();

  if (Point.IsNull())
  {
    Message_Msg msg174("XSTEP_174");
    SendFail(start, msg174);

    return res;
  }
  if (Axis.IsNull())
  {
    Message_Msg msg1280("IGES_1280");
    SendFail(start, msg1280);

    return res;
  }
  if (radius < Precision::Confusion())
  {
    return res;
  }

  gp_Pnt Pt = Point->Value();
  gp_Dir ax = gp_Dir(Axis->Value());
  gp_Ax3 ax3;
  if (!Param)
    ax3 = gp_Ax3(Pt, ax);
  else
  {
    occ::handle<IGESGeom_Direction> refdir = start->ReferenceDir();
    gp_Dir                          Dir    = gp_Dir(refdir->Value());
    gp_Dir                          vc     = Dir ^ ax;
    if (vc.XYZ().Modulus() < Precision::Confusion())
    {

      return res;
    }
    ax3 = gp_Ax3(Pt, ax, Dir);
  }
  gp_Cylinder cyl(ax3, radius);
  return new Geom_CylindricalSurface(cyl);
}

occ::handle<Geom_ConicalSurface> IGESToBRep_BasicSurface::TransferRigthConicalSurface(
  const occ::handle<IGESSolid_ConicalSurface>& start)
{
  occ::handle<Geom_ConicalSurface> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  bool                            Param  = start->IsParametrised();
  occ::handle<IGESGeom_Point>     Point  = start->LocationPoint();
  occ::handle<IGESGeom_Direction> Axis   = start->Axis();
  double                          radius = start->Radius();
  double                          angle  = start->SemiAngle() / 180. * M_PI;

  if (Point.IsNull())
  {
    Message_Msg msg174("XSTEP_174");
    SendFail(start, msg174);

    return res;
  }
  if (Axis.IsNull())
  {
    Message_Msg msg1280("IGES_1280");
    SendFail(start, msg1280);

    return res;
  }
  if (angle < Precision::Confusion() || angle > M_PI / 2.)
  {
    return res;
  }
  if (radius < 0)
  {
    return res;
  }
  if (radius < Precision::Confusion())
    radius = 0.;

  gp_Pnt Pt = Point->Value();
  gp_Dir ax = gp_Dir(Axis->Value());
  gp_Ax3 ax3;
  if (!Param)
    ax3 = gp_Ax3(Pt, ax);
  else
  {
    occ::handle<IGESGeom_Direction> refdir = start->ReferenceDir();
    gp_Dir                          Dir    = gp_Dir(refdir->Value());
    gp_Dir                          vc     = Dir ^ ax;
    if (vc.XYZ().Modulus() < Precision::Confusion())
    {

      return res;
    }
    ax3 = gp_Ax3(Pt, ax, Dir);
  }
  return new Geom_ConicalSurface(ax3, angle, radius);
}

occ::handle<Geom_SphericalSurface> IGESToBRep_BasicSurface::TransferSphericalSurface(
  const occ::handle<IGESSolid_SphericalSurface>& start)
{
  occ::handle<Geom_SphericalSurface> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  bool                            Param  = start->IsParametrised();
  occ::handle<IGESGeom_Point>     Point  = start->Center();
  occ::handle<IGESGeom_Direction> Axis   = start->Axis();
  double                          radius = start->Radius();

  if (Point.IsNull())
  {
    Message_Msg msg174("XSTEP_174");
    SendFail(start, msg174);

    return res;
  }
  if (Axis.IsNull())
  {
    Message_Msg msg1280("IGES_1280");
    SendFail(start, msg1280);

    return res;
  }
  if (radius < Precision::Confusion())
  {

    return res;
  }

  gp_Pnt Pt = Point->Value();
  gp_Dir ax = gp_Dir(Axis->Value());
  gp_Ax3 ax3;
  if (!Param)
    ax3 = gp_Ax3(Pt, ax);
  else
  {
    occ::handle<IGESGeom_Direction> refdir = start->ReferenceDir();
    gp_Dir                          Dir    = gp_Dir(refdir->Value());
    gp_Dir                          vc     = Dir ^ ax;
    if (vc.XYZ().Modulus() < Precision::Confusion())
    {

      return res;
    }
    ax3 = gp_Ax3(Pt, ax, Dir);
  }
  return new Geom_SphericalSurface(ax3, radius);
}

occ::handle<Geom_ToroidalSurface> IGESToBRep_BasicSurface::TransferToroidalSurface(
  const occ::handle<IGESSolid_ToroidalSurface>& start)
{
  occ::handle<Geom_ToroidalSurface> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  bool                            Param = start->IsParametrised();
  occ::handle<IGESGeom_Point>     Point = start->Center();
  occ::handle<IGESGeom_Direction> Axis  = start->Axis();
  double                          major = start->MajorRadius();
  double                          minor = start->MinorRadius();

  if (Point.IsNull())
  {
    Message_Msg msg174("XSTEP_174");
    SendFail(start, msg174);

    return res;
  }
  if (Axis.IsNull())
  {
    Message_Msg msg1280("IGES_1280");
    SendFail(start, msg1280);

    return res;
  }
  if (major < Precision::Confusion() || minor < Precision::Confusion())
  {

    return res;
  }

  gp_Pnt Pt = Point->Value();
  gp_Dir ax = gp_Dir(Axis->Value());
  gp_Ax3 ax3;
  if (!Param)
    ax3 = gp_Ax3(Pt, ax);
  else
  {
    occ::handle<IGESGeom_Direction> refdir = start->ReferenceDir();
    gp_Dir                          Dir    = gp_Dir(refdir->Value());
    gp_Dir                          vc     = Dir ^ ax;
    if (vc.XYZ().Modulus() < Precision::Confusion())
    {

      return res;
    }
    ax3 = gp_Ax3(Pt, ax, Dir);
  }
  return new Geom_ToroidalSurface(ax3, major, minor);
}

occ::handle<Geom_BSplineSurface> IGESToBRep_BasicSurface::TransferSplineSurface(
  const occ::handle<IGESGeom_SplineSurface>& start)
{
  occ::handle<Geom_BSplineSurface> resconv;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return resconv;
  }

  double epscoef = GetEpsCoeff();
  double epsgeom = GetEpsGeom();

  int result = IGESConvGeom::SplineSurfaceFromIGES(start, epscoef, epsgeom, resconv);

  switch (result)
  {
    case 5:
    {
      Message_Msg msg1305("IGES_1305");
      SendFail(start, msg1305);
      return resconv;
    }
    case 4:
    {
      Message_Msg msg1190("IGES_1190");
      SendFail(start, msg1190);
      return resconv;
    }

    default:
      break;
  }

  IGESConvGeom::IncreaseSurfaceContinuity(resconv, epsgeom, GetContinuity());
  return resconv;
}

occ::handle<Geom_BSplineSurface> IGESToBRep_BasicSurface::TransferBSplineSurface(
  const occ::handle<IGESGeom_BSplineSurface>& start)
{
  occ::handle<Geom_BSplineSurface> res;
  if (start.IsNull())
  {
    Message_Msg msg1005("IGES_1005");
    SendFail(start, msg1005);
    return res;
  }

  int DegreeU = start->DegreeU();
  int DegreeV = start->DegreeV();
  if ((DegreeU <= 0) || (DegreeU > Geom_BSplineSurface::MaxDegree()) || (DegreeV <= 0)
      || (DegreeV > Geom_BSplineSurface::MaxDegree()))
  {
    Message_Msg msg1310("IGES_1310");
    SendFail(start, msg1310);

    return res;
  }

  int NbPolesU    = start->NbPolesU();
  int newNbPolesU = NbPolesU;
  if (NbPolesU < 2)
  {
    Message_Msg msg1195("IGES_1195");
    SendFail(start, msg1195);

    return res;
  }

  int NbPolesV    = start->NbPolesV();
  int newNbPolesV = NbPolesV;
  if (NbPolesV < 2)
  {
    Message_Msg msg1195("IGES_1195");
    SendFail(start, msg1195);
    return res;
  }

  NCollection_Array2<gp_Pnt> Pole(1, NbPolesU, 1, NbPolesV);
  int                        UIndex = Pole.LowerRow();
  int                        VIndex = Pole.LowerCol();
  int                        i, j;

  if (!GetModeTransfer() && start->HasTransf())
    for (i = 0; i <= start->UpperIndexU(); i++)
    {
      for (j = 0; j <= start->UpperIndexV(); j++)
        Pole.SetValue(UIndex, VIndex++, start->TransformedPole(i, j));
      UIndex++;
      VIndex = Pole.LowerCol();
    }
  else
    for (i = 0; i <= start->UpperIndexU(); i++)
    {
      for (j = 0; j <= start->UpperIndexV(); j++)
        Pole.SetValue(UIndex, VIndex++, start->Pole(i, j));
      UIndex++;
      VIndex = Pole.LowerCol();
    }

  int                        NbUKnots = start->NbKnotsU();
  NCollection_Array1<double> TempUKnot(1, NbUKnots);
  NCollection_Array1<int>    TempUMult(1, NbUKnots);
  TempUMult.Init(1);

  UIndex = TempUKnot.Lower();

  TempUKnot.SetValue(UIndex, start->KnotU(-DegreeU));

  for (i = 1 - DegreeU; i < NbUKnots - DegreeU; i++)
  {

    double UKnot1 = start->KnotU(i);
    double UKnot2 = start->KnotU(i - 1);

    if (std::abs(UKnot1 - UKnot2) <= Epsilon(UKnot2))
      TempUMult.SetValue(UIndex, TempUMult.Value(UIndex) + 1);
    else
      TempUKnot.SetValue(++UIndex, UKnot1);
  }

  NCollection_Array1<double> UKnot(1, UIndex);
  NCollection_Array1<int>    UMult(1, UIndex);

  int SumOfUMult = 0;

  NCollection_Sequence<int> SeqIndexU;
  int                       DelIndexU;
  int                       OldSumOfUMult = 0;
  for (i = 1; i <= UIndex; i++)
  {
    int aMult   = TempUMult.Value(i);
    int maxMult = (i == 1 || i == UIndex ? DegreeU + 1 : DegreeU);
    if (aMult > maxMult)
    {
      Message_Msg msg1200("IGES_1200");
      msg1200.Arg("U");
      msg1200.Arg("U");
      msg1200.Arg("U");
      SendWarning(start, msg1200);
      for (DelIndexU = OldSumOfUMult + 1; aMult > maxMult; DelIndexU++, aMult--)
      {
        newNbPolesU--;
        SeqIndexU.Append(DelIndexU);
      }
    }
    OldSumOfUMult += TempUMult.Value(i);
    UKnot.SetValue(i, TempUKnot.Value(i));
    UMult.SetValue(i, aMult);
    SumOfUMult += aMult;
  }

  if (SumOfUMult != newNbPolesU + DegreeU + 1)
  {
    Message_Msg msg1210("IGES_1210");
    msg1210.Arg("U");
    msg1210.Arg("U");
    SendWarning(start, msg1210);
  }

  int                        NbVKnots = start->NbKnotsV();
  NCollection_Array1<double> TempVKnot(1, NbVKnots);
  NCollection_Array1<int>    TempVMult(1, NbVKnots);
  TempVMult.Init(1);

  VIndex = TempVKnot.Lower();

  TempVKnot.SetValue(VIndex, start->KnotV(-DegreeV));

  for (i = 1 - DegreeV; i < NbVKnots - DegreeV; i++)
  {

    double VKnot1 = start->KnotV(i);
    double VKnot2 = start->KnotV(i - 1);

    if (std::abs(VKnot1 - VKnot2) <= Epsilon(VKnot2))
      TempVMult.SetValue(VIndex, TempVMult.Value(VIndex) + 1);
    else
      TempVKnot.SetValue(++VIndex, VKnot1);
  }

  NCollection_Array1<double> VKnot(1, VIndex);
  NCollection_Array1<int>    VMult(1, VIndex);

  int SumOfVMult = 0;

  NCollection_Sequence<int> SeqIndexV;
  int                       DelIndexV;
  int                       OldSumOfVMult = 0;
  for (i = 1; i <= VIndex; i++)
  {
    int aMult   = TempVMult.Value(i);
    int maxMult = (i == 1 || i == VIndex ? DegreeV + 1 : DegreeV);
    if (aMult > maxMult)
    {
      Message_Msg msg1200("IGES_1200");
      msg1200.Arg("V");
      msg1200.Arg("V");
      msg1200.Arg("V");
      SendWarning(start, msg1200);

      for (DelIndexV = OldSumOfVMult + 1; aMult > maxMult; DelIndexV++, aMult--)
      {
        newNbPolesV--;
        SeqIndexV.Append(DelIndexV);
      }
    }
    OldSumOfVMult += TempVMult.Value(i);
    VKnot.SetValue(i, TempVKnot.Value(i));
    VMult.SetValue(i, aMult);
    SumOfVMult += aMult;
  }

  if (SumOfVMult != newNbPolesV + DegreeV + 1)
  {
    Message_Msg msg1210("IGES_1210");
    msg1210.Arg("V");
    msg1210.Arg("V");
    SendWarning(start, msg1210);
  }

  NCollection_Array2<gp_Pnt> Poles(1, newNbPolesU, 1, newNbPolesV);
  NCollection_Sequence<int>  PoleUInd;
  NCollection_Sequence<int>  PoleVInd;
  for (i = 1; i <= NbPolesU; i++)
    PoleUInd.Append(i);
  for (i = 1; i <= NbPolesV; i++)
    PoleVInd.Append(i);
  UIndex = Poles.LowerRow();
  VIndex = Poles.LowerCol();

  if ((newNbPolesU < NbPolesU) || (newNbPolesV < NbPolesV))
  {
    if (newNbPolesU < NbPolesU)
    {
      int Offset = 0;
      for (int itab = 1; itab <= SeqIndexU.Length(); itab++)
      {
        DelIndexU = SeqIndexU.Value(itab) - Offset;
        PoleUInd.Remove(DelIndexU);
        Offset++;
      }
    }
    if (newNbPolesV < NbPolesV)
    {
      int Offset = 0;
      for (int itab = 1; itab <= SeqIndexV.Length(); itab++)
      {
        DelIndexV = SeqIndexV.Value(itab) - Offset;
        PoleVInd.Remove(DelIndexV);
        Offset++;
      }
    }
    int nbUseq = PoleUInd.Length();
    int nbVseq = PoleVInd.Length();
    if ((nbUseq == newNbPolesU) && (nbVseq == newNbPolesV))
    {
      for (i = 1; i <= newNbPolesU; i++)
      {
        for (j = 1; j <= newNbPolesV; j++)
          Poles.SetValue(UIndex, VIndex++, Pole.Value(PoleUInd.Value(i), PoleVInd.Value(j)));
        UIndex++;
        VIndex = Poles.LowerCol();
      }
    }
    else
    {
      Message_Msg msg1175("IGES_1175");
      SendWarning(start, msg1175);
    }
  }

  else
  {
    for (i = 1; i <= newNbPolesU; i++)
    {
      for (j = 1; j <= newNbPolesV; j++)
        Poles.SetValue(UIndex, VIndex++, Pole.Value(i, j));
      UIndex++;
      VIndex = Poles.LowerCol();
    }
  }

  if (!GetModeTransfer() && start->HasTransf())
  {
    gp_GTrsf GBSplTrsf(start->CompoundLocation());
    gp_Trsf  BSplTrsf;
    if (IGESData_ToolLocation::ConvertLocation(GetEpsilon(), GBSplTrsf, BSplTrsf))
      for (i = Poles.LowerRow(); i <= Poles.UpperRow(); i++)
        for (j = Poles.LowerCol(); j <= Poles.UpperCol(); j++)
          Poles.SetValue(i, j, Poles.Value(i, j).Transformed(BSplTrsf));
    else
    {
      Message_Msg msg1035("IGES_1035");
      SendWarning(start, msg1035);
    }
  }

  if (start->IsPolynomial())
  {

    NCollection_Array2<double> Weight(1, 1, 1, 1);
    if (!checkBSplineSurface(this, start, UKnot, VKnot, Weight))
      return res;
    res = new Geom_BSplineSurface(Poles, UKnot, VKnot, UMult, VMult, DegreeU, DegreeV);
  }

  else
  {
    NCollection_Array2<double> PoleWeight(1, NbPolesU, 1, NbPolesV);
    bool                       polynomial      = true;
    double                     WeightReference = start->Weight(0, 0);
    int                        WeightRow       = PoleWeight.LowerRow();
    int                        WeightCol       = PoleWeight.LowerCol();

    for (i = 0; i <= start->UpperIndexU(); i++)
    {
      for (j = 0; j <= start->UpperIndexV(); j++)
      {
        polynomial = (std::abs(start->Weight(i, j) - WeightReference) <= Epsilon(WeightReference))
                     && polynomial;

        double weight = start->Weight(i, j);
        if (weight < Precision::PConfusion())
        {
          Message_Msg msg1215("IGES_1215");
          SendFail(start, msg1215);
          return res;
        }
        PoleWeight.SetValue(WeightRow, WeightCol++, weight);
      }
      WeightRow++;
      WeightCol = PoleWeight.LowerCol();
    }
    if (polynomial)
    {
      Message_Msg msg1220("IGES_1220");
      const char* surface("surface");
      msg1220.Arg(surface);
      SendWarning(start, msg1220);
    }

    NCollection_Array2<double> Weight(1, newNbPolesU, 1, newNbPolesV);
    UIndex = Weight.LowerRow();
    VIndex = Weight.LowerCol();
    if ((newNbPolesU < NbPolesU) || (newNbPolesV < NbPolesV))
    {

      for (i = 1; i <= newNbPolesU; i++)
      {
        for (j = 1; j <= newNbPolesV; j++)
          Weight.SetValue(UIndex, VIndex++, PoleWeight.Value(PoleUInd.Value(i), PoleVInd.Value(j)));
        UIndex++;
        VIndex = Poles.LowerCol();
      }
    }
    else
    {
      for (i = 1; i <= newNbPolesU; i++)
      {
        for (j = 1; j <= newNbPolesV; j++)
          Weight.SetValue(UIndex, VIndex++, PoleWeight.Value(i, j));
        UIndex++;
        VIndex = Poles.LowerCol();
      }
    }

    if (!checkBSplineSurface(this, start, UKnot, VKnot, Weight))
      return res;
    res = new Geom_BSplineSurface(Poles, Weight, UKnot, VKnot, UMult, VMult, DegreeU, DegreeV);
  }

  int icont = GetContinuity();

  i              = res->LastUKnotIndex();
  int FirstIndex = res->FirstUKnotIndex();
  while (--i >= FirstIndex + 1)
  {
    if (icont >= 2)
    {
      if (!res->RemoveUKnot(i, DegreeU - 2, GetEpsGeom()))
      {

        res->RemoveUKnot(i, DegreeU - 1, GetEpsGeom());
      }
      else
        res->RemoveUKnot(i, DegreeU - 1, GetEpsGeom());
    }
  }

  i          = res->LastVKnotIndex();
  FirstIndex = res->FirstVKnotIndex();
  while (--i >= FirstIndex + 1)
  {
    if (icont >= 2)
    {
      if (!res->RemoveVKnot(i, DegreeV - 2, GetEpsGeom()))
      {

        res->RemoveVKnot(i, DegreeV - 1, GetEpsGeom());
      }
      else
        res->RemoveVKnot(i, DegreeV - 1, GetEpsGeom());
    }
  }

  bool isUPeriodic = (start->IsClosedU() && (start->IsPeriodicU() || res->IsUClosed()));
  bool isVPeriodic = (start->IsClosedV() && (start->IsPeriodicV() || res->IsVClosed()));

  if (isUPeriodic || isVPeriodic)
  {
    occ::handle<Geom_BSplineSurface> periodicSurf =
      occ::down_cast<Geom_BSplineSurface>(ShapeAlgo::AlgoContainer()->ConvertToPeriodic(res));
    if (!periodicSurf.IsNull())
    {

      Message_Msg msg1221("IGES_1221");
      SendWarning(start, msg1221);
      res = periodicSurf;
    }
  }
  return res;
}
