

#include <Adaptor3d_Curve.hpp>
#include <Bnd_Box2d.hpp>
#include <ElCLib.hpp>
#include <Extrema_ExtPC.hpp>
#include <Extrema_LocateExtPC.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Conic.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_OffsetCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeExtend_ComplexCurve.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <NCollection_Sequence.hpp>

static void ProjectOnSegments(const Adaptor3d_Curve& theCurve,
                              const gp_Pnt&          thePoint,
                              const int              theSegmentCount,
                              double&                aStartParam,
                              double&                anEndParam,
                              double&                aProjDistance,
                              gp_Pnt&                aProjPoint,
                              double&                aProjParam)
{

  if (theSegmentCount <= 0)
  {
    return;
  }

  const double aParamStep     = (anEndParam - aStartParam) / theSegmentCount;
  double       aMinSqDistance = aProjDistance * aProjDistance;
  bool         aHasChanged    = false;
  for (int i = 0; i <= theSegmentCount; i++)
  {
    const double aCurrentParam      = aStartParam + (aParamStep * i);
    const gp_Pnt aCurrentPoint      = theCurve.Value(aCurrentParam);
    const double aCurrentSqDistance = aCurrentPoint.SquareDistance(thePoint);
    if (aCurrentSqDistance < aMinSqDistance)
    {
      aMinSqDistance = aCurrentSqDistance;
      aProjPoint     = aCurrentPoint;
      aProjParam     = aCurrentParam;
      aHasChanged    = true;
    }
  }
  if (aHasChanged)
  {
    aProjDistance = std::sqrt(aMinSqDistance);
  }

  anEndParam  = std::min(anEndParam, aProjParam + aParamStep);
  aStartParam = std::max(aStartParam, aProjParam - aParamStep);
}

double ShapeAnalysis_Curve::Project(const occ::handle<Geom_Curve>& C3D,
                                    const gp_Pnt&                  P3D,
                                    const double                   preci,
                                    gp_Pnt&                        proj,
                                    double&                        param,
                                    const bool                     AdjustToEnds) const
{
  double uMin = C3D->FirstParameter();
  double uMax = C3D->LastParameter();
  if (uMin < uMax)
    return Project(C3D, P3D, preci, proj, param, uMin, uMax, AdjustToEnds);
  else
    return Project(C3D, P3D, preci, proj, param, uMax, uMin, AdjustToEnds);
}

double ShapeAnalysis_Curve::Project(const occ::handle<Geom_Curve>& C3D,
                                    const gp_Pnt&                  P3D,
                                    const double                   preci,
                                    gp_Pnt&                        proj,
                                    double&                        param,
                                    const double                   cf,
                                    const double                   cl,
                                    const bool                     AdjustToEnds) const
{
  double distmin;
  double uMin = (cf < cl ? cf : cl);
  double uMax = (cf < cl ? cl : cf);

  GeomAdaptor_Curve GAC(C3D, uMin, uMax);
  if (C3D->IsKind(STANDARD_TYPE(Geom_BoundedCurve)))
  {

    double prec = (AdjustToEnds ? preci : Precision::Confusion());

    gp_Pnt LowBound = GAC.Value(uMin);
    gp_Pnt HigBound = GAC.Value(uMax);
    distmin         = LowBound.Distance(P3D);
    if (distmin <= prec)
    {
      param = uMin;
      proj  = LowBound;
      return distmin;
    }
    distmin = HigBound.Distance(P3D);
    if (distmin <= prec)
    {
      param = uMax;
      proj  = HigBound;
      return distmin;
    }
  }

  if (!C3D->IsClosed())
  {

    double delta = std::min(GAC.Resolution(preci), (uMax - uMin) * 0.1);
    uMin -= delta;
    uMax += delta;
    GAC.Load(C3D, uMin, uMax);
  }

  return ProjectAct(GAC, P3D, preci, proj, param);
}

double ShapeAnalysis_Curve::Project(const Adaptor3d_Curve& C3D,
                                    const gp_Pnt&          P3D,
                                    const double           preci,
                                    gp_Pnt&                proj,
                                    double&                param,
                                    const bool             AdjustToEnds) const

{

  double uMin = C3D.FirstParameter();
  double uMax = C3D.LastParameter();

  if (Precision::IsInfinite(uMin) && Precision::IsInfinite(uMax))
    return ProjectAct(C3D, P3D, preci, proj, param);

  double distmin_L = Precision::Infinite(), distmin_H = Precision::Infinite();

  double prec = (AdjustToEnds ? preci : Precision::Confusion());

  gp_Pnt LowBound = C3D.Value(uMin);
  gp_Pnt HigBound = C3D.Value(uMax);
  distmin_L       = LowBound.Distance(P3D);
  distmin_H       = HigBound.Distance(P3D);

  if (distmin_L <= prec)
  {
    param = uMin;
    proj  = LowBound;
    return distmin_L;
  }

  if (distmin_H <= prec)
  {
    param = uMax;
    proj  = HigBound;
    return distmin_H;
  }

  double distProj = ProjectAct(C3D, P3D, preci, proj, param);
  if (distProj < distmin_L + Precision::Confusion()
      && distProj < distmin_H + Precision::Confusion())
    return distProj;

  if (distmin_L < distmin_H)
  {
    param = uMin;
    proj  = LowBound;
    return distmin_L;
  }
  param = uMax;
  proj  = HigBound;
  return distmin_H;
}

double ShapeAnalysis_Curve::ProjectAct(const Adaptor3d_Curve& theCurve,
                                       const gp_Pnt&          thePoint,
                                       const double           theTolerance,
                                       gp_Pnt&                theProjPoint,
                                       double&                theProjParam) const

{
  bool OK      = false;
  theProjParam = 0.;
  try
  {
    OCC_CATCH_SIGNALS
    Extrema_ExtPC aCurveExtrema(thePoint, theCurve);
    double        aMinExtremaDistance = RealLast();
    int           aMinExtremaIndex    = 0;
    if (aCurveExtrema.IsDone() && (aCurveExtrema.NbExt() > 0))
    {
      for (int i = 1; i <= aCurveExtrema.NbExt(); i++)
      {
        if (!aCurveExtrema.IsMin(i))
        {
          continue;
        }

        const double aCurrentDistance = aCurveExtrema.SquareDistance(i);
        if (aCurrentDistance < aMinExtremaDistance)
        {
          aMinExtremaDistance = aCurrentDistance;
          aMinExtremaIndex    = i;
        }
      }

      if (aMinExtremaIndex != 0)
      {
        theProjParam = (aCurveExtrema.Point(aMinExtremaIndex)).Parameter();
        theProjPoint = (aCurveExtrema.Point(aMinExtremaIndex)).Value();
        OK           = true;
      }
    }
  }
  catch (const Standard_Failure& anException)
  {
    (void)anException;
    OK = false;
  }

  double uMin            = theCurve.FirstParameter();
  double uMax            = theCurve.LastParameter();
  bool   anIsClosedCurve = false;
  double aCurvePeriod    = 0.;

  double aProjDistance = Precision::Infinite();
  double aModMin       = Precision::Infinite();

  const double aComputedParam = theProjParam;
  const gp_Pnt aComputedProj  = theProjPoint;

  bool   anIsHaveOldSolution = false;
  double anOldParam          = 0.;
  gp_Pnt anOldProj;
  if (OK)
  {
    anIsHaveOldSolution = true;
    anOldProj           = theProjPoint;
    anOldParam          = theProjParam;
    aProjDistance       = theProjPoint.Distance(thePoint);
    aModMin             = aProjDistance;
    if (aProjDistance > theTolerance)
    {
      OK = false;
    }
    if (theCurve.IsClosed())
    {
      anIsClosedCurve = true;
      aCurvePeriod    = uMax - uMin;
    }
  }

  if (!OK)
  {

    theProjParam = 0.;

    switch (theCurve.GetType())
    {
      case GeomAbs_Circle:
      {
        const gp_Circ& aCirc = theCurve.Circle();
        theProjPoint         = aCirc.Position().Location();
        if (aCirc.Radius() <= gp::Resolution()
            || thePoint.SquareDistance(theProjPoint) <= gp::Resolution())
        {
          theProjParam = theCurve.FirstParameter();
          theProjPoint = theProjPoint.XYZ() + aCirc.XAxis().Direction().XYZ() * aCirc.Radius();
        }
        else
        {
          theProjParam = ElCLib::Parameter(aCirc, thePoint);
          theProjPoint = ElCLib::Value(theProjParam, aCirc);
        }
        anIsClosedCurve = true;
        aCurvePeriod    = 2. * M_PI;
      }
      break;

      case GeomAbs_Hyperbola:
      {
        theProjParam = ElCLib::Parameter(theCurve.Hyperbola(), thePoint);
        theProjPoint = ElCLib::Value(theProjParam, theCurve.Hyperbola());
      }
      break;

      case GeomAbs_Parabola:
      {
        theProjParam = ElCLib::Parameter(theCurve.Parabola(), thePoint);
        theProjPoint = ElCLib::Value(theProjParam, theCurve.Parabola());
      }
      break;

      case GeomAbs_Line:
      {
        theProjParam = ElCLib::Parameter(theCurve.Line(), thePoint);
        theProjPoint = ElCLib::Value(theProjParam, theCurve.Line());
      }
      break;

      case GeomAbs_Ellipse:
      {
        theProjParam    = ElCLib::Parameter(theCurve.Ellipse(), thePoint);
        theProjPoint    = ElCLib::Value(theProjParam, theCurve.Ellipse());
        anIsClosedCurve = true;
        aCurvePeriod    = 2. * M_PI;
      }
      break;

      default:
      {

        aProjDistance = Precision::Infinite();
        ProjectOnSegments(theCurve,
                          thePoint,
                          25,
                          uMin,
                          uMax,
                          aProjDistance,
                          theProjPoint,
                          theProjParam);
        if (aProjDistance <= theTolerance)
        {
          return aProjDistance;
        }

        Extrema_LocateExtPC aProjector(thePoint, theCurve, theProjParam, uMin, uMax, theTolerance);
        if (aProjector.IsDone())
        {
          theProjParam             = aProjector.Point().Parameter();
          theProjPoint             = aProjector.Point().Value();
          const double aDistNewton = thePoint.Distance(theProjPoint);
          if (aDistNewton < aModMin)
          {
            return aDistNewton;
          }
        }

        for (const int aSegmentCount : {40, 20, 25, 40})
        {
          ProjectOnSegments(theCurve,
                            thePoint,
                            aSegmentCount,
                            uMin,
                            uMax,
                            aProjDistance,
                            theProjPoint,
                            theProjParam);
          if (aProjDistance <= theTolerance)
          {
            return aProjDistance;
          }
        }

        if (aProjDistance > aModMin)
        {
          aProjDistance = aModMin;
          theProjParam  = aComputedParam;
          theProjPoint  = aComputedProj;
        }

        return aProjDistance;
      }
    }
  }

  if (anIsClosedCurve && (theProjParam < uMin || theProjParam > uMax))
  {
    theProjParam += ShapeAnalysis::AdjustByPeriod(theProjParam, 0.5 * (uMin + uMax), aCurvePeriod);
  }

  if (anIsHaveOldSolution)
  {

    const double anOldDist = anOldProj.SquareDistance(thePoint);
    const double aNewDist  = theProjPoint.SquareDistance(thePoint);
    if (anOldDist < aNewDist)
    {
      theProjPoint = anOldProj;
      theProjParam = anOldParam;
    }
  }
  return theProjPoint.Distance(thePoint);
}

double ShapeAnalysis_Curve::NextProject(const double                   paramPrev,
                                        const occ::handle<Geom_Curve>& C3D,
                                        const gp_Pnt&                  P3D,
                                        const double                   preci,
                                        gp_Pnt&                        proj,
                                        double&                        param,
                                        const double                   cf,
                                        const double                   cl,
                                        const bool                     AdjustToEnds) const
{
  double            uMin    = (cf < cl ? cf : cl);
  double            uMax    = (cf < cl ? cl : cf);
  double            distmin = Precision::Infinite();
  GeomAdaptor_Curve GAC(C3D, uMin, uMax);
  if (C3D->IsKind(STANDARD_TYPE(Geom_BoundedCurve)))
  {

    double prec = (AdjustToEnds ? preci : Precision::Confusion());

    gp_Pnt LowBound = GAC.Value(uMin);
    gp_Pnt HigBound = GAC.Value(uMax);
    distmin         = LowBound.Distance(P3D);
    if (distmin <= prec)
    {
      param = uMin;
      proj  = LowBound;
      return distmin;
    }
    distmin = HigBound.Distance(P3D);
    if (distmin <= prec)
    {
      param = uMax;
      proj  = HigBound;
      return distmin;
    }
  }

  if (!C3D->IsClosed())
  {

    double delta = std::min(GAC.Resolution(preci), (uMax - uMin) * 0.1);
    uMin -= delta;
    uMax += delta;
    GAC.Load(C3D, uMin, uMax);
  }
  return NextProject(paramPrev, GAC, P3D, preci, proj, param);
}

double ShapeAnalysis_Curve::NextProject(const double           paramPrev,
                                        const Adaptor3d_Curve& C3D,
                                        const gp_Pnt&          P3D,
                                        const double           preci,
                                        gp_Pnt&                proj,
                                        double&                param) const
{
  double uMin = C3D.FirstParameter();
  double uMax = C3D.LastParameter();

  Extrema_LocateExtPC aProjector(P3D, C3D, paramPrev, uMin, uMax, preci);
  if (aProjector.IsDone())
  {
    param = aProjector.Point().Parameter();
    proj  = aProjector.Point().Value();
    return P3D.Distance(proj);
  }
  return Project(C3D, P3D, preci, proj, param, false);
}

bool ShapeAnalysis_Curve::ValidateRange(const occ::handle<Geom_Curve>& theCurve,
                                        double&                        First,
                                        double&                        Last,
                                        const double                   preci) const
{

  double cf = theCurve->FirstParameter();
  double cl = theCurve->LastParameter();

  if (theCurve->IsKind(STANDARD_TYPE(Geom_BoundedCurve)) && !theCurve->IsClosed())
  {
    if (First < cf)
    {
      First = cf;
    }
    else if (First > cl)
    {
      First = cl;
    }
    if (Last < cf)
    {
      Last = cf;
    }
    else if (Last > cl)
    {
      Last = cl;
    }
  }

  if (ShapeAnalysis_Curve::IsPeriodic(theCurve))
  {

    ElCLib::AdjustPeriodic(cf, cl, Precision::PConfusion(), First, Last);
  }
  else if (First < Last)
  {
  }
  else if (theCurve->IsClosed())
  {

    if (std::abs(Last - cf) < Precision::PConfusion())
      Last = cl;

    else if (std::abs(First - cl) < Precision::PConfusion())
      First = cf;

    else
    {

      if (theCurve->Value(First).Distance(theCurve->Value(cf)) < preci)
        First = cf;
      if (theCurve->Value(Last).Distance(theCurve->Value(cl)) < preci)
        Last = cl;
      if (First > Last)
      {
        double tmp = First;
        First      = Last;
        Last       = tmp;
      }
    }
  }

  else if (theCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> aBSpline = occ::down_cast<Geom_BSplineCurve>(theCurve);
    if (aBSpline->StartPoint().Distance(aBSpline->EndPoint()) <= preci)
    {

      if (std::abs(Last - cf) < Precision::PConfusion())
        Last = cl;

      else if (std::abs(First - cl) < Precision::PConfusion())
        First = cf;

      else
      {
        double tmp = First;
        First      = Last;
        Last       = tmp;
      }
    }

    else if (First > Last)
    {
      First = theCurve->ReversedParameter(First);
      Last  = theCurve->ReversedParameter(Last);
      theCurve->Reverse();
    }

    if (First == Last)
    {
      First = cf;
      Last  = cl;
      return false;
    }
  }
  else
  {

    if (First > Last)
    {
      First = theCurve->ReversedParameter(First);
      Last  = theCurve->ReversedParameter(Last);
      theCurve->Reverse();
    }

    if (First == Last)
    {
      First -= Precision::PConfusion();
      Last += Precision::PConfusion();
    }
    return false;
  }
  return true;
}

static int SearchForExtremum(const occ::handle<Geom2d_Curve>& C2d,
                             const double                     First,
                             const double                     Last,
                             const gp_Vec2d&                  dir,
                             double&                          par,
                             gp_Pnt2d&                        res)
{
  double prevpar;
  int    nbOut = 0;
  for (int i = 0; i < 10; i++)
  {
    prevpar = par;

    gp_Vec2d D1, D2;
    C2d->D2(par, res, D1, D2);
    double Det = (D2 * dir);
    if (std::abs(Det) < 1e-10)
      return true;

    par -= (D1 * dir) / Det;
    if (std::abs(par - prevpar) < Precision::PConfusion())
      return true;

    if (par < First)
    {
      if (nbOut++ > 2 || prevpar == First)
        return false;
      par = First;
    }
    if (par > Last)
    {
      if (nbOut++ > 2 || prevpar == Last)
        return false;
      par = Last;
    }
  }
  return true;
}

void ShapeAnalysis_Curve::FillBndBox(const occ::handle<Geom2d_Curve>& C2d,
                                     const double                     First,
                                     const double                     Last,
                                     const int                        NPoints,
                                     const bool                       Exact,
                                     Bnd_Box2d&                       Box) const
{
  if (!Exact)
  {
    int    nseg = (NPoints < 2 ? 1 : NPoints - 1);
    double step = (Last - First) / nseg;
    for (int i = 0; i <= nseg; i++)
    {
      double   par = First + i * step;
      gp_Pnt2d pnt = C2d->Value(par);
      Box.Add(pnt);
    }
    return;
  }

  Geom2dAdaptor_Curve anAC(C2d, First, Last);
  int                 nbInt = anAC.NbIntervals(GeomAbs_C2);

  int                        nbSamples = (nbInt < 2 ? NPoints - 1 : nbInt);
  NCollection_Array1<double> aParams(1, nbSamples + 1);
  if (nbSamples == nbInt)
    anAC.Intervals(aParams, GeomAbs_C2);
  else
  {
    double step = (Last - First) / nbSamples;
    for (int i = 0; i <= nbSamples; i++)
      aParams(i + 1) = First + i * step;
  }
  for (int i = 1; i <= nbSamples + 1; i++)
  {
    double   aPar1 = aParams(i);
    gp_Pnt2d aPnt  = C2d->Value(aPar1);
    Box.Add(aPnt);
    if (i <= nbSamples)
    {
      double   aPar2 = aParams(i + 1);
      double   par   = (aPar1 + aPar2) * 0.5;
      gp_Pnt2d pextr;
      double   parextr = par;
      if (SearchForExtremum(C2d, aPar1, aPar2, gp_Vec2d(1, 0), parextr, pextr))
      {
        Box.Add(pextr);
      }
      parextr = par;
      if (SearchForExtremum(C2d, aPar1, aPar2, gp_Vec2d(0, 1), parextr, pextr))
      {
        Box.Add(pextr);
      }
    }
  }
}

int ShapeAnalysis_Curve::SelectForwardSeam(const occ::handle<Geom2d_Curve>& C1,
                                           const occ::handle<Geom2d_Curve>& C2) const
{

  int theCurveIndice = 0;

  occ::handle<Geom2d_Line> L1 = occ::down_cast<Geom2d_Line>(C1);
  if (L1.IsNull())
  {

    occ::handle<Geom2d_BoundedCurve> BC1 = occ::down_cast<Geom2d_BoundedCurve>(C1);
    if (BC1.IsNull())
      return theCurveIndice;
    gp_Pnt2d StartBC1 = BC1->StartPoint();
    gp_Pnt2d EndBC1   = BC1->EndPoint();
    gp_Vec2d VecBC1(StartBC1, EndBC1);
    if (VecBC1.SquareMagnitude() < gp::Resolution())
      return theCurveIndice;
    L1 = new Geom2d_Line(StartBC1, VecBC1);
  }

  occ::handle<Geom2d_Line> L2 = occ::down_cast<Geom2d_Line>(C2);
  if (L2.IsNull())
  {

    occ::handle<Geom2d_BoundedCurve> BC2 = occ::down_cast<Geom2d_BoundedCurve>(C2);
    if (BC2.IsNull())
      return theCurveIndice;
    gp_Pnt2d StartBC2 = BC2->StartPoint();
    gp_Pnt2d EndBC2   = BC2->EndPoint();
    gp_Vec2d VecBC2(StartBC2, EndBC2);
    if (VecBC2.SquareMagnitude() < gp::Resolution())
      return theCurveIndice;
    L2 = new Geom2d_Line(StartBC2, VecBC2);
  }

  bool UdirPos, UdirNeg, VdirPos, VdirNeg;
  UdirPos = UdirNeg = VdirPos = VdirNeg = false;

  gp_Dir2d theDir  = L1->Direction();
  gp_Pnt2d theLoc1 = L1->Location();
  gp_Pnt2d theLoc2 = L2->Location();

  if (theDir.X() > 0.)
  {
    UdirPos = true;
  }
  else if (theDir.X() < 0.)
  {
    UdirNeg = true;
  }
  else if (theDir.Y() > 0.)
  {
    VdirPos = true;
  }
  else if (theDir.Y() < 0.)
  {
    VdirNeg = true;
  }

  if (VdirPos)
  {

    if (theLoc1.X() > theLoc2.X())
      theCurveIndice = 1;
    else
      theCurveIndice = 2;
  }
  else if (VdirNeg)
  {
    if (theLoc1.X() > theLoc2.X())
      theCurveIndice = 2;
    else
      theCurveIndice = 1;
  }
  else if (UdirPos)
  {

    if (theLoc1.Y() < theLoc2.Y())
      theCurveIndice = 1;
    else
      theCurveIndice = 2;
  }
  else if (UdirNeg)
  {
    if (theLoc1.Y() < theLoc2.Y())
      theCurveIndice = 2;
    else
      theCurveIndice = 1;
  }

  return theCurveIndice;
}

static gp_XYZ GetAnyNormal(const gp_XYZ& orig)
{
  gp_XYZ Norm;
  if (std::abs(orig.Z()) < Precision::Confusion())
    Norm.SetCoord(0, 0, 1);
  else
  {
    Norm.SetCoord(orig.Z(), 0, -orig.X());
    double nrm = Norm.Modulus();
    if (nrm < Precision::Confusion())
      Norm.SetCoord(0, 0, 1);
    else
      Norm = Norm / nrm;
  }
  return Norm;
}

static void AppendControlPoles(NCollection_Sequence<gp_Pnt>&  seq,
                               const occ::handle<Geom_Curve>& curve)
{
  if (curve->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    seq.Append(curve->Value(0));
    seq.Append(curve->Value(1));
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_Conic)))
  {
    seq.Append(curve->Value(0));
    seq.Append(curve->Value(M_PI / 2));
    seq.Append(curve->Value(M_PI));
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {

    occ::handle<Geom_TrimmedCurve> Trimmed = occ::down_cast<Geom_TrimmedCurve>(curve);

    occ::handle<Geom_Curve> aBaseCrv = Trimmed->BasisCurve();
    bool                    done     = false;
    if (aBaseCrv->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
    {
      try
      {
        OCC_CATCH_SIGNALS
        occ::handle<Geom_Geometry>     Ctmp = aBaseCrv->Copy();
        occ::handle<Geom_BSplineCurve> bslp = occ::down_cast<Geom_BSplineCurve>(Ctmp);
        bslp->Segment(curve->FirstParameter(), curve->LastParameter());
        AppendControlPoles(seq, bslp);
        done = true;
      }
      catch (Standard_Failure const&)
      {
      }
    }
    else if (aBaseCrv->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
    {
      try
      {
        OCC_CATCH_SIGNALS
        occ::handle<Geom_Geometry>    Ctmp = aBaseCrv->Copy();
        occ::handle<Geom_BezierCurve> bz   = occ::down_cast<Geom_BezierCurve>(Ctmp);
        bz->Segment(curve->FirstParameter(), curve->LastParameter());
        AppendControlPoles(seq, bz);
        done = true;
      }
      catch (Standard_Failure const&)
      {
      }
    }
    if (!done)
    {
      seq.Append(curve->Value(curve->FirstParameter()));
      seq.Append(curve->Value((curve->FirstParameter() + curve->LastParameter()) / 2.));
      seq.Append(curve->Value(curve->LastParameter()));
    }
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {

    occ::handle<Geom_OffsetCurve> OffsetC = occ::down_cast<Geom_OffsetCurve>(curve);

    seq.Append(curve->Value(curve->FirstParameter()));
    seq.Append(curve->Value((curve->FirstParameter() + curve->LastParameter()) / 2.));
    seq.Append(curve->Value(curve->LastParameter()));
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {

    occ::handle<Geom_BSplineCurve> BSpline = occ::down_cast<Geom_BSplineCurve>(curve);
    NCollection_Array1<gp_Pnt>     Poles(1, BSpline->NbPoles());
    BSpline->Poles(Poles);
    for (int i = 1; i <= BSpline->NbPoles(); i++)
      seq.Append(Poles(i));
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {

    occ::handle<Geom_BezierCurve> Bezier = occ::down_cast<Geom_BezierCurve>(curve);
    NCollection_Array1<gp_Pnt>    Poles(1, Bezier->NbPoles());
    Bezier->Poles(Poles);
    for (int i = 1; i <= Bezier->NbPoles(); i++)
      seq.Append(Poles(i));
  }
}

bool ShapeAnalysis_Curve::IsPlanar(const NCollection_Array1<gp_Pnt>& pnts,
                                   gp_XYZ&                           Normal,
                                   const double                      preci)
{
  double precision = (preci > 0.0) ? preci : Precision::Confusion();
  bool   noNorm    = (Normal.SquareModulus() == 0);

  if (pnts.Length() < 3)
  {
    gp_XYZ N1 = pnts(1).XYZ() - pnts(2).XYZ();
    if (noNorm)
    {
      Normal = GetAnyNormal(N1);
      return true;
    }
    return std::abs(N1 * Normal) < Precision::Confusion();
  }

  gp_XYZ aMaxDir;
  if (noNorm)
  {

    gp_XYZ aCenter(0, 0, 0);
    int    i = 1;
    for (; i <= pnts.Length(); i++)
      aCenter += pnts(i).XYZ();
    aCenter /= pnts.Length();

    aMaxDir = pnts(1).XYZ() - aCenter;
    Normal  = (pnts(pnts.Length()).XYZ() - aCenter) ^ aMaxDir;

    for (i = 1; i < pnts.Length(); i++)
    {
      gp_XYZ aTmpDir = pnts(i + 1).XYZ() - aCenter;
      if (aTmpDir.SquareModulus() > aMaxDir.SquareModulus())
        aMaxDir = aTmpDir;

      gp_XYZ aDelta = (pnts(i).XYZ() - aCenter) ^ (pnts(i + 1).XYZ() - aCenter);
      if (Normal * aDelta < 0)
        aDelta *= -1;
      Normal += aDelta;
    }
  }

  double nrm = Normal.Modulus();
  if (nrm < Precision::Confusion())
  {
    Normal = GetAnyNormal(aMaxDir);
    return true;
  }
  Normal = Normal / nrm;

  double mind = RealLast(), maxd = -RealLast(), dev;
  for (int i = 1; i <= pnts.Length(); i++)
  {
    dev = pnts(i).XYZ() * Normal;
    if (dev < mind)
      mind = dev;
    if (dev > maxd)
      maxd = dev;
  }

  return ((maxd - mind) <= precision);
}

bool ShapeAnalysis_Curve::IsPlanar(const occ::handle<Geom_Curve>& curve,
                                   gp_XYZ&                        Normal,
                                   const double                   preci)
{
  double precision = (preci > 0.0) ? preci : Precision::Confusion();
  bool   noNorm    = (Normal.SquareModulus() == 0);

  if (curve->IsKind(STANDARD_TYPE(Geom_Line)))
  {

    occ::handle<Geom_Line> Line = occ::down_cast<Geom_Line>(curve);
    gp_XYZ                 N1   = Line->Position().Direction().XYZ();
    if (noNorm)
    {
      Normal = GetAnyNormal(N1);
      return true;
    }
    return std::abs(N1 * Normal) < Precision::Confusion();
  }

  if (curve->IsKind(STANDARD_TYPE(Geom_Conic)))
  {

    occ::handle<Geom_Conic> Conic = occ::down_cast<Geom_Conic>(curve);
    gp_XYZ                  N1    = Conic->Axis().Direction().XYZ();
    if (noNorm)
    {
      Normal = N1;
      return true;
    }
    gp_XYZ aVecMul = N1 ^ Normal;
    return aVecMul.SquareModulus() < Precision::SquareConfusion();
  }

  if (curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {

    occ::handle<Geom_TrimmedCurve> Trimmed = occ::down_cast<Geom_TrimmedCurve>(curve);
    return IsPlanar(Trimmed->BasisCurve(), Normal, precision);
  }

  if (curve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {

    occ::handle<Geom_OffsetCurve> OffsetC = occ::down_cast<Geom_OffsetCurve>(curve);
    return IsPlanar(OffsetC->BasisCurve(), Normal, precision);
  }

  if (curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {

    occ::handle<Geom_BSplineCurve> BSpline = occ::down_cast<Geom_BSplineCurve>(curve);
    NCollection_Array1<gp_Pnt>     Poles(1, BSpline->NbPoles());
    BSpline->Poles(Poles);
    return IsPlanar(Poles, Normal, precision);
  }

  if (curve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {

    occ::handle<Geom_BezierCurve> Bezier = occ::down_cast<Geom_BezierCurve>(curve);
    NCollection_Array1<gp_Pnt>    Poles(1, Bezier->NbPoles());
    Bezier->Poles(Poles);
    return IsPlanar(Poles, Normal, precision);
  }

  if (curve->IsKind(STANDARD_TYPE(ShapeExtend_ComplexCurve)))
  {

    occ::handle<ShapeExtend_ComplexCurve> Complex = occ::down_cast<ShapeExtend_ComplexCurve>(curve);
    NCollection_Sequence<gp_Pnt>          sequence;
    int                                   i;
    for (i = 1; i <= Complex->NbCurves(); i++)
      AppendControlPoles(sequence, Complex->Curve(i));
    NCollection_Array1<gp_Pnt> Poles(1, sequence.Length());
    for (i = 1; i <= sequence.Length(); i++)
      Poles(i) = sequence(i);
    return IsPlanar(Poles, Normal, precision);
  }

  return false;
}

bool ShapeAnalysis_Curve::GetSamplePoints(const occ::handle<Geom_Curve>& curve,
                                          const double                   first,
                                          const double                   last,
                                          NCollection_Sequence<gp_Pnt>&  seq)
{
  double adelta = curve->LastParameter() - curve->FirstParameter();
  if (!adelta)
    return false;

  int aK  = (int)ceil((last - first) / adelta);
  int nbp = 100 * aK;
  if (curve->IsKind(STANDARD_TYPE(Geom_Line)))
    nbp = 2;
  else if (curve->IsKind(STANDARD_TYPE(Geom_Circle)))
    nbp = 360 * aK;

  else if (curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> aBspl = occ::down_cast<Geom_BSplineCurve>(curve);

    nbp = aBspl->NbKnots() * aBspl->Degree() * aK;
    if (nbp < 2.0)
      nbp = 2;
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {
    occ::handle<Geom_BezierCurve> aB = occ::down_cast<Geom_BezierCurve>(curve);
    nbp                              = 3 + aB->NbPoles();
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {
    occ::handle<Geom_OffsetCurve> aC = occ::down_cast<Geom_OffsetCurve>(curve);
    return GetSamplePoints(aC->BasisCurve(), first, last, seq);
  }
  else if (curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> aC = occ::down_cast<Geom_TrimmedCurve>(curve);
    return GetSamplePoints(aC->BasisCurve(), first, last, seq);
  }

  GeomAdaptor_Curve GAC(curve);
  double            step = (last - first) / (double)(nbp - 1);
  for (int i = 0; i < nbp - 1; ++i)
    seq.Append(GAC.Value(first + step * i));
  seq.Append(GAC.Value(last));
  return true;
}

bool ShapeAnalysis_Curve::GetSamplePoints(const occ::handle<Geom2d_Curve>& curve,
                                          const double                     first,
                                          const double                     last,
                                          NCollection_Sequence<gp_Pnt2d>&  seq)
{

  Geom2dAdaptor_Curve C(curve, first, last);
  int                 nbs = Geom2dInt_Geom2dCurveTool::NbSamples(C);

  if (nbs > 2)
    nbs *= 4;
  double step = (last - first) / (double)(nbs - 1);
  for (int i = 0; i < nbs - 1; ++i)
    seq.Append(C.Value(first + step * i));
  seq.Append(C.Value(last));
  return true;
}

bool ShapeAnalysis_Curve::IsClosed(const occ::handle<Geom_Curve>& theCurve, const double preci)
{
  if (theCurve->IsClosed())
    return true;

  double prec = std::max(preci, Precision::Confusion());

  double f, l;
  f = theCurve->FirstParameter();
  l = theCurve->LastParameter();

  if (Precision::IsInfinite(f) || Precision::IsInfinite(l))
    return false;

  double aClosedVal = theCurve->Value(f).SquareDistance(theCurve->Value(l));
  double preci2     = prec * prec;

  return (aClosedVal <= preci2);
}

bool ShapeAnalysis_Curve::IsPeriodic(const occ::handle<Geom_Curve>& theCurve)
{

  occ::handle<Geom_Curve> aTmpCurve = theCurve;
  while ((aTmpCurve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
         || (aTmpCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))))
  {
    if (aTmpCurve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
      aTmpCurve = occ::down_cast<Geom_OffsetCurve>(aTmpCurve)->BasisCurve();
    if (aTmpCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
      aTmpCurve = occ::down_cast<Geom_TrimmedCurve>(aTmpCurve)->BasisCurve();
  }
  return aTmpCurve->IsPeriodic();
}

bool ShapeAnalysis_Curve::IsPeriodic(const occ::handle<Geom2d_Curve>& theCurve)
{

  occ::handle<Geom2d_Curve> aTmpCurve = theCurve;
  while ((aTmpCurve->IsKind(STANDARD_TYPE(Geom2d_OffsetCurve)))
         || (aTmpCurve->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve))))
  {
    if (aTmpCurve->IsKind(STANDARD_TYPE(Geom2d_OffsetCurve)))
      aTmpCurve = occ::down_cast<Geom2d_OffsetCurve>(aTmpCurve)->BasisCurve();
    if (aTmpCurve->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
      aTmpCurve = occ::down_cast<Geom2d_TrimmedCurve>(aTmpCurve)->BasisCurve();
  }
  return aTmpCurve->IsPeriodic();
}
