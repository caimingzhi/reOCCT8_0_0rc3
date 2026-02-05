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

//! This class makes the projection of a wire on a
//! shape.
class BRepAlgo_NormalProjection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_NormalProjection();

  Standard_EXPORT BRepAlgo_NormalProjection(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  //! Add an edge or a wire to the list of shape to project
  Standard_EXPORT void Add(const TopoDS_Shape& ToProj);

  //! Set the parameters used for computation
  //! Tol3d is the required tolerance between the 3d projected
  //! curve and its 2d representation
  //! InternalContinuity is the order of constraints
  //! used for approximation.
  //! MaxDeg and MaxSeg are the maximum degree and the maximum
  //! number of segment for BSpline resulting of an approximation.
  Standard_EXPORT void SetParams(const double        Tol3D,
                                 const double        Tol2D,
                                 const GeomAbs_Shape InternalContinuity,
                                 const int           MaxDegree,
                                 const int           MaxSeg);

  //! Set the parameters used for computation
  //! in their default values
  Standard_EXPORT void SetDefaultParams();

  //! Sets the maximum distance between target shape and
  //! shape to project. If this condition is not satisfied then
  //! corresponding part of solution is discarded.
  //! if MaxDist < 0 then this method does not affect the algorithm
  Standard_EXPORT void SetMaxDistance(const double MaxDist);

  //! if With3d = false the 3dcurve is not computed
  //! the initial 3dcurve is kept to build the resulting edges.
  Standard_EXPORT void Compute3d(const bool With3d = true);

  //! Manage limitation of projected edges.
  Standard_EXPORT void SetLimit(const bool FaceBoundaries = true);

  //! Builds the result as a compound.
  Standard_EXPORT void Build();

  Standard_EXPORT bool IsDone() const;

  //! returns the result
  Standard_EXPORT const TopoDS_Shape& Projection() const;

  //! For a resulting edge, returns the corresponding initial edge.
  Standard_EXPORT const TopoDS_Shape& Ancestor(const TopoDS_Edge& E) const;

  //! For a projected edge, returns the corresponding initial face.
  Standard_EXPORT const TopoDS_Shape& Couple(const TopoDS_Edge& E) const;

  //! Returns the list of shapes generated from the
  //! shape <S>.
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  Standard_EXPORT bool IsElementary(const Adaptor3d_Curve& C) const;

  //! build the result as a list of wire if possible in --
  //! a first returns a wire only if there is only a wire.
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
