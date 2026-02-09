#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2dConvert.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomToStep_MakeBoundedCurve.hpp>
#include <GeomToStep_MakeBSplineCurveWithKnots.hpp>
#include <GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_BSplineCurveWithKnots.hpp>
#include <StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.hpp>

GeomToStep_MakeBoundedCurve::GeomToStep_MakeBoundedCurve(const occ::handle<Geom_BoundedCurve>& C,
                                                         const StepData_Factors& theLocalFactors)
{
  done = true;

  if (C->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> Bspli = occ::down_cast<Geom_BSplineCurve>(C);

    if (C->IsPeriodic())
    {
      occ::handle<Geom_BSplineCurve> newBspli = occ::down_cast<Geom_BSplineCurve>(Bspli->Copy());
      newBspli->SetNotPeriodic();
      Bspli = newBspli;
    }
    if (Bspli->IsRational())
    {
      GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve MkRatBSplineC(Bspli,
                                                                                theLocalFactors);
      theBoundedCurve = MkRatBSplineC.Value();
    }
    else
    {
      GeomToStep_MakeBSplineCurveWithKnots MkBSplineC(Bspli, theLocalFactors);
      theBoundedCurve = MkBSplineC.Value();
    }
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {
    occ::handle<Geom_BezierCurve>  Cur   = occ::down_cast<Geom_BezierCurve>(C);
    occ::handle<Geom_BSplineCurve> Bspli = GeomConvert::CurveToBSplineCurve(Cur);
    if (Bspli->IsRational())
    {
      GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve MkRatBSplineC(Bspli,
                                                                                theLocalFactors);
      theBoundedCurve = MkRatBSplineC.Value();
    }
    else
    {
      GeomToStep_MakeBSplineCurveWithKnots MkBSplineC(Bspli, theLocalFactors);
      theBoundedCurve = MkBSplineC.Value();
    }
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "MakeBoundedCurve, type : " << C->DynamicType()->Name() << " not processed"
              << std::endl;
#endif
    done = false;
  }
}

GeomToStep_MakeBoundedCurve::GeomToStep_MakeBoundedCurve(const occ::handle<Geom2d_BoundedCurve>& C,
                                                         const StepData_Factors& theLocalFactors)
{
  done = true;
  if (C->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve)))
  {
    occ::handle<Geom2d_BSplineCurve> Bspli = occ::down_cast<Geom2d_BSplineCurve>(C);

    if (C->IsPeriodic())
    {
      occ::handle<Geom2d_BSplineCurve> newBspli =
        occ::down_cast<Geom2d_BSplineCurve>(Bspli->Copy());
      newBspli->SetNotPeriodic();
      Bspli = newBspli;
    }
    if (Bspli->IsRational())
    {
      GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve MkRatBSplineC(Bspli,
                                                                                theLocalFactors);
      theBoundedCurve = MkRatBSplineC.Value();
    }
    else
    {
      GeomToStep_MakeBSplineCurveWithKnots MkBSplineC(Bspli, theLocalFactors);
      theBoundedCurve = MkBSplineC.Value();
    }
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_BezierCurve)))
  {
    occ::handle<Geom2d_BezierCurve>      Cur   = occ::down_cast<Geom2d_BezierCurve>(C);
    occ::handle<Geom2d_BSplineCurve>     Bspli = Geom2dConvert::CurveToBSplineCurve(Cur);
    GeomToStep_MakeBSplineCurveWithKnots MkBSplineC(Bspli, theLocalFactors);
    theBoundedCurve = MkBSplineC.Value();
  }
  else
    done = false;
}

const occ::handle<StepGeom_BoundedCurve>& GeomToStep_MakeBoundedCurve::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeBoundedCurve::Value() - no result");
  return theBoundedCurve;
}
