#include <GeomAbs_SurfaceType.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>
#include <math_FunctionSetRoot.hpp>

static bool IsSingular(const gp_Vec& theDU,
                       const gp_Vec& theDV,
                       const double  theSqLinTol,
                       const double  theAngTol)
{
  gp_Vec aDU(theDU), aDV(theDV);

  const double aSqMagnDU = aDU.SquareMagnitude(), aSqMagnDV = aDV.SquareMagnitude();

  if (aSqMagnDU < theSqLinTol)
    return true;

  aDU.Divide(sqrt(aSqMagnDU));

  if (aSqMagnDV < theSqLinTol)
    return true;

  aDV.Divide(sqrt(aSqMagnDV));

  if (aDU.Crossed(aDV).SquareMagnitude() < theAngTol * theAngTol)
    return true;

  return false;
}

static bool SingularProcessing(const gp_Vec& theDU,
                               const gp_Vec& theDV,
                               const bool    theIsTo3DTgCompute,
                               const double  theLinTol,
                               const double  theAngTol,
                               gp_Vec&       theTg3D,
                               gp_Vec2d&     theTg2D)
{

  const double aSQTan = theTg3D.SquareMagnitude();

  const double aSqMagnDU = theDU.SquareMagnitude(), aSqMagnDV = theDV.SquareMagnitude();

  if ((aSqMagnDU < theLinTol) && (aSqMagnDV < theLinTol))
  {

    return false;
  }

  if (aSqMagnDU < theLinTol)
  {

    if (theIsTo3DTgCompute)
    {

      const double aTgMagn = 1.0;

      const double aNorm = sqrt(aSqMagnDV);
      theTg3D            = theDV.Divided(aNorm);
      theTg2D.SetCoord(0.0, aTgMagn / aNorm);
    }
    else
    {

      if (theDV.Crossed(theTg3D).SquareMagnitude() < theAngTol * theAngTol * aSqMagnDV * aSQTan)
      {

        const double aDP = theTg3D.Dot(theDV);
        theTg2D.SetCoord(0.0, std::copysign(sqrt(aSQTan / aSqMagnDV), aDP));
      }
      else
      {

        return false;
      }
    }

    return true;
  }

  if (aSqMagnDV < theLinTol)
  {

    if (theIsTo3DTgCompute)
    {

      const double aTgMagn = 1.0;

      const double aNorm = sqrt(aSqMagnDU);
      theTg3D            = theDU.Divided(aNorm);
      theTg2D.SetCoord(aTgMagn / aNorm, 0.0);
    }
    else
    {

      if (theDU.Crossed(theTg3D).SquareMagnitude() < theAngTol * theAngTol * aSqMagnDU * aSQTan)
      {

        const double aDP = theTg3D.Dot(theDU);
        theTg2D.SetCoord(std::copysign(sqrt(aSQTan / aSqMagnDU), aDP), 0.0);
      }
      else
      {

        return false;
      }
    }

    return true;
  }

  const double aLenU = sqrt(aSqMagnDU), aLenV = sqrt(aSqMagnDV);

  const double aLenSum = aLenU + aLenV;

  if (theDV.Dot(theDU) > 0.0)
  {

    if (theIsTo3DTgCompute)
    {
      theTg2D.SetCoord(1.0 / aLenSum, 1.0 / aLenSum);
      theTg3D = theDU * theTg2D.X() + theDV * theTg2D.Y();
    }
    else
    {

      if (theDU.Crossed(theTg3D).SquareMagnitude() < theAngTol * theAngTol * aSqMagnDU * aSQTan)
      {

        const double aDP    = theTg3D.Dot(theDU);
        const double aLenTg = std::copysign(sqrt(aSQTan), aDP);
        theTg2D.SetCoord(aLenTg / aLenSum, aLenTg / aLenSum);
      }
      else
      {

        return false;
      }
    }
  }
  else
  {

    if (theIsTo3DTgCompute)
    {

      theTg2D.SetCoord(1.0 / aLenSum, -1.0 / aLenSum);
      theTg3D = theDU * theTg2D.X() + theDV * theTg2D.Y();
    }
    else
    {

      if (theDU.Crossed(theTg3D).SquareMagnitude() < theAngTol * theAngTol * aSqMagnDU * aSQTan)
      {

        const double aDP    = theTg3D.Dot(theDU);
        const double aLenTg = std::copysign(sqrt(aSQTan), aDP);
        theTg2D.SetCoord(aLenTg / aLenSum, -aLenTg / aLenSum);
      }
      else
      {

        return false;
      }
    }
  }

  return true;
}

static bool NonSingularProcessing(const gp_Vec& theDU,
                                  const gp_Vec& theDV,
                                  const gp_Vec& theTg3D,
                                  const double  theLinTol,
                                  const double  theAngTol,
                                  gp_Vec2d&     theTg2D)
{
  const gp_Vec aNormal = theDU.Crossed(theDV);
  const double aSQMagn = aNormal.SquareMagnitude();

  if (IsSingular(theDU, theDV, theLinTol, theAngTol))
  {
    gp_Vec aTg(theTg3D);
    return SingularProcessing(theDU, theDV, false, theLinTol, theAngTol, aTg, theTg2D);
  }

  const gp_Vec aTgU(theTg3D.Crossed(theDU)), aTgV(theTg3D.Crossed(theDV));
  const double aDeltaU = aTgV.SquareMagnitude() / aSQMagn;
  const double aDeltaV = aTgU.SquareMagnitude() / aSQMagn;

  theTg2D.SetCoord(std::copysign(sqrt(aDeltaU), aTgV.Dot(aNormal)),
                   -std::copysign(sqrt(aDeltaV), aTgU.Dot(aNormal)));

  return true;
}

ApproxInt_ImpPrmSvSurfaces::ApproxInt_ImpPrmSvSurfaces(const TheISurface& ISurf,
                                                       const ThePSurface& PSurf)
    : MyIsTangent(false),
      MyHasBeenComputed(false),
      MyIsTangentbis(false),
      MyHasBeenComputedbis(false),
      MyImplicitFirst(true),
      MyZerImpFunc(PSurf, ISurf)
{
  SetUseSolver(true);
}

ApproxInt_ImpPrmSvSurfaces::ApproxInt_ImpPrmSvSurfaces(const ThePSurface& PSurf,
                                                       const TheISurface& ISurf)
    : MyIsTangent(false),
      MyHasBeenComputed(false),
      MyIsTangentbis(false),
      MyHasBeenComputedbis(false),
      MyImplicitFirst(false),
      MyZerImpFunc(PSurf, ISurf)
{
  SetUseSolver(true);
}

void ApproxInt_ImpPrmSvSurfaces::Pnt(const double u1,
                                     const double v1,
                                     const double u2,
                                     const double v2,
                                     gp_Pnt&      P)
{
  gp_Pnt   aP;
  gp_Vec   aT;
  gp_Vec2d aTS1, aTS2;
  double   tu1 = u1;
  double   tu2 = u2;
  double   tv1 = v1;
  double   tv2 = v2;
  this->Compute(tu1, tv1, tu2, tv2, aP, aT, aTS1, aTS2);
  P = MyPnt;
}

bool ApproxInt_ImpPrmSvSurfaces::Tangency(const double u1,
                                          const double v1,
                                          const double u2,
                                          const double v2,
                                          gp_Vec&      T)
{
  gp_Pnt   aP;
  gp_Vec   aT;
  gp_Vec2d aTS1, aTS2;
  double   tu1 = u1;
  double   tu2 = u2;
  double   tv1 = v1;
  double   tv2 = v2;
  bool     t   = this->Compute(tu1, tv1, tu2, tv2, aP, aT, aTS1, aTS2);
  T            = MyTg;
  return (t);
}

bool ApproxInt_ImpPrmSvSurfaces::TangencyOnSurf1(const double u1,
                                                 const double v1,
                                                 const double u2,
                                                 const double v2,
                                                 gp_Vec2d&    T)
{
  gp_Pnt   aP;
  gp_Vec   aT;
  gp_Vec2d aTS1, aTS2;
  double   tu1 = u1;
  double   tu2 = u2;
  double   tv1 = v1;
  double   tv2 = v2;
  bool     t   = this->Compute(tu1, tv1, tu2, tv2, aP, aT, aTS1, aTS2);
  T            = MyTguv1;
  return (t);
}

bool ApproxInt_ImpPrmSvSurfaces::TangencyOnSurf2(const double u1,
                                                 const double v1,
                                                 const double u2,
                                                 const double v2,
                                                 gp_Vec2d&    T)
{
  gp_Pnt   aP;
  gp_Vec   aT;
  gp_Vec2d aTS1, aTS2;
  double   tu1 = u1;
  double   tu2 = u2;
  double   tv1 = v1;
  double   tv2 = v2;
  bool     t   = this->Compute(tu1, tv1, tu2, tv2, aP, aT, aTS1, aTS2);
  T            = MyTguv2;
  return (t);
}

bool ApproxInt_ImpPrmSvSurfaces::Compute(double&   u1,
                                         double&   v1,
                                         double&   u2,
                                         double&   v2,
                                         gp_Pnt&   P,
                                         gp_Vec&   Tg,
                                         gp_Vec2d& Tguv1,
                                         gp_Vec2d& Tguv2)
{
  const IntSurf_Quadric& aQSurf  = MyZerImpFunc.ISurface();
  const ThePSurface&     aPSurf  = MyZerImpFunc.PSurface();
  gp_Vec2d&              aQuadTg = MyImplicitFirst ? Tguv1 : Tguv2;
  gp_Vec2d&              aPrmTg  = MyImplicitFirst ? Tguv2 : Tguv1;

  constexpr double aNullValue = Precision::Approximation() * Precision::Approximation(),
                   anAngTol   = Precision::Angular();

  double tu1 = u1;
  double tu2 = u2;
  double tv1 = v1;
  double tv2 = v2;

  if (MyHasBeenComputed)
  {
    if ((MyParOnS1.X() == u1) && (MyParOnS1.Y() == v1) && (MyParOnS2.X() == u2)
        && (MyParOnS2.Y() == v2))
    {
      return (MyIsTangent);
    }
    else if (MyHasBeenComputedbis == false)
    {
      MyTgbis              = MyTg;
      MyTguv1bis           = MyTguv1;
      MyTguv2bis           = MyTguv2;
      MyPntbis             = MyPnt;
      MyParOnS1bis         = MyParOnS1;
      MyParOnS2bis         = MyParOnS2;
      MyIsTangentbis       = MyIsTangent;
      MyHasBeenComputedbis = MyHasBeenComputed;
    }
  }

  if (MyHasBeenComputedbis)
  {
    if ((MyParOnS1bis.X() == u1) && (MyParOnS1bis.Y() == v1) && (MyParOnS2bis.X() == u2)
        && (MyParOnS2bis.Y() == v2))
    {

      gp_Vec   TV(MyTg);
      gp_Vec2d TV1(MyTguv1);
      gp_Vec2d TV2(MyTguv2);
      gp_Pnt   TP(MyPnt);
      gp_Pnt2d TP1(MyParOnS1);
      gp_Pnt2d TP2(MyParOnS2);
      bool     TB = MyIsTangent;

      MyTg        = MyTgbis;
      MyTguv1     = MyTguv1bis;
      MyTguv2     = MyTguv2bis;
      MyPnt       = MyPntbis;
      MyParOnS1   = MyParOnS1bis;
      MyParOnS2   = MyParOnS2bis;
      MyIsTangent = MyIsTangentbis;

      MyTgbis        = TV;
      MyTguv1bis     = TV1;
      MyTguv2bis     = TV2;
      MyPntbis       = TP;
      MyParOnS1bis   = TP1;
      MyParOnS2bis   = TP2;
      MyIsTangentbis = TB;

      return (MyIsTangent);
    }
  }

  math_Vector X(1, 2);
  math_Vector BornInf(1, 2), BornSup(1, 2), Tolerance(1, 2);

  Tolerance(1) = 1.0e-8;
  Tolerance(2) = 1.0e-8;
  double binfu, bsupu, binfv, bsupv;
  binfu               = ThePSurfaceTool::FirstUParameter(aPSurf);
  binfv               = ThePSurfaceTool::FirstVParameter(aPSurf);
  bsupu               = ThePSurfaceTool::LastUParameter(aPSurf);
  bsupv               = ThePSurfaceTool::LastVParameter(aPSurf);
  BornInf(1)          = binfu;
  BornSup(1)          = bsupu;
  BornInf(2)          = binfv;
  BornSup(2)          = bsupv;
  double TranslationU = 0., TranslationV = 0.;

  if (!FillInitialVectorOfSolution(u1,
                                   v1,
                                   u2,
                                   v2,
                                   binfu,
                                   bsupu,
                                   binfv,
                                   bsupv,
                                   X,
                                   TranslationU,
                                   TranslationV))
  {
    MyIsTangent = MyIsTangentbis = false;
    MyHasBeenComputed = MyHasBeenComputedbis = false;
    return (false);
  }

  bool   aRsnldIsDone = false;
  double PourTesterU  = X(1);
  double PourTesterV  = X(2);
  if (GetUseSolver())
  {
    math_FunctionSetRoot Rsnld(MyZerImpFunc);
    Rsnld.SetTolerance(Tolerance);
    Rsnld.Perform(MyZerImpFunc, X, BornInf, BornSup);
    aRsnldIsDone = Rsnld.IsDone();
    if (aRsnldIsDone)
      Rsnld.Root(X);
  }
  if (aRsnldIsDone || !GetUseSolver())
  {
    MyHasBeenComputed = true;

    double DistAvantApresU = std::abs(PourTesterU - X(1));
    double DistAvantApresV = std::abs(PourTesterV - X(2));

    MyPnt = P = ThePSurfaceTool::Value(aPSurf, X(1), X(2));

    if ((DistAvantApresV <= 0.001) && (DistAvantApresU <= 0.001))
    {
      gp_Vec aD1uPrm, aD1vPrm;
      gp_Vec aD1uQuad, aD1vQuad;

      if (MyImplicitFirst)
      {
        u2 = X(1) - TranslationU;
        v2 = X(2) - TranslationV;

        if (aQSurf.TypeQuadric() != GeomAbs_Plane)
        {
          while (u1 - tu1 > M_PI)
            u1 -= M_PI + M_PI;
          while (tu1 - u1 > M_PI)
            u1 += M_PI + M_PI;
        }

        MyParOnS1.SetCoord(tu1, tv1);
        MyParOnS2.SetCoord(tu2, tv2);

        gp_Pnt aP2;

        ThePSurfaceTool::D1(aPSurf, X(1), X(2), P, aD1uPrm, aD1vPrm);
        aQSurf.D1(u1, v1, aP2, aD1uQuad, aD1vQuad);

        P.BaryCenter(1.0, aP2, 1.0);
      }
      else
      {
        u1 = X(1) - TranslationU;
        v1 = X(2) - TranslationV;

        if (aQSurf.TypeQuadric() != GeomAbs_Plane)
        {
          while (u2 - tu2 > M_PI)
            u2 -= M_PI + M_PI;
          while (tu2 - u2 > M_PI)
            u2 += M_PI + M_PI;
        }

        MyParOnS1.SetCoord(tu1, tv1);
        MyParOnS2.SetCoord(tu2, tu2);

        gp_Pnt aP2;
        ThePSurfaceTool::D1(aPSurf, X(1), X(2), P, aD1uPrm, aD1vPrm);

        aQSurf.D1(u2, v2, aP2, aD1uQuad, aD1vQuad);

        P.BaryCenter(1.0, aP2, 1.0);
      }

      MyPnt = P;

      gp_Vec aNormalPrm(aD1uPrm.Crossed(aD1vPrm)), aNormalImp(aQSurf.Normale(MyPnt));

      const double aSQMagnPrm = aNormalPrm.SquareMagnitude(),
                   aSQMagnImp = aNormalImp.SquareMagnitude();

      bool isPrmSingular = false, isImpSingular = false;

      if (IsSingular(aD1uPrm, aD1vPrm, aNullValue, anAngTol))
      {
        isPrmSingular = true;
        if (!SingularProcessing(aD1uPrm, aD1vPrm, true, aNullValue, anAngTol, Tg, aPrmTg))
        {
          MyIsTangent       = false;
          MyHasBeenComputed = MyHasBeenComputedbis = false;
          return false;
        }

        MyTg = Tg;
      }
      else
      {
        aNormalPrm.Divide(sqrt(aSQMagnPrm));
      }

      if (aSQMagnImp < aNullValue)
      {
        isImpSingular = true;

        if (!SingularProcessing(aD1uQuad,
                                aD1vQuad,
                                !isPrmSingular,
                                aNullValue,
                                anAngTol,
                                Tg,
                                aQuadTg))
        {
          MyIsTangent       = false;
          MyHasBeenComputed = MyHasBeenComputedbis = false;
          return false;
        }

        MyTg = Tg;
      }
      else
      {
        aNormalImp.Divide(sqrt(aSQMagnImp));
      }

      if (isImpSingular && isPrmSingular)
      {

        MyTguv1 = Tguv1;
        MyTguv2 = Tguv2;

        MyIsTangent = true;
        return MyIsTangent;
      }
      else if (!(isImpSingular || isPrmSingular))
      {

        Tg = aNormalImp.Crossed(aNormalPrm);
      }

      const double aSQMagnTg = Tg.SquareMagnitude();

      if (aSQMagnTg < aNullValue)
      {
        MyIsTangent       = false;
        MyHasBeenComputed = MyHasBeenComputedbis = false;
        return false;
      }

      Tg.Divide(sqrt(aSQMagnTg));
      MyTg = Tg;

      if (!isPrmSingular)
      {

        if (!NonSingularProcessing(aD1uPrm, aD1vPrm, Tg, aNullValue, anAngTol, aPrmTg))
        {
          MyIsTangent       = false;
          MyHasBeenComputed = MyHasBeenComputedbis = false;
          return false;
        }
      }

      if (!isImpSingular)
      {

        if (!NonSingularProcessing(aD1uQuad, aD1vQuad, Tg, aNullValue, anAngTol, aQuadTg))
        {
          MyIsTangent       = false;
          MyHasBeenComputed = MyHasBeenComputedbis = false;
          return false;
        }
      }

      MyTguv1 = Tguv1;
      MyTguv2 = Tguv2;

      MyIsTangent = true;

#ifdef OCCT_DEBUG

#endif

      return true;
    }
    else
    {

      MyIsTangent       = false;
      MyHasBeenComputed = MyHasBeenComputedbis = false;
      return false;
    }
  }
  else
  {
    MyIsTangent       = false;
    MyHasBeenComputed = MyHasBeenComputedbis = false;
    return false;
  }
}

bool ApproxInt_ImpPrmSvSurfaces::SeekPoint(const double     u1,
                                           const double     v1,
                                           const double     u2,
                                           const double     v2,
                                           IntSurf_PntOn2S& Point)
{
  const IntSurf_Quadric& aQSurf = MyZerImpFunc.ISurface();
  const ThePSurface&     aPSurf = MyZerImpFunc.PSurface();

  math_Vector X(1, 2);
  math_Vector BornInf(1, 2), BornSup(1, 2), Tolerance(1, 2);

  Tolerance(1) = 1.0e-8;
  Tolerance(2) = 1.0e-8;
  double binfu, bsupu, binfv, bsupv;
  binfu               = ThePSurfaceTool::FirstUParameter(aPSurf);
  binfv               = ThePSurfaceTool::FirstVParameter(aPSurf);
  bsupu               = ThePSurfaceTool::LastUParameter(aPSurf);
  bsupv               = ThePSurfaceTool::LastVParameter(aPSurf);
  BornInf(1)          = binfu;
  BornSup(1)          = bsupu;
  BornInf(2)          = binfv;
  BornSup(2)          = bsupv;
  double TranslationU = 0., TranslationV = 0.;

  if (!FillInitialVectorOfSolution(u1,
                                   v1,
                                   u2,
                                   v2,
                                   binfu,
                                   bsupu,
                                   binfv,
                                   bsupv,
                                   X,
                                   TranslationU,
                                   TranslationV))
    return false;

  double NewU1, NewV1, NewU2, NewV2;

  math_FunctionSetRoot Rsnld(MyZerImpFunc);
  Rsnld.SetTolerance(Tolerance);
  Rsnld.Perform(MyZerImpFunc, X, BornInf, BornSup);
  if (Rsnld.IsDone())
  {
    MyHasBeenComputed = true;
    Rsnld.Root(X);

    MyPnt = ThePSurfaceTool::Value(aPSurf, X(1), X(2));

    if (MyImplicitFirst)
    {
      NewU2 = X(1) - TranslationU;
      NewV2 = X(2) - TranslationV;

      aQSurf.Parameters(MyPnt, NewU1, NewV1);

      if (aQSurf.TypeQuadric() != GeomAbs_Plane)
      {
        double sign = (NewU1 > u1) ? -1 : 1;
        while (std::abs(u1 - NewU1) > M_PI)
          NewU1 += sign * (M_PI + M_PI);
      }
    }
    else
    {
      NewU1 = X(1) - TranslationU;
      NewV1 = X(2) - TranslationV;

      aQSurf.Parameters(MyPnt, NewU2, NewV2);

      if (aQSurf.TypeQuadric() != GeomAbs_Plane)
      {
        double sign = (NewU2 > u2) ? -1 : 1;
        while (std::abs(u2 - NewU2) > M_PI)
          NewU2 += sign * (M_PI + M_PI);
      }
    }
  }
  else
    return false;

  Point.SetValue(MyPnt, NewU1, NewV1, NewU2, NewV2);
  return true;
}

bool ApproxInt_ImpPrmSvSurfaces::FillInitialVectorOfSolution(const double u1,
                                                             const double v1,
                                                             const double u2,
                                                             const double v2,
                                                             const double binfu,
                                                             const double bsupu,
                                                             const double binfv,
                                                             const double bsupv,
                                                             math_Vector& X,
                                                             double&      TranslationU,
                                                             double&      TranslationV)
{
  const ThePSurface& aPSurf = MyZerImpFunc.PSurface();

  math_Vector F(1, 1);

  TranslationU = 0.0;
  TranslationV = 0.0;

  if (MyImplicitFirst)
  {
    if (u2 < binfu - 0.0000000001)
    {
      if (ThePSurfaceTool::IsUPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::UPeriod(aPSurf);
        do
        {
          TranslationU += d;
        } while (u2 + TranslationU < binfu);
      }
      else
        return (false);
    }
    else if (u2 > bsupu + 0.0000000001)
    {
      if (ThePSurfaceTool::IsUPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::UPeriod(aPSurf);
        do
        {
          TranslationU -= d;
        } while (u2 + TranslationU > bsupu);
      }
      else
        return (false);
    }
    if (v2 < binfv - 0.0000000001)
    {
      if (ThePSurfaceTool::IsVPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::VPeriod(aPSurf);
        do
        {
          TranslationV += d;
        } while (v2 + TranslationV < binfv);
      }
      else
        return (false);
    }
    else if (v2 > bsupv + 0.0000000001)
    {
      if (ThePSurfaceTool::IsVPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::VPeriod(aPSurf);
        do
        {
          TranslationV -= d;
        } while (v2 + TranslationV > bsupv);
      }
      else
        return (false);
    }
    X(1) = u2 + TranslationU;
    X(2) = v2 + TranslationV;
  }
  else
  {
    if (u1 < binfu - 0.0000000001)
    {
      if (ThePSurfaceTool::IsUPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::UPeriod(aPSurf);
        do
        {
          TranslationU += d;
        } while (u1 + TranslationU < binfu);
      }
      else
        return (false);
    }
    else if (u1 > bsupu + 0.0000000001)
    {
      if (ThePSurfaceTool::IsUPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::UPeriod(aPSurf);
        do
        {
          TranslationU -= d;
        } while (u1 + TranslationU > bsupu);
      }
      else
        return (false);
    }
    if (v1 < binfv - 0.0000000001)
    {
      if (ThePSurfaceTool::IsVPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::VPeriod(aPSurf);
        do
        {
          TranslationV += d;
        } while (v1 + TranslationV < binfv);
      }
      else
        return (false);
    }
    else if (v1 > bsupv + 0.0000000001)
    {
      if (ThePSurfaceTool::IsVPeriodic(aPSurf))
      {
        double d = ThePSurfaceTool::VPeriod(aPSurf);
        do
        {
          TranslationV -= d;
        } while (v1 + TranslationV > bsupv);
      }
      else
        return (false);
    }
    X(1) = u1 + TranslationU;
    X(2) = v1 + TranslationV;
  }

  if (GetUseSolver())
  {
    double du = std::max(Precision::Confusion(),
                         ThePSurfaceTool::UResolution(aPSurf, Precision::Confusion()));
    double dv = std::max(Precision::Confusion(),
                         ThePSurfaceTool::VResolution(aPSurf, Precision::Confusion()));
    if (X(1) - 0.0000000001 <= binfu)
      X(1) = X(1) + du;
    if (X(1) + 0.0000000001 >= bsupu)
      X(1) = X(1) - du;
    if (X(2) - 0.0000000001 <= binfv)
      X(2) = X(2) + dv;
    if (X(2) + 0.0000000001 >= bsupv)
      X(2) = X(2) - dv;
  }

  return true;
}
