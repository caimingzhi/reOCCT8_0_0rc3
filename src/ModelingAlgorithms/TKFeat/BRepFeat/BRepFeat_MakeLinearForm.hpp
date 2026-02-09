#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepFeat_RibSlot.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class Geom_Plane;
class TopoDS_Shape;
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class gp_Pnt;

class BRepFeat_MakeLinearForm : public BRepFeat_RibSlot
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakeLinearForm();

  BRepFeat_MakeLinearForm(const TopoDS_Shape&            Sbase,
                          const TopoDS_Wire&             W,
                          const occ::handle<Geom_Plane>& P,
                          const gp_Vec&                  Direction,
                          const gp_Vec&                  Direction1,
                          const int                      Fuse,
                          const bool                     Modify);

  Standard_EXPORT void Init(const TopoDS_Shape&            Sbase,
                            const TopoDS_Wire&             W,
                            const occ::handle<Geom_Plane>& P,
                            const gp_Vec&                  Direction,
                            const gp_Vec&                  Direction1,
                            const int                      Fuse,
                            const bool                     Modify);

  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform();

  Standard_EXPORT void TransformShapeFU(const int flag);

  Standard_EXPORT bool Propagate(NCollection_List<TopoDS_Shape>& L,
                                 const TopoDS_Face&              F,
                                 const gp_Pnt&                   FPoint,
                                 const gp_Pnt&                   LPoint,
                                 bool&                           falseside);

private:
  occ::handle<Geom_Curve> myCrv;
  gp_Vec                  myDir;
  gp_Vec                  myDir1;
  occ::handle<Geom_Plane> myPln;
  double                  myBnd;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 mySlface;
  NCollection_List<TopoDS_Shape> myListOfEdges;
  double                         myTol;
};

inline BRepFeat_MakeLinearForm::BRepFeat_MakeLinearForm()
    : myBnd(0.0),
      myTol(0.0)
{
}

inline BRepFeat_MakeLinearForm::BRepFeat_MakeLinearForm(const TopoDS_Shape&            Sbase,
                                                        const TopoDS_Wire&             W,
                                                        const occ::handle<Geom_Plane>& P,
                                                        const gp_Vec&                  Direc,
                                                        const gp_Vec&                  Direc1,
                                                        const int                      Fuse,
                                                        const bool                     Modify)

{
  Init(Sbase, W, P, Direc, Direc1, Fuse, Modify);
}
