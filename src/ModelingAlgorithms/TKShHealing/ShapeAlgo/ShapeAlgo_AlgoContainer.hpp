#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_BoundedCurve.hpp>
#include <NCollection_HSequence.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class ShapeAlgo_ToolContainer;
class ShapeAnalysis_Wire;
class ShapeExtend_WireData;
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;
class TopoDS_Shape;
class Geom_BSplineSurface;
class Geom_Surface;
class TopoDS_Wire;
class TopoDS_Face;
class Geom_Curve;

class ShapeAlgo_AlgoContainer : public Standard_Transient
{

public:
  Standard_EXPORT ShapeAlgo_AlgoContainer();

  void SetToolContainer(const occ::handle<ShapeAlgo_ToolContainer>& TC);

  occ::handle<ShapeAlgo_ToolContainer> ToolContainer() const;

  Standard_EXPORT virtual bool ConnectNextWire(const occ::handle<ShapeAnalysis_Wire>&   saw,
                                               const occ::handle<ShapeExtend_WireData>& nextsewd,
                                               const double                             maxtol,
                                               double&                                  distmin,
                                               bool&                                    revsewd,
                                               bool& revnextsewd) const;

  Standard_EXPORT virtual void ApproxBSplineCurve(
    const occ::handle<Geom_BSplineCurve>&          bspline,
    NCollection_Sequence<occ::handle<Geom_Curve>>& seq) const;

  Standard_EXPORT virtual void ApproxBSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&          bspline,
    NCollection_Sequence<occ::handle<Geom2d_Curve>>& seq) const;

  Standard_EXPORT virtual bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom_BoundedCurve>>>& seqBS) const;

  Standard_EXPORT virtual bool C0BSplineToSequenceOfC1BSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>&                               BS,
    occ::handle<NCollection_HSequence<occ::handle<Geom2d_BoundedCurve>>>& seqBS) const;

  Standard_EXPORT virtual TopoDS_Shape C0ShapeToC1Shape(const TopoDS_Shape& shape,
                                                        const double        tol) const;

  Standard_EXPORT virtual occ::handle<Geom_BSplineSurface> ConvertSurfaceToBSpline(
    const occ::handle<Geom_Surface>& surf,
    const double                     UF,
    const double                     UL,
    const double                     VF,
    const double                     VL) const;

  Standard_EXPORT virtual bool HomoWires(const TopoDS_Wire& wireIn1,
                                         const TopoDS_Wire& wireIn2,
                                         TopoDS_Wire&       wireOut1,
                                         TopoDS_Wire&       wireOut2,
                                         const bool         byParam) const;

  Standard_EXPORT virtual TopoDS_Wire OuterWire(const TopoDS_Face& face) const;

  Standard_EXPORT virtual occ::handle<Geom_Surface> ConvertToPeriodic(
    const occ::handle<Geom_Surface>& surf) const;

  Standard_EXPORT virtual void GetFaceUVBounds(const TopoDS_Face& F,
                                               double&            Umin,
                                               double&            Umax,
                                               double&            Vmin,
                                               double&            Vmax) const;

  Standard_EXPORT virtual occ::handle<Geom_BSplineCurve> ConvertCurveToBSpline(
    const occ::handle<Geom_Curve>& C3D,
    const double                   First,
    const double                   Last,
    const double                   Tol3d,
    const GeomAbs_Shape            Continuity,
    const int                      MaxSegments,
    const int                      MaxDegree) const;

  DEFINE_STANDARD_RTTIEXT(ShapeAlgo_AlgoContainer, Standard_Transient)

private:
  occ::handle<ShapeAlgo_ToolContainer> myTC;
};

#include <ShapeAlgo_AlgoContainer.hpp>

inline void ShapeAlgo_AlgoContainer::SetToolContainer(
  const occ::handle<ShapeAlgo_ToolContainer>& TC)
{
  myTC = TC;
}

inline occ::handle<ShapeAlgo_ToolContainer> ShapeAlgo_AlgoContainer::ToolContainer() const
{
  return myTC;
}
