#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Wire;
class TopoDS_Face;
class ShapeExtend_WireData;
class TopoDS_Shape;
class TopoDS_Vertex;

class ShapeAnalysis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Wire OuterWire(const TopoDS_Face& theFace);

  Standard_EXPORT static double TotCross2D(const occ::handle<ShapeExtend_WireData>& sewd,
                                           const TopoDS_Face&                       aFace);

  Standard_EXPORT static double ContourArea(const TopoDS_Wire& theWire);

  Standard_EXPORT static bool IsOuterBound(const TopoDS_Face& face);

  Standard_EXPORT static double AdjustByPeriod(const double Val,
                                               const double ToVal,
                                               const double Period);

  Standard_EXPORT static double AdjustToPeriod(const double Val,
                                               const double ValMin,
                                               const double ValMax);

  Standard_EXPORT static void FindBounds(const TopoDS_Shape& shape,
                                         TopoDS_Vertex&      V1,
                                         TopoDS_Vertex&      V2);

  Standard_EXPORT static void GetFaceUVBounds(const TopoDS_Face& F,
                                              double&            Umin,
                                              double&            Umax,
                                              double&            Vmin,
                                              double&            Vmax);
};
