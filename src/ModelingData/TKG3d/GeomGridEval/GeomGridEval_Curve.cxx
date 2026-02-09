

#include <GeomGridEval_Curve.hpp>

#include <GeomAdaptor_Curve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Line.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_TrimmedCurve.hpp>

namespace
{

  occ::handle<Geom_Curve> ExtractBasisCurve(const occ::handle<Geom_Curve>& theCurve)
  {
    occ::handle<Geom_Curve> aResult = theCurve;
    while (auto aTrimmed = occ::down_cast<Geom_TrimmedCurve>(aResult))
    {
      aResult = aTrimmed->BasisCurve();
    }
    return aResult;
  }

} // namespace

void GeomGridEval_Curve::Initialize(const Adaptor3d_Curve& theCurve)
{
  if (theCurve.IsKind(STANDARD_TYPE(GeomAdaptor_Curve)))
  {
    Initialize(static_cast<const GeomAdaptor_Curve&>(theCurve).Curve());
    return;
  }

  myCurveType = theCurve.GetType();
  myEvaluator.emplace<GeomGridEval_OtherCurve>(theCurve);
}

void GeomGridEval_Curve::Initialize(const occ::handle<Geom_Curve>& theCurve)
{
  if (theCurve.IsNull())
  {
    myEvaluator.emplace<std::monostate>();
    myCurveType = GeomAbs_OtherCurve;
    return;
  }

  occ::handle<Geom_Curve> aBasisCurve = ExtractBasisCurve(theCurve);

  if (auto aLine = occ::down_cast<Geom_Line>(aBasisCurve))
  {
    myCurveType = GeomAbs_Line;
    myEvaluator.emplace<GeomGridEval_Line>(aLine);
  }
  else if (auto aCircle = occ::down_cast<Geom_Circle>(aBasisCurve))
  {
    myCurveType = GeomAbs_Circle;
    myEvaluator.emplace<GeomGridEval_Circle>(aCircle);
  }
  else if (auto anEllipse = occ::down_cast<Geom_Ellipse>(aBasisCurve))
  {
    myCurveType = GeomAbs_Ellipse;
    myEvaluator.emplace<GeomGridEval_Ellipse>(anEllipse);
  }
  else if (auto aHyperbola = occ::down_cast<Geom_Hyperbola>(aBasisCurve))
  {
    myCurveType = GeomAbs_Hyperbola;
    myEvaluator.emplace<GeomGridEval_Hyperbola>(aHyperbola);
  }
  else if (auto aParabola = occ::down_cast<Geom_Parabola>(aBasisCurve))
  {
    myCurveType = GeomAbs_Parabola;
    myEvaluator.emplace<GeomGridEval_Parabola>(aParabola);
  }
  else if (auto aBezier = occ::down_cast<Geom_BezierCurve>(aBasisCurve))
  {
    myCurveType = GeomAbs_BezierCurve;
    myEvaluator.emplace<GeomGridEval_BezierCurve>(aBezier);
  }
  else if (auto aBSpline = occ::down_cast<Geom_BSplineCurve>(aBasisCurve))
  {
    myCurveType = GeomAbs_BSplineCurve;
    myEvaluator.emplace<GeomGridEval_BSplineCurve>(aBSpline);
  }
  else if (auto anOffset = occ::down_cast<Geom_OffsetCurve>(aBasisCurve))
  {
    myCurveType = GeomAbs_OffsetCurve;
    myEvaluator.emplace<GeomGridEval_OffsetCurve>(anOffset);
  }
  else
  {

    myEvaluator.emplace<std::monostate>();
    myCurveType = GeomAbs_OtherCurve;
  }
}

bool GeomGridEval_Curve::IsInitialized() const
{
  return !std::holds_alternative<std::monostate>(myEvaluator);
}

NCollection_Array1<gp_Pnt> GeomGridEval_Curve::EvaluateGrid(
  const NCollection_Array1<double>& theParams) const
{
  return std::visit(
    [&theParams](const auto& theEval) -> NCollection_Array1<gp_Pnt>
    {
      using T = std::decay_t<decltype(theEval)>;
      if constexpr (std::is_same_v<T, std::monostate>)
      {
        return NCollection_Array1<gp_Pnt>();
      }
      else
      {
        return theEval.EvaluateGrid(theParams);
      }
    },
    myEvaluator);
}

NCollection_Array1<GeomGridEval::CurveD1> GeomGridEval_Curve::EvaluateGridD1(
  const NCollection_Array1<double>& theParams) const
{
  return std::visit(
    [&theParams](const auto& theEval) -> NCollection_Array1<GeomGridEval::CurveD1>
    {
      using T = std::decay_t<decltype(theEval)>;
      if constexpr (std::is_same_v<T, std::monostate>)
      {
        return NCollection_Array1<GeomGridEval::CurveD1>();
      }
      else
      {
        return theEval.EvaluateGridD1(theParams);
      }
    },
    myEvaluator);
}

NCollection_Array1<GeomGridEval::CurveD2> GeomGridEval_Curve::EvaluateGridD2(
  const NCollection_Array1<double>& theParams) const
{
  return std::visit(
    [&theParams](const auto& theEval) -> NCollection_Array1<GeomGridEval::CurveD2>
    {
      using T = std::decay_t<decltype(theEval)>;
      if constexpr (std::is_same_v<T, std::monostate>)
      {
        return NCollection_Array1<GeomGridEval::CurveD2>();
      }
      else
      {
        return theEval.EvaluateGridD2(theParams);
      }
    },
    myEvaluator);
}

NCollection_Array1<GeomGridEval::CurveD3> GeomGridEval_Curve::EvaluateGridD3(
  const NCollection_Array1<double>& theParams) const
{
  return std::visit(
    [&theParams](const auto& theEval) -> NCollection_Array1<GeomGridEval::CurveD3>
    {
      using T = std::decay_t<decltype(theEval)>;
      if constexpr (std::is_same_v<T, std::monostate>)
      {
        return NCollection_Array1<GeomGridEval::CurveD3>();
      }
      else
      {
        return theEval.EvaluateGridD3(theParams);
      }
    },
    myEvaluator);
}

NCollection_Array1<gp_Vec> GeomGridEval_Curve::EvaluateGridDN(
  const NCollection_Array1<double>& theParams,
  int                               theN) const
{
  return std::visit(
    [&theParams, theN](const auto& theEval) -> NCollection_Array1<gp_Vec>
    {
      using T = std::decay_t<decltype(theEval)>;
      if constexpr (std::is_same_v<T, std::monostate>)
      {
        return NCollection_Array1<gp_Vec>();
      }
      else
      {
        return theEval.EvaluateGridDN(theParams, theN);
      }
    },
    myEvaluator);
}
