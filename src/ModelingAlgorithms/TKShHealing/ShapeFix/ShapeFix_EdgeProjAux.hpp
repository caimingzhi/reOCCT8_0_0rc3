#pragma once

#include <Standard.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
class Geom2d_Curve;

//! Project 3D point (vertex) on pcurves to find Vertex Parameter
//! on parametric representation of an edge
class ShapeFix_EdgeProjAux : public Standard_Transient
{

public:
  Standard_EXPORT ShapeFix_EdgeProjAux();

  Standard_EXPORT ShapeFix_EdgeProjAux(const TopoDS_Face& F, const TopoDS_Edge& E);

  Standard_EXPORT void Init(const TopoDS_Face& F, const TopoDS_Edge& E);

  Standard_EXPORT void Compute(const double preci);

  Standard_EXPORT bool IsFirstDone() const;

  Standard_EXPORT bool IsLastDone() const;

  Standard_EXPORT double FirstParam() const;

  Standard_EXPORT double LastParam() const;

  Standard_EXPORT bool IsIso(const occ::handle<Geom2d_Curve>& C);

  DEFINE_STANDARD_RTTIEXT(ShapeFix_EdgeProjAux, Standard_Transient)

protected:
  Standard_EXPORT void Init2d(const double preci);

  Standard_EXPORT void Init3d(const double preci);

  Standard_EXPORT void UpdateParam2d(const occ::handle<Geom2d_Curve>& C);

  TopoDS_Face myFace;
  TopoDS_Edge myEdge;
  double      myFirstParam;
  double      myLastParam;
  bool        myFirstDone;
  bool        myLastDone;
};
