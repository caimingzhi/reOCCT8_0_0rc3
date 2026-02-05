#pragma once

#include <Adaptor3d_Curve.hpp>
#include <BRepCheck_Result.hpp>
#include <BRepCheck_Status.hpp>

class BRep_CurveRepresentation;
class TopoDS_Edge;
class TopoDS_Shape;

class BRepCheck_Edge : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Edge(const TopoDS_Edge& E);

  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  Standard_EXPORT bool GeometricControls() const;

  Standard_EXPORT void GeometricControls(const bool B);

  Standard_EXPORT double Tolerance();

  //! Sets status of Edge;
  Standard_EXPORT void SetStatus(const BRepCheck_Status theStatus);

  //! Sets method to calculate distance: Calculating in finite number of points (if theIsExact
  //! is false, faster, but possible not correct result) or exact calculating by using
  //! BRepLib_CheckCurveOnSurface class (if theIsExact is true, slowly, but more correctly).
  //! Exact method is used only when edge is SameParameter.
  //! Default method is calculating in finite number of points
  void SetExactMethod(bool theIsExact) { myIsExactMethod = theIsExact; }

  //! Returns true if exact method selected
  bool IsExactMethod() { return myIsExactMethod; }

  //! Checks, if polygon on triangulation of heEdge
  //! is out of 3D-curve of this edge.
  Standard_EXPORT BRepCheck_Status CheckPolygonOnTriangulation(const TopoDS_Edge& theEdge);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Edge, BRepCheck_Result)

private:
  occ::handle<BRep_CurveRepresentation> myCref;
  occ::handle<Adaptor3d_Curve>          myHCurve;
  bool                                  myGctrl;
  bool                                  myIsExactMethod;
};
