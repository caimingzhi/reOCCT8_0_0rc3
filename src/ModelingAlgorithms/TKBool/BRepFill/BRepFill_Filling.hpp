#pragma once

#include <BRepFill_EdgeFaceAndOrder.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepFill_FaceAndOrder.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomPlate_BuildPlateSurface.hpp>
#include <GeomPlate_PointConstraint.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

#include <memory>

class TopoDS_Edge;
class gp_Pnt;

class BRepFill_Filling
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Filling(const int    Degree      = 3,
                                   const int    NbPtsOnCur  = 15,
                                   const int    NbIter      = 2,
                                   const bool   Anisotropie = false,
                                   const double Tol2d       = 0.00001,
                                   const double Tol3d       = 0.0001,
                                   const double TolAng      = 0.01,
                                   const double TolCurv     = 0.1,
                                   const int    MaxDeg      = 8,
                                   const int    MaxSegments = 9);

  Standard_EXPORT void SetConstrParam(const double Tol2d   = 0.00001,
                                      const double Tol3d   = 0.0001,
                                      const double TolAng  = 0.01,
                                      const double TolCurv = 0.1);

  Standard_EXPORT void SetResolParam(const int  Degree      = 3,
                                     const int  NbPtsOnCur  = 15,
                                     const int  NbIter      = 2,
                                     const bool Anisotropie = false);

  Standard_EXPORT void SetApproxParam(const int MaxDeg = 8, const int MaxSegments = 9);

  Standard_EXPORT void LoadInitSurface(const TopoDS_Face& aFace);

  Standard_EXPORT int Add(const TopoDS_Edge&  anEdge,
                          const GeomAbs_Shape Order,
                          const bool          IsBound = true);

  Standard_EXPORT int Add(const TopoDS_Edge&  anEdge,
                          const TopoDS_Face&  Support,
                          const GeomAbs_Shape Order,
                          const bool          IsBound = true);

  Standard_EXPORT int Add(const TopoDS_Face& Support, const GeomAbs_Shape Order);

  Standard_EXPORT int Add(const gp_Pnt& Point);

  Standard_EXPORT int Add(const double        U,
                          const double        V,
                          const TopoDS_Face&  Support,
                          const GeomAbs_Shape Order);

  Standard_EXPORT void Build();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT TopoDS_Face Face() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S);

  Standard_EXPORT double G0Error() const;

  Standard_EXPORT double G1Error() const;

  Standard_EXPORT double G2Error() const;

  Standard_EXPORT double G0Error(const int Index);

  Standard_EXPORT double G1Error(const int Index);

  Standard_EXPORT double G2Error(const int Index);

private:
  Standard_EXPORT void AddConstraints(
    const NCollection_Sequence<BRepFill_EdgeFaceAndOrder>& SeqOfConstraints);

  Standard_EXPORT void BuildWires(NCollection_List<TopoDS_Shape>& EdgeList,
                                  NCollection_List<TopoDS_Shape>& WireList);

  Standard_EXPORT void FindExtremitiesOfHoles(const NCollection_List<TopoDS_Shape>& WireList,
                                              NCollection_Sequence<TopoDS_Shape>&   VerSeq) const;

private:
  std::shared_ptr<GeomPlate_BuildPlateSurface>                             myBuilder;
  NCollection_Sequence<BRepFill_EdgeFaceAndOrder>                          myBoundary;
  NCollection_Sequence<BRepFill_EdgeFaceAndOrder>                          myConstraints;
  NCollection_Sequence<BRepFill_FaceAndOrder>                              myFreeConstraints;
  NCollection_Sequence<occ::handle<GeomPlate_PointConstraint>>             myPoints;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myOldNewMap;
  NCollection_List<TopoDS_Shape>                                           myGenerated;
  TopoDS_Face                                                              myFace;
  TopoDS_Face                                                              myInitFace;
  double                                                                   myTol2d;
  double                                                                   myTol3d;
  double                                                                   myTolAng;
  double                                                                   myTolCurv;
  int                                                                      myMaxDeg;
  int                                                                      myMaxSegments;
  int                                                                      myDegree;
  int                                                                      myNbPtsOnCur;
  int                                                                      myNbIter;
  bool                                                                     myAnisotropie;
  bool                                                                     myIsInitFaceGiven;
  bool                                                                     myIsDone;
};
