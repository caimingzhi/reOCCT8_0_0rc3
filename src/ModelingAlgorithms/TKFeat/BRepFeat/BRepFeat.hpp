#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_OStream.hpp>
#include <BRepFeat_StatusError.hpp>
class TopoDS_Shape;
class gp_Pnt;
class Geom_Curve;
class TopoDS_Face;
class BRepTopAdaptor_FClass2d;
class Geom2dAdaptor_Curve;
class TopoDS_Solid;

class BRepFeat
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SampleEdges(const TopoDS_Shape& S, NCollection_Sequence<gp_Pnt>& Pt);

  Standard_EXPORT static void Barycenter(const TopoDS_Shape& S, gp_Pnt& Pt);

  Standard_EXPORT static double ParametricBarycenter(const TopoDS_Shape&            S,
                                                     const occ::handle<Geom_Curve>& C);

  Standard_EXPORT static void ParametricMinMax(const TopoDS_Shape&            S,
                                               const occ::handle<Geom_Curve>& C,
                                               double&                        prmin,
                                               double&                        prmax,
                                               double&                        prbmin,
                                               double&                        prbmax,
                                               bool&                          flag,
                                               const bool                     Ori = false);

  Standard_EXPORT static bool IsInside(const TopoDS_Face& F1, const TopoDS_Face& F2);

  Standard_EXPORT static bool IsInOut(const BRepTopAdaptor_FClass2d& FC,
                                      const Geom2dAdaptor_Curve&     AC);

  Standard_EXPORT static void FaceUntil(const TopoDS_Shape& S, TopoDS_Face& F);

  Standard_EXPORT static TopoDS_Solid Tool(const TopoDS_Shape&      SRef,
                                           const TopoDS_Face&       Fac,
                                           const TopAbs_Orientation Orf);

  Standard_EXPORT static Standard_OStream& Print(const BRepFeat_StatusError SE,
                                                 Standard_OStream&          S);
};
