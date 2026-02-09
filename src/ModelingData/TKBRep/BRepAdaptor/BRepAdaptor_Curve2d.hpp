#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Geom2dAdaptor_Curve.hpp>

class BRepAdaptor_Curve2d : public Geom2dAdaptor_Curve
{
  DEFINE_STANDARD_RTTIEXT(BRepAdaptor_Curve2d, Geom2dAdaptor_Curve)
public:
  Standard_EXPORT BRepAdaptor_Curve2d();

  Standard_EXPORT BRepAdaptor_Curve2d(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  Standard_EXPORT void Initialize(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT const TopoDS_Face& Face() const;

private:
  TopoDS_Edge myEdge;
  TopoDS_Face myFace;
};
