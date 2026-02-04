#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Geom2dAdaptor_Curve.hpp>

//! The Curve2d from BRepAdaptor allows to use an Edge
//! on a Face like a 2d curve (curve in the parametric
//! space).
//!
//! It has the methods of the class Curve2d from
//! Adpator.
//!
//! It is created or initialized with a Face and an
//! Edge. The methods are inherited from Curve from
//! Geom2dAdaptor.
class BRepAdaptor_Curve2d : public Geom2dAdaptor_Curve
{
  DEFINE_STANDARD_RTTIEXT(BRepAdaptor_Curve2d, Geom2dAdaptor_Curve)
public:
  //! Creates an uninitialized curve2d.
  Standard_EXPORT BRepAdaptor_Curve2d();

  //! Creates with the pcurve of <E> on <F>.
  Standard_EXPORT BRepAdaptor_Curve2d(const TopoDS_Edge& E, const TopoDS_Face& F);

  //! Shallow copy of adaptor
  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  //! Initialize with the pcurve of <E> on <F>.
  Standard_EXPORT void Initialize(const TopoDS_Edge& E, const TopoDS_Face& F);

  //! Returns the Edge.
  Standard_EXPORT const TopoDS_Edge& Edge() const;

  //! Returns the Face.
  Standard_EXPORT const TopoDS_Face& Face() const;

private:
  TopoDS_Edge myEdge;
  TopoDS_Face myFace;
};

