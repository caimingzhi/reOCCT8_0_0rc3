#ifndef OCCT_DEBUG
  #define No_Standard_RangeError
  #define No_Standard_OutOfRange
#endif

#include <IntImp_ComputeTangence.hpp>
#include <math_FunctionSetRoot.hpp>
#include <math_Vector.hpp>
#include <IntImp_ConstIsoparametric.hpp>
#include <Standard_ConstructionError.hpp>
#include <Precision.hpp>

IntImp_Int2S::IntImp_Int2S(const ThePSurface& surf1,
                           const ThePSurface& surf2,
                           const double       TolTangency)
    : done(true),
      empty(true),
      tangent(false),
      myZerParFunc(surf1, surf2),
      tol(TolTangency * TolTangency)
{
  ua0 = ThePSurfaceTool::FirstUParameter(surf1);
  va0 = ThePSurfaceTool::FirstVParameter(surf1);
  ua1 = ThePSurfaceTool::LastUParameter(surf1);
  va1 = ThePSurfaceTool::LastVParameter(surf1);

  ub0 = ThePSurfaceTool::FirstUParameter(surf2);
  vb0 = ThePSurfaceTool::FirstVParameter(surf2);
  ub1 = ThePSurfaceTool::LastUParameter(surf2);
  vb1 = ThePSurfaceTool::LastVParameter(surf2);

  ures1 = ThePSurfaceTool::UResolution(surf1, Precision::Confusion());
  vres1 = ThePSurfaceTool::VResolution(surf1, Precision::Confusion());

  ures2 = ThePSurfaceTool::UResolution(surf2, Precision::Confusion());
  vres2 = ThePSurfaceTool::VResolution(surf2, Precision::Confusion());
}

IntImp_Int2S::IntImp_Int2S(const NCollection_Array1<double>& Param,
                           const ThePSurface&                surf1,
                           const ThePSurface&                surf2,
                           const double                      TolTangency)
    : done(true),
      empty(true),
      myZerParFunc(surf1, surf2),
      tol(TolTangency * TolTangency)
{
  math_FunctionSetRoot Rsnld(myZerParFunc, 15);
  ua0 = ThePSurfaceTool::FirstUParameter(surf1);
  va0 = ThePSurfaceTool::FirstVParameter(surf1);
  ua1 = ThePSurfaceTool::LastUParameter(surf1);
  va1 = ThePSurfaceTool::LastVParameter(surf1);

  ub0 = ThePSurfaceTool::FirstUParameter(surf2);
  vb0 = ThePSurfaceTool::FirstVParameter(surf2);
  ub1 = ThePSurfaceTool::LastUParameter(surf2);
  vb1 = ThePSurfaceTool::LastVParameter(surf2);

  ures1 = ThePSurfaceTool::UResolution(surf1, Precision::Confusion());
  vres1 = ThePSurfaceTool::VResolution(surf1, Precision::Confusion());

  ures2 = ThePSurfaceTool::UResolution(surf2, Precision::Confusion());
  vres2 = ThePSurfaceTool::VResolution(surf2, Precision::Confusion());
  Perform(Param, Rsnld);
}

IntImp_ConstIsoparametric IntImp_Int2S::Perform(const NCollection_Array1<double>& Param,
                                                math_FunctionSetRoot&             Rsnld,
                                                const IntImp_ConstIsoparametric   ChoixIso)
{
  double      BornInfBuf[3] = {}, BornSupBuf[3] = {}, ToleranceBuf[3] = {}, UVapBuf[3] = {};
  double      UvresBuf[4] = {};
  math_Vector BornInf(BornInfBuf, 1, 3), BornSup(BornSupBuf, 1, 3), Tolerance(ToleranceBuf, 1, 3),
    UVap(UVapBuf, 1, 3);
  NCollection_Array1<double> Uvres(UvresBuf[0], 1, 4);

  IntImp_ConstIsoparametric BestChoix;

  myZerParFunc.ComputeParameters(ChoixIso, Param, UVap, BornInf, BornSup, Tolerance);
  Rsnld.SetTolerance(Tolerance);
  Rsnld.Perform(myZerParFunc, UVap, BornInf, BornSup);
  BestChoix = ChoixIso;
  if (Rsnld.IsDone())
  {
    if (std::abs(myZerParFunc.Root()) <= tol)
    {

      Rsnld.Root(UVap);
      empty   = false;
      tangent = myZerParFunc.IsTangent(UVap, Uvres, BestChoix);
      pint.SetValue(myZerParFunc.Point(), Uvres(1), Uvres(2), Uvres(3), Uvres(4));
      if (!tangent)
      {
        d3d  = myZerParFunc.Direction();
        d2d1 = myZerParFunc.DirectionOnS1();
        d2d2 = myZerParFunc.DirectionOnS2();
      }
    }
    else
    {
      empty = true;
    }
  }
  else
  {
    empty = true;
  }
  return BestChoix;
}

IntImp_ConstIsoparametric IntImp_Int2S::Perform(const NCollection_Array1<double>& Param,
                                                math_FunctionSetRoot&             Rsnld)
{
  gp_Vec                     DPUV[4];
  gp_Pnt                     P1, P2;
  double                     Epsuv[4];
  double                     DuvBuf[4] = {};
  NCollection_Array1<double> Duv(DuvBuf[0], 1, 4);
  double                     UVd[4], UVf[4];
  IntImp_ConstIsoparametric  ChoixIso[4];
  IntImp_ConstIsoparametric  BestChoix = ChoixRef(0);
  const ThePSurface&         Caro1     = myZerParFunc.AuxillarSurface1();
  const ThePSurface&         Caro2     = myZerParFunc.AuxillarSurface2();

  ThePSurfaceTool::D1(Caro1, Param(1), Param(2), P1, DPUV[0], DPUV[1]);
  ThePSurfaceTool::D1(Caro2, Param(3), Param(4), P2, DPUV[2], DPUV[3]);

  Epsuv[0] = ThePSurfaceTool::UResolution(Caro1, Precision::Confusion());
  Epsuv[1] = ThePSurfaceTool::VResolution(Caro1, Precision::Confusion());

  Epsuv[2] = ThePSurfaceTool::UResolution(Caro2, Precision::Confusion());
  Epsuv[3] = ThePSurfaceTool::VResolution(Caro2, Precision::Confusion());

  for (int j = 0; j <= 3; j++)
    UVd[j] = Param(j + 1);

  empty = true;

  bool Tangent = IntImp_ComputeTangence(DPUV, Epsuv, UVd, ChoixIso);
  if (Tangent)
    return BestChoix;

  int                       i            = 0;
  IntImp_ConstIsoparametric CurrentChoix = BestChoix;

  while (empty && i <= 3)
  {
    CurrentChoix = Perform(Param, Rsnld, ChoixIso[i]);
    if (!empty)
    {
      BestChoix = CurrentChoix;
    }
    i++;
  }
  if (!empty)
  {
    pint.Parameters(Duv(1), Duv(2), Duv(3), Duv(4));

    UVd[0] = ua0;
    UVd[1] = va0;
    UVf[0] = ua1;
    UVf[1] = va1;

    UVd[2] = ub0;
    UVd[3] = vb0;
    UVf[2] = ub1;
    UVf[3] = vb1;

    int Nc, Iiso;
    if (Duv(1) <= UVd[0] - Epsuv[0])
    {
      Duv(1) = UVd[0];
      Nc     = 0;
      Iiso   = 0;
    }
    else if (Duv(1) >= UVf[0] + Epsuv[0])
    {
      Duv(1) = UVf[0];
      Nc     = 0;
      Iiso   = 0;
    }
    else if (Duv(2) <= UVd[1] - Epsuv[1])
    {
      Duv(2) = UVd[1];
      Nc     = 0;
      Iiso   = 1;
    }
    else if (Duv(2) >= UVf[1] + Epsuv[1])
    {
      Duv(2) = UVf[1];
      Nc     = 0;
      Iiso   = 1;
    }
    else if (Duv(3) <= UVd[2] - Epsuv[2])
    {
      Duv(3) = UVd[2];
      Nc     = 2;
      Iiso   = 2;
    }
    else if (Duv(3) >= UVf[2] + Epsuv[2])
    {
      Duv(3) = UVf[2];
      Nc     = 2;
      Iiso   = 2;
    }
    else if (Duv(4) <= UVd[3] - Epsuv[3])
    {
      Duv(4) = UVd[3];
      Nc     = 2;
      Iiso   = 3;
    }
    else if (Duv(4) >= UVf[3] + Epsuv[3])
    {
      Duv(4) = UVf[3];
      Nc     = 2;
      Iiso   = 3;
    }
    else
      return BestChoix;
    empty     = true;
    BestChoix = ChoixRef(Iiso);
    BestChoix = Perform(Duv, Rsnld, BestChoix);
    if (!empty)
    {

      Nc = 3 - Nc;
      if (Duv(Nc) <= UVd[Nc - 1] - Epsuv[Nc - 1])
        Duv(Nc) = UVd[Nc - 1];
      else if (Duv(Nc) >= UVf[Nc - 1] + Epsuv[Nc - 1])
        Duv(Nc) = UVf[Nc - 1];
      else if (Duv(Nc + 1) <= UVd[Nc])
      {
        Nc      = Nc + 1;
        Duv(Nc) = UVd[Nc - 1];
      }
      else if (Duv(Nc + 1) >= UVf[Nc])
      {
        Nc      = Nc + 1;
        Duv(Nc) = UVf[Nc - 1];
      }
      else
        return BestChoix;

      empty = true;

      if (Nc == 4)
        Nc = 0;

      BestChoix = ChoixRef(Nc);
      BestChoix = Perform(Duv, Rsnld, BestChoix);
    }
  }
  return BestChoix;
}
