#include <Geom2d_BoundedCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Conic.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2dConvert.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomToStep_MakeBoundedCurve.hpp>
#include <GeomToStep_MakeConic.hpp>
#include <GeomToStep_MakeCurve.hpp>
#include <GeomToStep_MakeLine.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_BoundedCurve.hpp>
#include <StepGeom_Conic.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_Line.hpp>
#include <Geom2d_TrimmedCurve.hpp>

//=============================================================================
// Creation d' une Curve de prostep a partir d' une Curve de Geom
//=============================================================================
GeomToStep_MakeCurve::GeomToStep_MakeCurve(const occ::handle<Geom_Curve>& C,
                                           const StepData_Factors&        theLocalFactors)
{
  done = true;
  if (C->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Line> L = occ::down_cast<Geom_Line>(C);
    GeomToStep_MakeLine    MkLine(L, theLocalFactors);
    theCurve = MkLine.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_Conic)))
  {
    occ::handle<Geom_Conic> L = occ::down_cast<Geom_Conic>(C);
    GeomToStep_MakeConic    MkConic(L, theLocalFactors);
    theCurve = MkConic.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> T = occ::down_cast<Geom_TrimmedCurve>(C);
    occ::handle<Geom_Curve>        B = T->BasisCurve();
    //    TANT PIS, on passe la courbe de base ...
    if (B->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
    {
      occ::handle<Geom_BSplineCurve> BS = occ::down_cast<Geom_BSplineCurve>(B->Copy());
      BS->Segment(T->FirstParameter(), T->LastParameter());
      B = BS;
    }
    else if (B->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
    {
      occ::handle<Geom_BezierCurve> BZ = occ::down_cast<Geom_BezierCurve>(B->Copy());
      BZ->Segment(T->FirstParameter(), T->LastParameter());
      B = BZ;
    }
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "GeomToStep_MakeCurve, TrimmedCurve, BasisCurve is transferred not trimmed"
                << std::endl;
      std::cout << "BasisCurve Type : " << B->DynamicType()->Name() << std::endl;
#endif
    }
    GeomToStep_MakeCurve MkBasisC(B, theLocalFactors);
    theCurve = MkBasisC.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom_BoundedCurve)))
  {
    occ::handle<Geom_BoundedCurve> L = occ::down_cast<Geom_BoundedCurve>(C);
    GeomToStep_MakeBoundedCurve    MkBoundedC(L, theLocalFactors);
    theCurve = MkBoundedC.Value();
  }
  else
    done = false;
}

//=============================================================================
// Creation d'une Curve de prostep a partir d' une Curve de Geom2d
//=============================================================================

GeomToStep_MakeCurve::GeomToStep_MakeCurve(const occ::handle<Geom2d_Curve>& C,
                                           const StepData_Factors&          theLocalFactors)
{
  done = true;
  if (C->IsKind(STANDARD_TYPE(Geom2d_Line)))
  {
    occ::handle<Geom2d_Line> L = occ::down_cast<Geom2d_Line>(C);
    GeomToStep_MakeLine      MkLine(L, theLocalFactors);
    theCurve = MkLine.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_Conic)))
  {

    // ----------------------------------------------------------------------
    // A Circle of an Ellipse can be indirect. An indirect Axis in not
    // mappable onto STEP. Then to avoid changing the topology, the Circle
    // or the Ellipse are converted into BSpline Curves
    // ----------------------------------------------------------------------

    if (C->IsKind(STANDARD_TYPE(Geom2d_Circle)))
    {
      occ::handle<Geom2d_Circle> theC2d = occ::down_cast<Geom2d_Circle>(C);
      gp_Circ2d                  C2d    = theC2d->Circ2d();
      if (!C2d.IsDirect())
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning : Circle converted to BSpline." << std::endl;
#endif
        occ::handle<Geom2d_BSplineCurve> aBSplineCurve2d =
          Geom2dConvert::CurveToBSplineCurve(theC2d);
        const occ::handle<Geom2d_BoundedCurve>& aBC2d = aBSplineCurve2d; // to avoid ambiguity
        GeomToStep_MakeBoundedCurve             MkBoundedC(aBC2d, theLocalFactors);
        theCurve = MkBoundedC.Value();
      }
      else
      {
        occ::handle<Geom2d_Conic> L = occ::down_cast<Geom2d_Conic>(C);
        GeomToStep_MakeConic      MkConic(L, theLocalFactors);
        theCurve = MkConic.Value();
      }
    }
    else if (C->IsKind(STANDARD_TYPE(Geom2d_Ellipse)))
    {
      occ::handle<Geom2d_Ellipse> theE2d = occ::down_cast<Geom2d_Ellipse>(C);
      gp_Elips2d                  E2d    = theE2d->Elips2d();
      if (!E2d.IsDirect())
      {
#ifdef OCCT_DEBUG
        std::cout << "Warning : Ellipse converted to BSpline." << std::endl;
#endif
        occ::handle<Geom2d_BSplineCurve> aBSplineCurve2d =
          Geom2dConvert::CurveToBSplineCurve(theE2d);
        const occ::handle<Geom2d_BoundedCurve>& aBC2d = aBSplineCurve2d; // to avoid ambiguity
        GeomToStep_MakeBoundedCurve             MkBoundedC(aBC2d, theLocalFactors);
        theCurve = MkBoundedC.Value();
      }
      else
      {
        occ::handle<Geom2d_Conic> L = occ::down_cast<Geom2d_Conic>(C);
        GeomToStep_MakeConic      MkConic(L, theLocalFactors);
        theCurve = MkConic.Value();
      }
    }
    else
    {
      occ::handle<Geom2d_Conic> L = occ::down_cast<Geom2d_Conic>(C);
      GeomToStep_MakeConic      MkConic(L, theLocalFactors);
      theCurve = MkConic.Value();
    }
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_BoundedCurve)))
  {
    occ::handle<Geom2d_BoundedCurve> L = occ::down_cast<Geom2d_BoundedCurve>(C);
    GeomToStep_MakeBoundedCurve      MkBoundedC(L, theLocalFactors);
    theCurve = MkBoundedC.Value();
  }
  else if (C->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
  {
    GeomToStep_MakeCurve aMaker(occ::down_cast<Geom2d_TrimmedCurve>(C)->BasisCurve(),
                                theLocalFactors);
    theCurve = aMaker.Value();
  }
  else
    done = false;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Curve>& GeomToStep_MakeCurve::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeCurve::Value() - no result");
  return theCurve;
}
