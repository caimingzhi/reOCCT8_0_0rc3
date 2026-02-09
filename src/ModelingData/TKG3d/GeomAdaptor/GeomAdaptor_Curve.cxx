#define No_Standard_RangeError
#define No_Standard_OutOfRange

#include <GeomAdaptor_Curve.hpp>

#include <Adaptor3d_Curve.hpp>
#include <BSplCLib.hpp>
#include <BSplCLib_Cache.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_NotImplemented.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

#include "../Geom/Geom_OffsetCurveUtils.hpp"

static const double PosTol = Precision::PConfusion() / 2;

IMPLEMENT_STANDARD_RTTIEXT(GeomAdaptor_Curve, Adaptor3d_Curve)

occ::handle<Adaptor3d_Curve> GeomAdaptor_Curve::ShallowCopy() const
{
  occ::handle<GeomAdaptor_Curve> aCopy = new GeomAdaptor_Curve();

  aCopy->myCurve     = myCurve;
  aCopy->myTypeCurve = myTypeCurve;
  aCopy->myFirst     = myFirst;
  aCopy->myLast      = myLast;

  if (const auto* anOffsetData = std::get_if<OffsetData>(&myCurveData))
  {
    OffsetData aCopyData;
    aCopyData.BasisAdaptor =
      occ::down_cast<GeomAdaptor_Curve>(anOffsetData->BasisAdaptor->ShallowCopy());
    aCopyData.Offset    = anOffsetData->Offset;
    aCopyData.Direction = anOffsetData->Direction;
    aCopy->myCurveData  = std::move(aCopyData);
  }
  else if (const auto* aBSplineData = std::get_if<BSplineData>(&myCurveData))
  {
    BSplineData aCopyData;
    aCopyData.Curve    = aBSplineData->Curve;
    aCopy->myCurveData = std::move(aCopyData);
  }
  else if (std::holds_alternative<BezierData>(myCurveData))
  {
    aCopy->myCurveData = BezierData{};
  }

  return aCopy;
}

GeomAbs_Shape GeomAdaptor_Curve::LocalContinuity(const double U1, const double U2) const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_BSplineCurve, " ");
  const auto&                       aBSpl  = std::get<BSplineData>(myCurveData).Curve;
  int                               Nb     = aBSpl->NbKnots();
  int                               Index1 = 0;
  int                               Index2 = 0;
  double                            newFirst, newLast;
  const NCollection_Array1<double>& TK = aBSpl->Knots();
  const NCollection_Array1<int>&    TM = aBSpl->Multiplicities();
  BSplCLib::LocateParameter(aBSpl->Degree(),
                            TK,
                            TM,
                            U1,
                            aBSpl->IsPeriodic(),
                            1,
                            Nb,
                            Index1,
                            newFirst);
  BSplCLib::LocateParameter(aBSpl->Degree(),
                            TK,
                            TM,
                            U2,
                            aBSpl->IsPeriodic(),
                            1,
                            Nb,
                            Index2,
                            newLast);
  if (std::abs(newFirst - TK(Index1 + 1)) < Precision::PConfusion())
  {
    if (Index1 < Nb)
      Index1++;
  }
  if (std::abs(newLast - TK(Index2)) < Precision::PConfusion())
    Index2--;
  int MultMax;

  if ((aBSpl->IsPeriodic()) && (Index1 == Nb))
    Index1 = 1;

  if ((Index2 - Index1 <= 0) && (!aBSpl->IsPeriodic()))
  {
    MultMax = 100;
  }
  else
  {
    MultMax = TM(Index1 + 1);
    for (int i = Index1 + 1; i <= Index2; i++)
    {
      if (TM(i) > MultMax)
        MultMax = TM(i);
    }
    MultMax = aBSpl->Degree() - MultMax;
  }
  if (MultMax <= 0)
  {
    return GeomAbs_C0;
  }
  else if (MultMax == 1)
  {
    return GeomAbs_C1;
  }
  else if (MultMax == 2)
  {
    return GeomAbs_C2;
  }
  else if (MultMax == 3)
  {
    return GeomAbs_C3;
  }
  else
  {
    return GeomAbs_CN;
  }
}

void GeomAdaptor_Curve::Reset()
{
  myTypeCurve = GeomAbs_OtherCurve;
  myCurve.Nullify();
  myCurveData = std::monostate{};
  myFirst = myLast = 0.0;
}

void GeomAdaptor_Curve::load(const occ::handle<Geom_Curve>& C,
                             const double                   UFirst,
                             const double                   ULast)
{
  myFirst = UFirst;
  myLast  = ULast;

  if (myCurve != C)
  {
    myCurve     = C;
    myCurveData = std::monostate{};

    const occ::handle<Standard_Type>& TheType = C->DynamicType();
    if (TheType == STANDARD_TYPE(Geom_TrimmedCurve))
    {
      Load(occ::down_cast<Geom_TrimmedCurve>(C)->BasisCurve(), UFirst, ULast);
    }
    else if (TheType == STANDARD_TYPE(Geom_Circle))
    {
      myTypeCurve = GeomAbs_Circle;
    }
    else if (TheType == STANDARD_TYPE(Geom_Line))
    {
      myTypeCurve = GeomAbs_Line;
    }
    else if (TheType == STANDARD_TYPE(Geom_Ellipse))
    {
      myTypeCurve = GeomAbs_Ellipse;
    }
    else if (TheType == STANDARD_TYPE(Geom_Parabola))
    {
      myTypeCurve = GeomAbs_Parabola;
    }
    else if (TheType == STANDARD_TYPE(Geom_Hyperbola))
    {
      myTypeCurve = GeomAbs_Hyperbola;
    }
    else if (TheType == STANDARD_TYPE(Geom_BezierCurve))
    {
      myTypeCurve = GeomAbs_BezierCurve;
      myCurveData = BezierData{};
    }
    else if (TheType == STANDARD_TYPE(Geom_BSplineCurve))
    {
      myTypeCurve = GeomAbs_BSplineCurve;
      BSplineData aBSplineData;
      aBSplineData.Curve = occ::down_cast<Geom_BSplineCurve>(C);
      myCurveData        = std::move(aBSplineData);
    }
    else if (TheType == STANDARD_TYPE(Geom_OffsetCurve))
    {
      myTypeCurve                                 = GeomAbs_OffsetCurve;
      occ::handle<Geom_OffsetCurve> anOffsetCurve = occ::down_cast<Geom_OffsetCurve>(C);
      OffsetData                    anOffsetData;
      anOffsetData.BasisAdaptor = new GeomAdaptor_Curve(anOffsetCurve->BasisCurve());
      anOffsetData.Offset       = anOffsetCurve->Offset();
      anOffsetData.Direction    = anOffsetCurve->Direction();
      myCurveData               = std::move(anOffsetData);
    }
    else
    {
      myTypeCurve = GeomAbs_OtherCurve;
    }
  }
  else
  {

    if (auto* aBSplineData = std::get_if<BSplineData>(&myCurveData))
    {
      aBSplineData->Cache.Nullify();
    }
    else if (auto* aBezierData = std::get_if<BezierData>(&myCurveData))
    {
      aBezierData->Cache.Nullify();
    }
  }
}

GeomAbs_Shape GeomAdaptor_Curve::Continuity() const
{
  if (myTypeCurve == GeomAbs_BSplineCurve)
    return LocalContinuity(myFirst, myLast);

  if (myTypeCurve == GeomAbs_OffsetCurve)
  {
    const GeomAbs_Shape S = occ::down_cast<Geom_OffsetCurve>(myCurve)->GetBasisCurveContinuity();
    switch (S)
    {
      case GeomAbs_CN:
        return GeomAbs_CN;
      case GeomAbs_C3:
        return GeomAbs_C2;
      case GeomAbs_C2:
        return GeomAbs_C1;
      case GeomAbs_C1:
        return GeomAbs_C0;
      case GeomAbs_G1:
        return GeomAbs_G1;
      case GeomAbs_G2:
        return GeomAbs_G2;
      default:
        throw Standard_NoSuchObject("GeomAdaptor_Curve::Continuity");
    }
  }
  else if (myTypeCurve == GeomAbs_OtherCurve)
  {
    throw Standard_NoSuchObject("GeomAdaptor_Curve::Contunuity");
  }

  return GeomAbs_CN;
}

int GeomAdaptor_Curve::NbIntervals(const GeomAbs_Shape S) const
{
  if (myTypeCurve == GeomAbs_BSplineCurve)
  {
    const auto& aBSpl = std::get<BSplineData>(myCurveData).Curve;
    if ((!aBSpl->IsPeriodic() && S <= Continuity()) || S == GeomAbs_C0)
    {
      return 1;
    }

    int aDegree = aBSpl->Degree();
    int aCont;

    switch (S)
    {
      case GeomAbs_C1:
        aCont = 1;
        break;
      case GeomAbs_C2:
        aCont = 2;
        break;
      case GeomAbs_C3:
        aCont = 3;
        break;
      case GeomAbs_CN:
        aCont = aDegree;
        break;
      default:
        throw Standard_DomainError("GeomAdaptor_Curve::NbIntervals()");
    }

    double anEps = std::min(Resolution(Precision::Confusion()), Precision::PConfusion());

    return BSplCLib::Intervals(aBSpl->Knots(),
                               aBSpl->Multiplicities(),
                               aDegree,
                               aBSpl->IsPeriodic(),
                               aCont,
                               myFirst,
                               myLast,
                               anEps,
                               nullptr);
  }

  else if (myTypeCurve == GeomAbs_OffsetCurve)
  {
    int           myNbIntervals = 1;
    GeomAbs_Shape BaseS         = GeomAbs_C0;
    switch (S)
    {
      case GeomAbs_G1:
      case GeomAbs_G2:
        throw Standard_DomainError("GeomAdaptor_Curve::NbIntervals");
        break;
      case GeomAbs_C0:
        BaseS = GeomAbs_C1;
        break;
      case GeomAbs_C1:
        BaseS = GeomAbs_C2;
        break;
      case GeomAbs_C2:
        BaseS = GeomAbs_C3;
        break;
      default:
        BaseS = GeomAbs_CN;
    }
    GeomAdaptor_Curve C(occ::down_cast<Geom_OffsetCurve>(myCurve)->BasisCurve(), myFirst, myLast);

    int iNbBasisInt = C.NbIntervals(BaseS), iInt;
    if (iNbBasisInt > 1)
    {
      NCollection_Array1<double> rdfInter(1, 1 + iNbBasisInt);
      C.Intervals(rdfInter, BaseS);
      for (iInt = 1; iInt <= iNbBasisInt; iInt++)
        if (rdfInter(iInt) > myFirst && rdfInter(iInt) < myLast)
          myNbIntervals++;
    }

    return myNbIntervals;
  }

  else
  {
    return 1;
  }
}

void GeomAdaptor_Curve::Intervals(NCollection_Array1<double>& T, const GeomAbs_Shape S) const
{
  if (myTypeCurve == GeomAbs_BSplineCurve)
  {
    const auto& aBSpl = std::get<BSplineData>(myCurveData).Curve;
    if ((!aBSpl->IsPeriodic() && S <= Continuity()) || S == GeomAbs_C0)
    {
      T(T.Lower())     = myFirst;
      T(T.Lower() + 1) = myLast;
      return;
    }

    int aDegree = aBSpl->Degree();
    int aCont;

    switch (S)
    {
      case GeomAbs_C1:
        aCont = 1;
        break;
      case GeomAbs_C2:
        aCont = 2;
        break;
      case GeomAbs_C3:
        aCont = 3;
        break;
      case GeomAbs_CN:
        aCont = aDegree;
        break;
      default:
        throw Standard_DomainError("GeomAdaptor_Curve::Intervals()");
    }

    double anEps = std::min(Resolution(Precision::Confusion()), Precision::PConfusion());

    BSplCLib::Intervals(aBSpl->Knots(),
                        aBSpl->Multiplicities(),
                        aDegree,
                        aBSpl->IsPeriodic(),
                        aCont,
                        myFirst,
                        myLast,
                        anEps,
                        &T);
  }

  else if (myTypeCurve == GeomAbs_OffsetCurve)
  {
    int           myNbIntervals = 1;
    GeomAbs_Shape BaseS         = GeomAbs_C0;
    switch (S)
    {
      case GeomAbs_G1:
      case GeomAbs_G2:
        throw Standard_DomainError("GeomAdaptor_Curve::NbIntervals");
        break;
      case GeomAbs_C0:
        BaseS = GeomAbs_C1;
        break;
      case GeomAbs_C1:
        BaseS = GeomAbs_C2;
        break;
      case GeomAbs_C2:
        BaseS = GeomAbs_C3;
        break;
      default:
        BaseS = GeomAbs_CN;
    }
    GeomAdaptor_Curve C(occ::down_cast<Geom_OffsetCurve>(myCurve)->BasisCurve(), myFirst, myLast);

    int iNbBasisInt = C.NbIntervals(BaseS), iInt;
    if (iNbBasisInt > 1)
    {
      NCollection_Array1<double> rdfInter(1, 1 + iNbBasisInt);
      C.Intervals(rdfInter, BaseS);
      for (iInt = 1; iInt <= iNbBasisInt; iInt++)
        if (rdfInter(iInt) > myFirst && rdfInter(iInt) < myLast)
          T(++myNbIntervals) = rdfInter(iInt);
    }

    T(T.Lower())                 = myFirst;
    T(T.Lower() + myNbIntervals) = myLast;
  }

  else
  {
    T(T.Lower())     = myFirst;
    T(T.Lower() + 1) = myLast;
  }
}

occ::handle<Adaptor3d_Curve> GeomAdaptor_Curve::Trim(const double First,
                                                     const double Last,
                                                     const double) const
{
  return occ::handle<GeomAdaptor_Curve>(new GeomAdaptor_Curve(myCurve, First, Last));
}

bool GeomAdaptor_Curve::IsClosed() const
{
  if (!Precision::IsPositiveInfinite(myLast) && !Precision::IsNegativeInfinite(myFirst))
  {
    const gp_Pnt Pd = Value(myFirst);
    const gp_Pnt Pf = Value(myLast);
    return (Pd.Distance(Pf) <= Precision::Confusion());
  }
  return false;
}

bool GeomAdaptor_Curve::IsPeriodic() const
{
  return myCurve->IsPeriodic();
}

double GeomAdaptor_Curve::Period() const
{
  return myCurve->LastParameter() - myCurve->FirstParameter();
}

void GeomAdaptor_Curve::RebuildCache(const double theParameter) const
{
  if (myTypeCurve == GeomAbs_BezierCurve)
  {

    auto&                         aCache  = std::get<BezierData>(myCurveData).Cache;
    occ::handle<Geom_BezierCurve> aBezier = occ::down_cast<Geom_BezierCurve>(myCurve);
    int                           aDeg    = aBezier->Degree();
    NCollection_Array1<double>    aFlatKnots(BSplCLib::FlatBezierKnots(aDeg), 1, 2 * (aDeg + 1));
    if (aCache.IsNull())
      aCache = new BSplCLib_Cache(aDeg,
                                  aBezier->IsPeriodic(),
                                  aFlatKnots,
                                  aBezier->Poles(),
                                  aBezier->Weights());
    aCache->BuildCache(theParameter, aFlatKnots, aBezier->Poles(), aBezier->Weights());
  }
  else if (myTypeCurve == GeomAbs_BSplineCurve)
  {

    auto&       aBSplData = std::get<BSplineData>(myCurveData);
    const auto& aBSpl     = aBSplData.Curve;
    auto&       aCache    = aBSplData.Cache;
    if (aCache.IsNull())
      aCache = new BSplCLib_Cache(aBSpl->Degree(),
                                  aBSpl->IsPeriodic(),
                                  aBSpl->KnotSequence(),
                                  aBSpl->Poles(),
                                  aBSpl->Weights());
    aCache->BuildCache(theParameter, aBSpl->KnotSequence(), aBSpl->Poles(), aBSpl->Weights());
  }
}

bool GeomAdaptor_Curve::IsBoundary(const double theU, int& theSpanStart, int& theSpanFinish) const
{
  const auto* aBSplData = std::get_if<BSplineData>(&myCurveData);
  if (aBSplData != nullptr && (theU == myFirst || theU == myLast))
  {
    const auto& aBSpl = aBSplData->Curve;
    if (theU == myFirst)
    {
      aBSpl->LocateU(myFirst, PosTol, theSpanStart, theSpanFinish);
      if (theSpanStart < 1)
        theSpanStart = 1;
      if (theSpanStart >= theSpanFinish)
        theSpanFinish = theSpanStart + 1;
    }
    else if (theU == myLast)
    {
      aBSpl->LocateU(myLast, PosTol, theSpanStart, theSpanFinish);
      if (theSpanFinish > aBSpl->NbKnots())
        theSpanFinish = aBSpl->NbKnots();
      if (theSpanStart >= theSpanFinish)
        theSpanStart = theSpanFinish - 1;
    }
    return true;
  }
  return false;
}

gp_Pnt GeomAdaptor_Curve::Value(const double U) const
{
  gp_Pnt aValue;
  D0(U, aValue);
  return aValue;
}

void GeomAdaptor_Curve::D0(const double U, gp_Pnt& P) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BezierCurve:
    {
      auto& aCache = std::get<BezierData>(myCurveData).Cache;
      if (aCache.IsNull() || !aCache->IsCacheValid(U))
        RebuildCache(U);
      aCache->D0(U, P);
      break;
    }

    case GeomAbs_BSplineCurve:
    {
      int   aStart = 0, aFinish = 0;
      auto& aBSplData = std::get<BSplineData>(myCurveData);
      if (IsBoundary(U, aStart, aFinish))
      {
        aBSplData.Curve->LocalD0(U, aStart, aFinish, P);
      }
      else
      {

        if (aBSplData.Cache.IsNull() || !aBSplData.Cache->IsCacheValid(U))
          RebuildCache(U);
        aBSplData.Cache->D0(U, P);
      }
      break;
    }

    case GeomAbs_OffsetCurve:
    {
      const auto& anOffsetData = std::get<OffsetData>(myCurveData);
      if (!Geom_OffsetCurveUtils::EvaluateD0(U,
                                             anOffsetData.BasisAdaptor.get(),
                                             anOffsetData.Direction,
                                             anOffsetData.Offset,
                                             P))
      {
        throw Standard_NullValue("GeomAdaptor_Curve::D0: Unable to calculate offset point");
      }
      break;
    }

    default:
      myCurve->D0(U, P);
  }
}

void GeomAdaptor_Curve::D1(const double U, gp_Pnt& P, gp_Vec& V) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BezierCurve:
    {
      auto& aCache = std::get<BezierData>(myCurveData).Cache;
      if (aCache.IsNull() || !aCache->IsCacheValid(U))
        RebuildCache(U);
      aCache->D1(U, P, V);
      break;
    }

    case GeomAbs_BSplineCurve:
    {
      int   aStart = 0, aFinish = 0;
      auto& aBSplData = std::get<BSplineData>(myCurveData);
      if (IsBoundary(U, aStart, aFinish))
      {
        aBSplData.Curve->LocalD1(U, aStart, aFinish, P, V);
      }
      else
      {

        if (aBSplData.Cache.IsNull() || !aBSplData.Cache->IsCacheValid(U))
          RebuildCache(U);
        aBSplData.Cache->D1(U, P, V);
      }
      break;
    }

    case GeomAbs_OffsetCurve:
    {
      const auto& anOffsetData = std::get<OffsetData>(myCurveData);
      if (!Geom_OffsetCurveUtils::EvaluateD1(U,
                                             anOffsetData.BasisAdaptor.get(),
                                             anOffsetData.Direction,
                                             anOffsetData.Offset,
                                             P,
                                             V))
      {
        throw Standard_NullValue("GeomAdaptor_Curve::D1: Unable to calculate offset D1");
      }
      break;
    }

    default:
      myCurve->D1(U, P, V);
  }
}

void GeomAdaptor_Curve::D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BezierCurve:
    {
      auto& aCache = std::get<BezierData>(myCurveData).Cache;
      if (aCache.IsNull() || !aCache->IsCacheValid(U))
        RebuildCache(U);
      aCache->D2(U, P, V1, V2);
      break;
    }

    case GeomAbs_BSplineCurve:
    {
      int   aStart = 0, aFinish = 0;
      auto& aBSplData = std::get<BSplineData>(myCurveData);
      if (IsBoundary(U, aStart, aFinish))
      {
        aBSplData.Curve->LocalD2(U, aStart, aFinish, P, V1, V2);
      }
      else
      {

        if (aBSplData.Cache.IsNull() || !aBSplData.Cache->IsCacheValid(U))
          RebuildCache(U);
        aBSplData.Cache->D2(U, P, V1, V2);
      }
      break;
    }

    case GeomAbs_OffsetCurve:
    {
      const auto& anOffsetData = std::get<OffsetData>(myCurveData);
      if (!Geom_OffsetCurveUtils::EvaluateD2(U,
                                             anOffsetData.BasisAdaptor.get(),
                                             anOffsetData.Direction,
                                             anOffsetData.Offset,
                                             P,
                                             V1,
                                             V2))
      {
        throw Standard_NullValue("GeomAdaptor_Curve::D2: Unable to calculate offset D2");
      }
      break;
    }

    default:
      myCurve->D2(U, P, V1, V2);
  }
}

void GeomAdaptor_Curve::D3(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BezierCurve:
    {
      auto& aCache = std::get<BezierData>(myCurveData).Cache;
      if (aCache.IsNull() || !aCache->IsCacheValid(U))
        RebuildCache(U);
      aCache->D3(U, P, V1, V2, V3);
      break;
    }

    case GeomAbs_BSplineCurve:
    {
      int   aStart = 0, aFinish = 0;
      auto& aBSplData = std::get<BSplineData>(myCurveData);
      if (IsBoundary(U, aStart, aFinish))
      {
        aBSplData.Curve->LocalD3(U, aStart, aFinish, P, V1, V2, V3);
      }
      else
      {

        if (aBSplData.Cache.IsNull() || !aBSplData.Cache->IsCacheValid(U))
          RebuildCache(U);
        aBSplData.Cache->D3(U, P, V1, V2, V3);
      }
      break;
    }

    case GeomAbs_OffsetCurve:
    {
      const auto& anOffsetData = std::get<OffsetData>(myCurveData);
      if (!Geom_OffsetCurveUtils::EvaluateD3(U,
                                             anOffsetData.BasisAdaptor.get(),
                                             anOffsetData.Direction,
                                             anOffsetData.Offset,
                                             P,
                                             V1,
                                             V2,
                                             V3))
      {
        throw Standard_NullValue("GeomAdaptor_Curve::D3: Unable to calculate offset D3");
      }
      break;
    }

    default:
      myCurve->D3(U, P, V1, V2, V3);
  }
}

gp_Vec GeomAdaptor_Curve::DN(const double U, const int N) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BezierCurve:
      return myCurve->DN(U, N);

    case GeomAbs_BSplineCurve:
    {
      int aStart = 0, aFinish = 0;
      if (IsBoundary(U, aStart, aFinish))
      {
        return std::get<BSplineData>(myCurveData).Curve->LocalDN(U, aStart, aFinish, N);
      }
      else
        return myCurve->DN(U, N);
    }

    case GeomAbs_OffsetCurve:
    {
      const auto& anOffsetData = std::get<OffsetData>(myCurveData);
      gp_Vec      aDN;
      if (!Geom_OffsetCurveUtils::EvaluateDN(U,
                                             anOffsetData.BasisAdaptor.get(),
                                             anOffsetData.Direction,
                                             anOffsetData.Offset,
                                             N,
                                             aDN))
      {
        throw Standard_NullValue("GeomAdaptor_Curve::DN: Unable to calculate offset DN");
      }
      return aDN;
    }

    default:
      break;
  }
  return myCurve->DN(U, N);
}

double GeomAdaptor_Curve::Resolution(const double R3D) const
{
  switch (myTypeCurve)
  {
    case GeomAbs_Line:
      return R3D;
    case GeomAbs_Circle:
    {
      double R = occ::down_cast<Geom_Circle>(myCurve)->Circ().Radius();
      if (R > R3D / 2.)
        return 2 * std::asin(R3D / (2 * R));
      else
        return 2 * M_PI;
    }
    case GeomAbs_Ellipse:
    {
      return R3D / occ::down_cast<Geom_Ellipse>(myCurve)->MajorRadius();
    }
    case GeomAbs_BezierCurve:
    {
      double res;
      occ::down_cast<Geom_BezierCurve>(myCurve)->Resolution(R3D, res);
      return res;
    }
    case GeomAbs_BSplineCurve:
    {
      double res;
      std::get<BSplineData>(myCurveData).Curve->Resolution(R3D, res);
      return res;
    }
    default:
      return Precision::Parametric(R3D);
  }
}

gp_Lin GeomAdaptor_Curve::Line() const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_Line,
                                 "GeomAdaptor_Curve::Line() - curve is not a Line");
  return occ::down_cast<Geom_Line>(myCurve)->Lin();
}

gp_Circ GeomAdaptor_Curve::Circle() const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_Circle,
                                 "GeomAdaptor_Curve::Circle() - curve is not a Circle");
  return occ::down_cast<Geom_Circle>(myCurve)->Circ();
}

gp_Elips GeomAdaptor_Curve::Ellipse() const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_Ellipse,
                                 "GeomAdaptor_Curve::Ellipse() - curve is not an Ellipse");
  return occ::down_cast<Geom_Ellipse>(myCurve)->Elips();
}

gp_Hypr GeomAdaptor_Curve::Hyperbola() const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_Hyperbola,
                                 "GeomAdaptor_Curve::Hyperbola() - curve is not a Hyperbola");
  return occ::down_cast<Geom_Hyperbola>(myCurve)->Hypr();
}

gp_Parab GeomAdaptor_Curve::Parabola() const
{
  Standard_NoSuchObject_Raise_if(myTypeCurve != GeomAbs_Parabola,
                                 "GeomAdaptor_Curve::Parabola() - curve is not a Parabola");
  return occ::down_cast<Geom_Parabola>(myCurve)->Parab();
}

int GeomAdaptor_Curve::Degree() const
{
  if (myTypeCurve == GeomAbs_BezierCurve)
    return occ::down_cast<Geom_BezierCurve>(myCurve)->Degree();
  else if (myTypeCurve == GeomAbs_BSplineCurve)
    return std::get<BSplineData>(myCurveData).Curve->Degree();
  else
    throw Standard_NoSuchObject();
}

bool GeomAdaptor_Curve::IsRational() const
{
  switch (myTypeCurve)
  {
    case GeomAbs_BSplineCurve:
      return std::get<BSplineData>(myCurveData).Curve->IsRational();
    case GeomAbs_BezierCurve:
      return occ::down_cast<Geom_BezierCurve>(myCurve)->IsRational();
    default:
      return false;
  }
}

int GeomAdaptor_Curve::NbPoles() const
{
  if (myTypeCurve == GeomAbs_BezierCurve)
    return occ::down_cast<Geom_BezierCurve>(myCurve)->NbPoles();
  else if (myTypeCurve == GeomAbs_BSplineCurve)
    return std::get<BSplineData>(myCurveData).Curve->NbPoles();
  else
    throw Standard_NoSuchObject();
}

int GeomAdaptor_Curve::NbKnots() const
{
  if (myTypeCurve != GeomAbs_BSplineCurve)
    throw Standard_NoSuchObject("GeomAdaptor_Curve::NbKnots");
  return std::get<BSplineData>(myCurveData).Curve->NbKnots();
}

occ::handle<Geom_BezierCurve> GeomAdaptor_Curve::Bezier() const
{
  if (myTypeCurve != GeomAbs_BezierCurve)
    throw Standard_NoSuchObject("GeomAdaptor_Curve::Bezier");
  return occ::down_cast<Geom_BezierCurve>(myCurve);
}

occ::handle<Geom_BSplineCurve> GeomAdaptor_Curve::BSpline() const
{
  if (myTypeCurve != GeomAbs_BSplineCurve)
    throw Standard_NoSuchObject("GeomAdaptor_Curve::BSpline");

  return std::get<BSplineData>(myCurveData).Curve;
}

occ::handle<Geom_OffsetCurve> GeomAdaptor_Curve::OffsetCurve() const
{
  if (myTypeCurve != GeomAbs_OffsetCurve)
    throw Standard_NoSuchObject("GeomAdaptor_Curve::OffsetCurve");
  return occ::down_cast<Geom_OffsetCurve>(myCurve);
}
