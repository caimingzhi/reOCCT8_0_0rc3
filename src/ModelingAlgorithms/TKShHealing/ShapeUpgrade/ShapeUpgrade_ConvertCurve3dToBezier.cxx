#include <Geom_BezierCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Conic.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomConvert_ApproxCurve.hpp>
#include <GeomConvert_BSplineCurveToBezierCurve.hpp>
#include <Precision.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade_ConvertCurve3dToBezier.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_ConvertCurve3dToBezier, ShapeUpgrade_SplitCurve3d)

ShapeUpgrade_ConvertCurve3dToBezier::ShapeUpgrade_ConvertCurve3dToBezier()
{
  mySegments    = new NCollection_HSequence<occ::handle<Geom_Curve>>;
  mySplitParams = new NCollection_HSequence<double>;
  myLineMode    = true;
  myCircleMode  = true;
  myConicMode   = true;
}

void ShapeUpgrade_ConvertCurve3dToBezier::Compute()
{
  mySegments->Clear();
  mySplitParams->Clear();
  constexpr double precision = Precision::PConfusion();
  double           First     = mySplitValues->Value(1);
  double           Last      = mySplitValues->Value(mySplitValues->Length());
  if (myCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve>      tmp      = occ::down_cast<Geom_TrimmedCurve>(myCurve);
    occ::handle<Geom_Curve>             BasCurve = tmp->BasisCurve();
    ShapeUpgrade_ConvertCurve3dToBezier converter;
    converter.Init(BasCurve, First, Last);
    converter.SetSplitValues(mySplitValues);
    converter.Compute();
    mySplitValues->ChangeSequence() = converter.SplitValues()->Sequence();
    myNbCurves                      = mySplitValues->Length() - 1;
    myStatus |= converter.myStatus;
    mySegments->ChangeSequence()    = converter.Segments()->Sequence();
    mySplitParams->ChangeSequence() = converter.SplitParams()->Sequence();
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
  {
    occ::handle<Geom_BezierCurve> bezier = occ::down_cast<Geom_BezierCurve>(myCurve);
    myNbCurves                           = mySplitValues->Length() - 1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    if (First < precision && Last > 1 - precision)
    {
      mySegments->Append(bezier);
      myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
    }
    else
    {
      occ::handle<Geom_BezierCurve> besNew = occ::down_cast<Geom_BezierCurve>(bezier->Copy());
      besNew->Segment(First, Last);
      mySegments->Append(besNew);
      myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
    }
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom_Line)))
  {
    occ::handle<Geom_Line> aLine = occ::down_cast<Geom_Line>(myCurve);
    myNbCurves                   = mySplitValues->Length() - 1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    if (!myLineMode)
    {
      mySegments->Append(aLine);
      myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
      return;
    }
    NCollection_Array1<gp_Pnt> poles(1, 2);
    poles(1)                             = aLine->Value(First);
    poles(2)                             = aLine->Value(Last);
    occ::handle<Geom_BezierCurve> bezier = new Geom_BezierCurve(poles);
    mySegments->Append(bezier);
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
    return;
  }
  else if ((myCurve->IsKind(STANDARD_TYPE(Geom_Conic)) && !myConicMode)
           || (myCurve->IsKind(STANDARD_TYPE(Geom_Circle)) && !myCircleMode))
  {
    myNbCurves = mySplitValues->Length() - 1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    mySegments->Append(myCurve);
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
    return;
  }
  else
  {
    occ::handle<Geom_BSplineCurve> aBSpline;
    double                         Shift = 0.;
    if (myCurve->IsKind(STANDARD_TYPE(Geom_Conic)))
    {

      occ::handle<Geom_Curve> tcurve = new Geom_TrimmedCurve(myCurve, First, Last);

      GeomConvert_ApproxCurve approx(tcurve, Precision::Approximation(), GeomAbs_C1, 100, 6);
      if (approx.HasResult())
        aBSpline = approx.Curve();
      else
      {
        occ::handle<Geom_TrimmedCurve> t3d = new Geom_TrimmedCurve(myCurve, First, Last);
        aBSpline = GeomConvert::CurveToBSplineCurve(t3d, Convert_QuasiAngular);
      }
      Shift = First - aBSpline->FirstParameter();
      First = aBSpline->FirstParameter();
      Last  = aBSpline->LastParameter();
    }
    else if (!myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
    {
      aBSpline = GeomConvert::CurveToBSplineCurve(myCurve, Convert_QuasiAngular);
    }
    else
      aBSpline = occ::down_cast<Geom_BSplineCurve>(myCurve);

    double bf = aBSpline->FirstParameter();
    double bl = aBSpline->LastParameter();
    if (std::abs(First - bf) < precision)
      First = bf;
    if (std::abs(Last - bl) < precision)
      Last = bl;
    if (First < bf)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      First = bf;
      mySplitValues->SetValue(1, First);
    }
    if (Last > bl)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      Last = bl;
      mySplitValues->SetValue(mySplitValues->Length(), Last);
    }

    GeomConvert_BSplineCurveToBezierCurve tool(aBSpline, First, Last, precision);
    int                                   nbArcs = tool.NbArcs();
    NCollection_Array1<double>            knots(1, nbArcs + 1);
    tool.Knots(knots);
    mySplitParams->Append(First + Shift);
    int j;
    for (j = 1; j <= nbArcs; j++)
    {
      double nextKnot = knots(j + 1) + Shift;
      if (nextKnot - mySplitParams->Value(mySplitParams->Length()) > precision)
      {
        mySegments->Append(tool.Arc(j));
        mySplitParams->Append(knots(j + 1) + Shift);
      }
    }

    First = mySplitValues->Value(1);
    for (j = 2; j <= mySplitValues->Length(); j++)
    {
      Last = mySplitValues->Value(j);
      for (int i = 2; i <= nbArcs + 1; i++)
      {
        double valknot = knots(i) + Shift;
        if (valknot <= First + precision)
          continue;
        if (valknot >= Last - precision)
          break;
        mySplitValues->InsertBefore(j++, valknot);
      }
      First = Last;
    }
    myNbCurves = mySplitValues->Length() - 1;
  }
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
}

void ShapeUpgrade_ConvertCurve3dToBezier::Build(const bool)
{
  constexpr double prec = Precision::PConfusion();
  int              nb   = mySplitValues->Length();
  myResultingCurves     = new NCollection_HArray1<occ::handle<Geom_Curve>>(1, nb - 1);
  double prevPar        = 0.;
  int    j              = 2;
  for (int i = 2; i <= nb; i++)
  {
    double par = mySplitValues->Value(i);
    for (; j <= mySplitParams->Length(); j++)
      if (mySplitParams->Value(j) + prec > par)
        break;
      else
        prevPar = 0.;

    occ::handle<Geom_Curve> crv = occ::down_cast<Geom_Curve>(mySegments->Value(j - 1)->Copy());
    if (crv->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
    {
      occ::handle<Geom_BezierCurve> bes    = occ::down_cast<Geom_BezierCurve>(crv);
      double                        uFact  = mySplitParams->Value(j) - mySplitParams->Value(j - 1);
      double                        pp     = mySplitValues->Value(i - 1);
      double                        length = (par - pp) / uFact;
      bes->Segment(prevPar, prevPar + length);
      prevPar += length;
      myResultingCurves->SetValue(i - 1, bes);
    }
    else
      myResultingCurves->SetValue(i - 1, crv);
  }
}

occ::handle<NCollection_HSequence<occ::handle<Geom_Curve>>> ShapeUpgrade_ConvertCurve3dToBezier::
  Segments() const
{
  return mySegments;
}

occ::handle<NCollection_HSequence<double>> ShapeUpgrade_ConvertCurve3dToBezier::SplitParams() const
{
  return mySplitParams;
}
