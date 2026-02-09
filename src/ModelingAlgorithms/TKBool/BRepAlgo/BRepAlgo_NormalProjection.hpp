#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
class TopoDS_Edge;
class Adaptor3d_Curve;

class BRepAlgo_NormalProjection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_NormalProjection();

  Standard_EXPORT BRepAlgo_NormalProjection(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Add(const TopoDS_Shape& ToProj);

  Standard_EXPORT void SetParams(const double        Tol3D,
                                 const double        Tol2D,
                                 const GeomAbs_Shape InternalContinuity,
                                 const int           MaxDegree,
                                 const int           MaxSeg);

  Standard_EXPORT void SetDefaultParams();

  Standard_EXPORT void SetMaxDistance(const double MaxDist);

  Standard_EXPORT void Compute3d(const bool With3d = true);

  Standard_EXPORT void SetLimit(const bool FaceBoundaries = true);

  Standard_EXPORT void Build();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape& Projection() const;

  Standard_EXPORT const TopoDS_Shape& Ancestor(const TopoDS_Edge& E) const;

  Standard_EXPORT const TopoDS_Shape& Couple(const TopoDS_Edge& E) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  Standard_EXPORT bool IsElementary(const Adaptor3d_Curve& C) const;

  Standard_EXPORT bool BuildWire(NCollection_List<TopoDS_Shape>& Liste) const;

private:
  TopoDS_Shape                                                             myShape;
  bool                                                                     myIsDone;
  double                                                                   myTol3d;
  double                                                                   myTol2d;
  double                                                                   myMaxDist;
  bool                                                                     myWith3d;
  GeomAbs_Shape                                                            myContinuity;
  int                                                                      myMaxDegree;
  int                                                                      myMaxSeg;
  bool                                                                     myFaceBounds;
  TopoDS_Shape                                                             myToProj;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myAncestorMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myCorresp;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
               myDescendants;
  TopoDS_Shape myRes;
};
