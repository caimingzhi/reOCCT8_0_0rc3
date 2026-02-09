#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepAlgo_NormalProjection.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <GeomAbs_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TopoDS_Edge;

class BRepOffsetAPI_NormalProjection : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_NormalProjection();

  Standard_EXPORT BRepOffsetAPI_NormalProjection(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Add(const TopoDS_Shape& ToProj);

  Standard_EXPORT void SetParams(const double        Tol3D,
                                 const double        Tol2D,
                                 const GeomAbs_Shape InternalContinuity,
                                 const int           MaxDegree,
                                 const int           MaxSeg);

  Standard_EXPORT void SetMaxDistance(const double MaxDist);

  Standard_EXPORT void SetLimit(const bool FaceBoundaries = true);

  Standard_EXPORT void Compute3d(const bool With3d = true);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT const TopoDS_Shape& Projection() const;

  Standard_EXPORT const TopoDS_Shape& Couple(const TopoDS_Edge& E) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT const TopoDS_Shape& Ancestor(const TopoDS_Edge& E) const;

  Standard_EXPORT bool BuildWire(NCollection_List<TopoDS_Shape>& Liste) const;

private:
  BRepAlgo_NormalProjection myNormalProjector;
};
