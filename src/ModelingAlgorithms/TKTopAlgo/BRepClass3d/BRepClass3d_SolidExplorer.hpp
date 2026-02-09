#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <BRepClass3d_BndBoxTree.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_State.hpp>
#include <TopExp_Explorer.hpp>
#include <NCollection_IndexedMap.hpp>

class gp_Pnt;
class TopoDS_Face;
class gp_Vec;
class TopoDS_Shell;
class gp_Lin;
class IntCurvesFace_Intersector;

class BRepClass3d_SolidExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass3d_SolidExplorer();

  Standard_EXPORT BRepClass3d_SolidExplorer(const TopoDS_Shape& S);

  Standard_EXPORT virtual ~BRepClass3d_SolidExplorer();

  Standard_EXPORT void InitShape(const TopoDS_Shape& S);

  Standard_EXPORT virtual bool Reject(const gp_Pnt& P) const;

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F, gp_Pnt& P, double& Param);

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F,
                                                  gp_Pnt&            P,
                                                  double&            u,
                                                  double&            v,
                                                  double&            Param);

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F,
                                                  gp_Pnt&            P,
                                                  double&            u,
                                                  double&            v,
                                                  double&            Param,
                                                  gp_Vec&            theVecD1U,
                                                  gp_Vec&            theVecD1V);

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F,
                                                  gp_Pnt&            P,
                                                  double&            u,
                                                  double&            v);

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F, gp_Pnt& P);

  Standard_EXPORT static bool FindAPointInTheFace(const TopoDS_Face& F, double& u, double& v);

  Standard_EXPORT bool PointInTheFace(const TopoDS_Face& F,
                                      gp_Pnt&            P,
                                      double&            u,
                                      double&            v,
                                      double&            Param,
                                      int&               Index) const;

  Standard_EXPORT bool PointInTheFace(const TopoDS_Face&                      F,
                                      gp_Pnt&                                 P,
                                      double&                                 u,
                                      double&                                 v,
                                      double&                                 Param,
                                      int&                                    Index,
                                      const occ::handle<BRepAdaptor_Surface>& surf,
                                      const double                            u1,
                                      const double                            v1,
                                      const double                            u2,
                                      const double                            v2) const;

  Standard_EXPORT bool PointInTheFace(const TopoDS_Face&                      F,
                                      gp_Pnt&                                 P,
                                      double&                                 u,
                                      double&                                 v,
                                      double&                                 Param,
                                      int&                                    Index,
                                      const occ::handle<BRepAdaptor_Surface>& surf,
                                      const double                            u1,
                                      const double                            v1,
                                      const double                            u2,
                                      const double                            v2,
                                      gp_Vec&                                 theVecD1U,
                                      gp_Vec&                                 theVecD1V) const;

  Standard_EXPORT void InitShell();

  Standard_EXPORT bool MoreShell() const;

  Standard_EXPORT void NextShell();

  Standard_EXPORT TopoDS_Shell CurrentShell() const;

  Standard_EXPORT virtual bool RejectShell(const gp_Lin& L) const;

  Standard_EXPORT void InitFace();

  Standard_EXPORT bool MoreFace() const;

  Standard_EXPORT void NextFace();

  Standard_EXPORT TopoDS_Face CurrentFace() const;

  Standard_EXPORT virtual bool RejectFace(const gp_Lin& L) const;

  Standard_EXPORT int Segment(const gp_Pnt& P, gp_Lin& L, double& Par);

  Standard_EXPORT int OtherSegment(const gp_Pnt& P, gp_Lin& L, double& Par);

  Standard_EXPORT int GetFaceSegmentIndex() const;

  Standard_EXPORT virtual void DumpSegment(const gp_Pnt&      P,
                                           const gp_Lin&      L,
                                           const double       Par,
                                           const TopAbs_State S) const;

  Standard_EXPORT const TopoDS_Shape& GetShape() const;

  Standard_EXPORT IntCurvesFace_Intersector& Intersector(const TopoDS_Face& F) const;

  const NCollection_UBTree<int, Bnd_Box>& GetTree() { return myTree; }

  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& GetMapEV()
  {
    return myMapEV;
  }

  Standard_EXPORT void Destroy();

private:
  BRepClass3d_SolidExplorer(const BRepClass3d_SolidExplorer& Oth) = delete;

protected:
  Standard_EXPORT TopAbs_State ClassifyUVPoint(const IntCurvesFace_Intersector& theIntersector,
                                               const occ::handle<BRepAdaptor_Surface>& theSurf,
                                               const gp_Pnt2d& theP2d) const;

private:
  TopoDS_Shape                                                      myShape;
  bool                                                              myReject;
  int                                                               myFirstFace;
  double                                                            myParamOnEdge;
  TopExp_Explorer                                                   myShellExplorer;
  TopExp_Explorer                                                   myFaceExplorer;
  NCollection_DataMap<TopoDS_Shape, void*, TopTools_ShapeMapHasher> myMapOfInter;
  NCollection_UBTree<int, Bnd_Box>                                  myTree;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>     myMapEV;
};
