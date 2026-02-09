#include <GeomLib_CheckCurveOnSurface.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_CurveOnSurface.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <math_NewtonMinimum.hpp>
#include <math_PSO.hpp>
#include <math_PSOParticlesPool.hpp>
#include <OSD_Parallel.hpp>
#include <Standard_ErrorHandler.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

typedef NCollection_Array1<occ::handle<Adaptor3d_Curve>> Array1OfHCurve;

class GeomLib_CheckCurveOnSurface_TargetFunc;

static bool MinComputing(GeomLib_CheckCurveOnSurface_TargetFunc& theFunction,
                         const double                            theEpsilon,
                         const int                               theNbParticles,
                         double&                                 theBestValue,
                         double&                                 theBestParameter);

static int FillSubIntervals(const occ::handle<Adaptor3d_Curve>&   theCurve3d,
                            const occ::handle<Adaptor2d_Curve2d>& theCurve2d,
                            const double                          theFirst,
                            const double                          theLast,
                            int&                                  theNbParticles,
                            NCollection_Array1<double>* const     theSubIntervals = nullptr);

class GeomLib_CheckCurveOnSurface_TargetFunc : public math_MultipleVarFunctionWithHessian
{
public:
  GeomLib_CheckCurveOnSurface_TargetFunc(const Adaptor3d_Curve& theC3D,
                                         const Adaptor3d_Curve& theCurveOnSurface,
                                         const double           theFirst,
                                         const double           theLast)
      : myCurve1(theC3D),
        myCurve2(theCurveOnSurface),
        myFirst(theFirst),
        myLast(theLast)
  {
  }

  int NbVariables() const override { return 1; }

  bool Value(const math_Vector& theX, double& theFVal) override { return Value(theX(1), theFVal); }

  bool Value(const double theX, double& theFVal) const
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (!CheckParameter(theX))
        return false;

      const gp_Pnt aP1(myCurve1.Value(theX)), aP2(myCurve2.Value(theX));

      theFVal = -1.0 * aP1.SquareDistance(aP2);
    }
    catch (Standard_Failure const&)
    {
      return false;
    }
    return true;
  }

  int GetStateNumber() override { return 0; }

  bool Gradient(const math_Vector& theX, math_Vector& theGrad) override
  {
    return Derive(theX(1), theGrad(1));
  }

  bool Derive(const double theX, double& theDeriv1, double* const theDeriv2 = nullptr) const
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (!CheckParameter(theX))
      {
        return false;
      }

      gp_Pnt aP1, aP2;
      gp_Vec aDC1, aDC2, aDCC1, aDCC2;

      if (!theDeriv2)
      {
        myCurve1.D1(theX, aP1, aDC1);
        myCurve2.D1(theX, aP2, aDC2);
      }
      else
      {
        myCurve1.D2(theX, aP1, aDC1, aDCC1);
        myCurve2.D2(theX, aP2, aDC2, aDCC2);
      }

      const gp_Vec aVec1(aP1, aP2), aVec2(aDC2 - aDC1);

      theDeriv1 = -2.0 * aVec1.Dot(aVec2);

      if (theDeriv2)
      {
        const gp_Vec aVec3(aDCC2 - aDCC1);
        *theDeriv2 = -2.0 * (aVec2.SquareMagnitude() + aVec1.Dot(aVec3));
      }
    }
    catch (Standard_Failure const&)
    {
      return false;
    }

    return true;
  }

  bool Values(const math_Vector& theX, double& theVal, math_Vector& theGrad) override
  {
    if (!Value(theX, theVal))
    {
      return false;
    }

    if (!Gradient(theX, theGrad))
    {
      return false;
    }

    return true;
  }

  bool Values(const math_Vector& theX,
              double&            theVal,
              math_Vector&       theGrad,
              math_Matrix&       theHessian) override
  {
    if (!Value(theX, theVal))
    {
      return false;
    }

    if (!Derive(theX(1), theGrad(1), &theHessian(1, 1)))
    {
      return false;
    }

    return true;
  }

  double FirstParameter() const { return myFirst; }

  double LastParameter() const { return myLast; }

private:
  GeomLib_CheckCurveOnSurface_TargetFunc operator=(GeomLib_CheckCurveOnSurface_TargetFunc&) =
    delete;

  bool CheckParameter(const double theParam) const
  {
    return ((myFirst <= theParam) && (theParam <= myLast));
  }

  const Adaptor3d_Curve& myCurve1;
  const Adaptor3d_Curve& myCurve2;
  const double           myFirst;
  const double           myLast;
};

class GeomLib_CheckCurveOnSurface_Local
{
public:
  GeomLib_CheckCurveOnSurface_Local(const Array1OfHCurve&             theCurveArray,
                                    const Array1OfHCurve&             theCurveOnSurfaceArray,
                                    const NCollection_Array1<double>& theIntervalsArr,
                                    const double                      theEpsilonRange,
                                    const int                         theNbParticles)
      : myCurveArray(theCurveArray),
        myCurveOnSurfaceArray(theCurveOnSurfaceArray),
        mySubIntervals(theIntervalsArr),
        myEpsilonRange(theEpsilonRange),
        myNbParticles(theNbParticles),
        myArrOfDist(theIntervalsArr.Lower(), theIntervalsArr.Upper() - 1),
        myArrOfParam(theIntervalsArr.Lower(), theIntervalsArr.Upper() - 1)
  {
  }

  void operator()(int theThreadIndex, int theElemIndex) const
  {

    GeomLib_CheckCurveOnSurface_TargetFunc aFunc(
      *(myCurveArray.Value(theThreadIndex).get()),
      *(myCurveOnSurfaceArray.Value(theThreadIndex).get()),
      mySubIntervals.Value(theElemIndex),
      mySubIntervals.Value(theElemIndex + 1));

    double aMinDist = RealLast(), aPar = 0.0;
    if (!MinComputing(aFunc, myEpsilonRange, myNbParticles, aMinDist, aPar))
    {
      myArrOfDist(theElemIndex)  = RealLast();
      myArrOfParam(theElemIndex) = aFunc.FirstParameter();
      return;
    }

    myArrOfDist(theElemIndex)  = aMinDist;
    myArrOfParam(theElemIndex) = aPar;
  }

  void OptimalValues(double& theMinimalValue, double& theParameter) const
  {

    const int aStartInd = myArrOfDist.Lower();
    theMinimalValue     = myArrOfDist(aStartInd);
    theParameter        = myArrOfParam(aStartInd);
    for (int i = aStartInd + 1; i <= myArrOfDist.Upper(); i++)
    {
      if (myArrOfDist(i) < theMinimalValue)
      {
        theMinimalValue = myArrOfDist(i);
        theParameter    = myArrOfParam(i);
      }
    }
  }

private:
  GeomLib_CheckCurveOnSurface_Local operator=(const GeomLib_CheckCurveOnSurface_Local&) = delete;

private:
  const Array1OfHCurve& myCurveArray;
  const Array1OfHCurve& myCurveOnSurfaceArray;

  const NCollection_Array1<double>&  mySubIntervals;
  const double                       myEpsilonRange;
  const int                          myNbParticles;
  mutable NCollection_Array1<double> myArrOfDist;
  mutable NCollection_Array1<double> myArrOfParam;
};

GeomLib_CheckCurveOnSurface::GeomLib_CheckCurveOnSurface()
    : myErrorStatus(0),
      myMaxDistance(RealLast()),
      myMaxParameter(0.),
      myTolRange(Precision::PConfusion()),
      myIsParallel(false)
{
}

GeomLib_CheckCurveOnSurface::GeomLib_CheckCurveOnSurface(
  const occ::handle<Adaptor3d_Curve>& theCurve,
  const double                        theTolRange)
    : myCurve(theCurve),
      myErrorStatus(0),
      myMaxDistance(RealLast()),
      myMaxParameter(0.),
      myTolRange(theTolRange),
      myIsParallel(false)
{
}

void GeomLib_CheckCurveOnSurface::Init()
{
  myCurve.Nullify();
  myErrorStatus  = 0;
  myMaxDistance  = RealLast();
  myMaxParameter = 0.0;
  myTolRange     = Precision::PConfusion();
}

void GeomLib_CheckCurveOnSurface::Init(const occ::handle<Adaptor3d_Curve>& theCurve,
                                       const double                        theTolRange)
{
  myCurve        = theCurve;
  myErrorStatus  = 0;
  myMaxDistance  = RealLast();
  myMaxParameter = 0.0;
  myTolRange     = theTolRange;
}

void GeomLib_CheckCurveOnSurface::Perform(
  const occ::handle<Adaptor3d_CurveOnSurface>& theCurveOnSurface)
{
  if (myCurve.IsNull() || theCurveOnSurface.IsNull())
  {
    myErrorStatus = 1;
    return;
  }

  if ((myCurve->FirstParameter() - theCurveOnSurface->FirstParameter() > myTolRange)
      || (myCurve->LastParameter() - theCurveOnSurface->LastParameter() < -myTolRange))
  {
    myErrorStatus = 2;
    return;
  }

  const double anEpsilonRange = 1.e-3;

  int aNbParticles = 3;

  const int aNbSubIntervals = FillSubIntervals(myCurve,
                                               theCurveOnSurface->GetCurve(),
                                               myCurve->FirstParameter(),
                                               myCurve->LastParameter(),
                                               aNbParticles);

  if (!aNbSubIntervals)
  {
    myErrorStatus = 3;
    return;
  }

  try
  {
    OCC_CATCH_SIGNALS

    NCollection_Array1<double> anIntervals(1, aNbSubIntervals + 1);
    FillSubIntervals(myCurve,
                     theCurveOnSurface->GetCurve(),
                     myCurve->FirstParameter(),
                     myCurve->LastParameter(),
                     aNbParticles,
                     &anIntervals);

    const int aNbThreads =
      myIsParallel
        ? std::min(anIntervals.Size(), OSD_ThreadPool::DefaultPool()->NbDefaultThreadsToLaunch())
        : 1;
    Array1OfHCurve aCurveArray(0, aNbThreads - 1);
    Array1OfHCurve aCurveOnSurfaceArray(0, aNbThreads - 1);
    for (int anI = 0; anI < aNbThreads; ++anI)
    {
      aCurveArray.SetValue(anI, aNbThreads > 1 ? myCurve->ShallowCopy() : myCurve);
      aCurveOnSurfaceArray.SetValue(
        anI,
        aNbThreads > 1 ? theCurveOnSurface->ShallowCopy()
                       : static_cast<const occ::handle<Adaptor3d_Curve>&>(theCurveOnSurface));
    }
    GeomLib_CheckCurveOnSurface_Local aComp(aCurveArray,
                                            aCurveOnSurfaceArray,
                                            anIntervals,
                                            anEpsilonRange,
                                            aNbParticles);
    if (aNbThreads > 1)
    {
      const occ::handle<OSD_ThreadPool>& aThreadPool = OSD_ThreadPool::DefaultPool();
      OSD_ThreadPool::Launcher           aLauncher(*aThreadPool, aNbThreads);
      aLauncher.Perform(anIntervals.Lower(), anIntervals.Upper(), aComp);
    }
    else
    {
      for (int anI = anIntervals.Lower(); anI < anIntervals.Upper(); ++anI)
      {
        aComp(0, anI);
      }
    }
    aComp.OptimalValues(myMaxDistance, myMaxParameter);

    myMaxDistance = sqrt(std::abs(myMaxDistance));
  }
  catch (Standard_Failure const&)
  {
    myErrorStatus = 3;
  }
}

int FillSubIntervals(const occ::handle<Adaptor3d_Curve>&   theCurve3d,
                     const occ::handle<Adaptor2d_Curve2d>& theCurve2d,
                     const double                          theFirst,
                     const double                          theLast,
                     int&                                  theNbParticles,
                     NCollection_Array1<double>* const     theSubIntervals)
{
  const int                        aMaxKnots     = 101;
  const double                     anArrTempC[2] = {theFirst, theLast};
  const NCollection_Array1<double> anArrTemp(anArrTempC[0], 1, 2);

  theNbParticles = 3;
  occ::handle<Geom2d_BSplineCurve> aBS2DCurv;
  occ::handle<Geom_BSplineCurve>   aBS3DCurv;
  bool                             isTrimmed3D = false, isTrimmed2D = false;

  if (theCurve3d->GetType() == GeomAbs_BSplineCurve)
  {
    aBS3DCurv = theCurve3d->BSpline();
  }
  if (theCurve2d->GetType() == GeomAbs_BSplineCurve)
  {
    aBS2DCurv = theCurve2d->BSpline();
  }

  occ::handle<NCollection_HArray1<double>> anArrKnots3D, anArrKnots2D;

  if (!aBS3DCurv.IsNull())
  {
    if (aBS3DCurv->NbKnots() <= aMaxKnots)
    {
      anArrKnots3D = new NCollection_HArray1<double>(aBS3DCurv->Knots());
    }
    else
    {
      int KnotCount;
      if (isTrimmed3D)
      {
        int i;
        KnotCount                                = 0;
        const NCollection_Array1<double>& aKnots = aBS3DCurv->Knots();
        for (i = aBS3DCurv->FirstUKnotIndex(); i <= aBS3DCurv->LastUKnotIndex(); ++i)
        {
          if (aKnots(i) > theFirst && aKnots(i) < theLast)
          {
            ++KnotCount;
          }
        }
        KnotCount += 2;
      }
      else
      {
        KnotCount = aBS3DCurv->LastUKnotIndex() - aBS3DCurv->FirstUKnotIndex() + 1;
      }
      if (KnotCount <= aMaxKnots)
      {
        anArrKnots3D = new NCollection_HArray1<double>(aBS3DCurv->Knots());
      }
      else
      {
        anArrKnots3D = new NCollection_HArray1<double>(1, aMaxKnots);
        anArrKnots3D->SetValue(1, theFirst);
        anArrKnots3D->SetValue(aMaxKnots, theLast);
        int    i;
        double dt = (theLast - theFirst) / (aMaxKnots - 1);
        double t  = theFirst + dt;
        for (i = 2; i < aMaxKnots; ++i, t += dt)
        {
          anArrKnots3D->SetValue(i, t);
        }
      }
    }
  }
  else
  {
    anArrKnots3D = new NCollection_HArray1<double>(anArrTemp);
  }
  if (!aBS2DCurv.IsNull())
  {
    if (aBS2DCurv->NbKnots() <= aMaxKnots)
    {
      anArrKnots2D = new NCollection_HArray1<double>(aBS2DCurv->Knots());
    }
    else
    {
      int KnotCount;
      if (isTrimmed2D)
      {
        int i;
        KnotCount                                = 0;
        const NCollection_Array1<double>& aKnots = aBS2DCurv->Knots();
        for (i = aBS2DCurv->FirstUKnotIndex(); i <= aBS2DCurv->LastUKnotIndex(); ++i)
        {
          if (aKnots(i) > theFirst && aKnots(i) < theLast)
          {
            ++KnotCount;
          }
        }
        KnotCount += 2;
      }
      else
      {
        KnotCount = aBS2DCurv->LastUKnotIndex() - aBS2DCurv->FirstUKnotIndex() + 1;
      }
      if (KnotCount <= aMaxKnots)
      {
        anArrKnots2D = new NCollection_HArray1<double>(aBS2DCurv->Knots());
      }
      else
      {
        anArrKnots2D = new NCollection_HArray1<double>(1, aMaxKnots);
        anArrKnots2D->SetValue(1, theFirst);
        anArrKnots2D->SetValue(aMaxKnots, theLast);
        int    i;
        double dt = (theLast - theFirst) / (aMaxKnots - 1);
        double t  = theFirst + dt;
        for (i = 2; i < aMaxKnots; ++i, t += dt)
        {
          anArrKnots2D->SetValue(i, t);
        }
      }
    }
  }
  else
  {
    anArrKnots2D = new NCollection_HArray1<double>(anArrTemp);
  }

  int aNbSubIntervals = 1;

  try
  {
    OCC_CATCH_SIGNALS
    const int anIndMax3D = anArrKnots3D->Upper(), anIndMax2D = anArrKnots2D->Upper();

    int anIndex3D = anArrKnots3D->Lower(), anIndex2D = anArrKnots2D->Lower();

    if (theSubIntervals)
      theSubIntervals->ChangeValue(aNbSubIntervals) = theFirst;

    while ((anIndex3D <= anIndMax3D) && (anIndex2D <= anIndMax2D))
    {
      const double aVal3D = anArrKnots3D->Value(anIndex3D), aVal2D = anArrKnots2D->Value(anIndex2D);
      const double aDelta = aVal3D - aVal2D;

      if (aDelta < Precision::PConfusion())
      {
        if ((aVal3D > theFirst) && (aVal3D < theLast))
        {
          aNbSubIntervals++;

          if (theSubIntervals)
            theSubIntervals->ChangeValue(aNbSubIntervals) = aVal3D;
        }

        anIndex3D++;

        if (-aDelta < Precision::PConfusion())
        {
          anIndex2D++;
        }
      }
      else
      {
        if ((aVal2D > theFirst) && (aVal2D < theLast))
        {
          aNbSubIntervals++;

          if (theSubIntervals)
            theSubIntervals->ChangeValue(aNbSubIntervals) = aVal2D;
        }

        anIndex2D++;
      }
    }

    if (theSubIntervals)
      theSubIntervals->ChangeValue(aNbSubIntervals + 1) = theLast;

    if (!aBS3DCurv.IsNull())
    {
      theNbParticles = std::max(theNbParticles, aBS3DCurv->Degree());
    }

    if (!aBS2DCurv.IsNull())
    {
      theNbParticles = std::max(theNbParticles, aBS2DCurv->Degree());
    }
  }
  catch (Standard_Failure const&)
  {
#ifdef OCCT_DEBUG
    std::cout << "ERROR! BRepLib_CheckCurveOnSurface.cxx, "
                 "FillSubIntervals(): Incorrect filling!"
              << std::endl;
#endif

    aNbSubIntervals = 0;
  }

  return aNbSubIntervals;
}

bool PSO_Perform(GeomLib_CheckCurveOnSurface_TargetFunc& theFunction,
                 const math_Vector&                      theParInf,
                 const math_Vector&                      theParSup,
                 const double                            theEpsilon,
                 const int                               theNbParticles,
                 double&                                 theBestValue,
                 math_Vector&                            theOutputParam)
{
  const double aDeltaParam = theParSup(1) - theParInf(1);
  if (aDeltaParam < Precision::PConfusion())
    return false;

  math_Vector aStepPar(1, 1);
  aStepPar(1) = theEpsilon * aDeltaParam;

  math_PSOParticlesPool aParticles(theNbParticles, 1);

  const int aNbControlPoints = 3 * theNbParticles;

  const double aStep  = aDeltaParam / (aNbControlPoints - 1);
  int          aCount = 1;
  for (double aPrm = theParInf(1); aCount <= aNbControlPoints;
       aCount++, aPrm = (aCount == aNbControlPoints) ? theParSup(1) : aPrm + aStep)
  {
    double aVal = RealLast();
    if (!theFunction.Value(aPrm, aVal))
      continue;

    PSO_Particle* aParticle = aParticles.GetWorstParticle();

    if (aVal > aParticle->BestDistance)
      continue;

    aParticle->Position[0]     = aPrm;
    aParticle->BestPosition[0] = aPrm;
    aParticle->Distance        = aVal;
    aParticle->BestDistance    = aVal;
  }

  math_PSO aPSO(&theFunction, theParInf, theParSup, aStepPar);
  aPSO.Perform(aParticles, theNbParticles, theBestValue, theOutputParam);

  return true;
}

bool MinComputing(GeomLib_CheckCurveOnSurface_TargetFunc& theFunction,
                  const double                            theEpsilon,
                  const int                               theNbParticles,
                  double&                                 theBestValue,
                  double&                                 theBestParameter)
{
  try
  {
    OCC_CATCH_SIGNALS

    math_Vector aParInf(1, 1), aParSup(1, 1), anOutputParam(1, 1);
    aParInf(1)       = theFunction.FirstParameter();
    aParSup(1)       = theFunction.LastParameter();
    theBestParameter = aParInf(1);
    theBestValue     = RealLast();

    if (!PSO_Perform(theFunction,
                     aParInf,
                     aParSup,
                     theEpsilon,
                     theNbParticles,
                     theBestValue,
                     anOutputParam))
    {
#ifdef OCCT_DEBUG
      std::cout << "BRepLib_CheckCurveOnSurface::Compute(): math_PSO is failed!" << std::endl;
#endif
      return false;
    }

    theBestParameter = anOutputParam(1);

    math_NewtonMinimum aMinSol(theFunction);
    aMinSol.Perform(theFunction, anOutputParam);

    if (aMinSol.IsDone() && (aMinSol.GetStatus() == math_OK))
    {
      aMinSol.Location(anOutputParam);
      theBestParameter = anOutputParam(1);
      theBestValue     = aMinSol.Minimum();
    }
    else
    {
      const double aStep = theEpsilon * (aParSup(1) - aParInf(1));
      aParInf(1)         = theBestParameter - 0.5 * aStep;
      aParSup(1)         = theBestParameter + 0.5 * aStep;

      double aValue = RealLast();
      if (PSO_Perform(theFunction,
                      aParInf,
                      aParSup,
                      theEpsilon,
                      theNbParticles,
                      aValue,
                      anOutputParam))
      {
        if (aValue < theBestValue)
        {
          theBestValue     = aValue;
          theBestParameter = anOutputParam(1);
        }
      }
    }
  }
  catch (Standard_Failure const&)
  {
#ifdef OCCT_DEBUG
    std::cout << "BRepLib_CheckCurveOnSurface.cxx: Exception in MinComputing()!" << std::endl;
#endif
    return false;
  }

  return true;
}
