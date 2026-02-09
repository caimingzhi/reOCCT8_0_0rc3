#pragma once

#include <GeomAbs_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;

class BRepAlgo
{
public:
  Standard_EXPORT static TopoDS_Wire ConcatenateWire(const TopoDS_Wire&  Wire,
                                                     const GeomAbs_Shape Option,
                                                     const double        AngularTolerance = 1.0e-4);

  Standard_EXPORT static TopoDS_Edge ConcatenateWireC0(const TopoDS_Wire& Wire);

  static Standard_EXPORT TopoDS_Wire ConvertWire(const TopoDS_Wire& theWire,
                                                 const double       theAngleTolerance,
                                                 const TopoDS_Face& theFace);

  static Standard_EXPORT TopoDS_Face ConvertFace(const TopoDS_Face& theFace,
                                                 const double       theAngleTolerance);

  Standard_EXPORT static bool IsValid(const TopoDS_Shape& S);

  Standard_EXPORT static bool IsValid(const NCollection_List<TopoDS_Shape>& theArgs,
                                      const TopoDS_Shape&                   theResult,
                                      const bool                            closedSolid = false,
                                      const bool                            GeomCtrl    = true);

  Standard_EXPORT static bool IsTopologicallyValid(const TopoDS_Shape& S);
};
