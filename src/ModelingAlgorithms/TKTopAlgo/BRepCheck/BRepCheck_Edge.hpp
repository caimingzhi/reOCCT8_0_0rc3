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

  Standard_EXPORT void SetStatus(const BRepCheck_Status theStatus);

  void SetExactMethod(bool theIsExact) { myIsExactMethod = theIsExact; }

  bool IsExactMethod() { return myIsExactMethod; }

  Standard_EXPORT BRepCheck_Status CheckPolygonOnTriangulation(const TopoDS_Edge& theEdge);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Edge, BRepCheck_Result)

private:
  occ::handle<BRep_CurveRepresentation> myCref;
  occ::handle<Adaptor3d_Curve>          myHCurve;
  bool                                  myGctrl;
  bool                                  myIsExactMethod;
};
