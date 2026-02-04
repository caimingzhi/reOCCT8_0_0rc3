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

//! This package is intended to analyze geometrical objects
//! and topological shapes. Analysis domain includes both
//! exploring geometrical and topological properties of
//! shapes and checking their conformance to Open CASCADE requirements.
//! The directions of analysis provided by tools of this package are:
//! computing quantities of subshapes,
//! computing parameters of points on curve and surface,
//! computing surface singularities,
//! checking edge and wire consistency,
//! checking edges order in the wire,
//! checking face bounds orientation,
//! checking small faces,
//! analyzing shape tolerances,
//! analyzing of free bounds of the shape.
class ShapeAnalysis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns positively oriented wire in the face.
  //! If there is no such wire - returns the last wire of the face.
  Standard_EXPORT static TopoDS_Wire OuterWire(const TopoDS_Face& theFace);

  //! Returns a total area of 2d wire
  Standard_EXPORT static double TotCross2D(const occ::handle<ShapeExtend_WireData>& sewd,
                                           const TopoDS_Face&                       aFace);

  //! Returns a total area of 3d wire
  Standard_EXPORT static double ContourArea(const TopoDS_Wire& theWire);

  //! Returns True if <F> has outer bound.
  Standard_EXPORT static bool IsOuterBound(const TopoDS_Face& face);

  //! Returns a shift required to move point
  //! <Val> to the range [ToVal-Period/2,ToVal+Period/2].
  //! This shift will be the divisible by Period.
  //! Intended for adjusting parameters on periodic surfaces.
  Standard_EXPORT static double AdjustByPeriod(const double Val,
                                               const double ToVal,
                                               const double Period);

  //! Returns a shift required to move point
  //! <Val> to the range [ValMin,ValMax].
  //! This shift will be the divisible by Period
  //! with Period = ValMax - ValMin.
  //! Intended for adjusting parameters on periodic surfaces.
  Standard_EXPORT static double AdjustToPeriod(const double Val,
                                               const double ValMin,
                                               const double ValMax);

  //! Finds the start and end vertices of the shape
  //! Shape can be of the following type:
  //! vertex: V1 and V2 are the same and equal to <shape>,
  //! edge  : V1 is start and V2 is end vertex (see ShapeAnalysis_Edge
  //! methods FirstVertex and LastVertex),
  //! wire  : V1 is start vertex of the first edge, V2 is end vertex
  //! of the last edge (also see ShapeAnalysis_Edge).
  //! If wire contains no edges V1 and V2 are nullified
  //! If none of the above V1 and V2 are nullified
  Standard_EXPORT static void FindBounds(const TopoDS_Shape& shape,
                                         TopoDS_Vertex&      V1,
                                         TopoDS_Vertex&      V2);

  //! Computes exact UV bounds of all wires on the face
  Standard_EXPORT static void GetFaceUVBounds(const TopoDS_Face& F,
                                              double&            Umin,
                                              double&            Umax,
                                              double&            Vmin,
                                              double&            Vmax);
};

