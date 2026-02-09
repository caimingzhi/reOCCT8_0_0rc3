#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Ax1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepFeat_RibSlot.hpp>
#include <Standard_Integer.hpp>
class Geom_Plane;
class TopoDS_Shape;
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class gp_Pnt;

class BRepFeat_MakeRevolutionForm : public BRepFeat_RibSlot
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakeRevolutionForm();

  BRepFeat_MakeRevolutionForm(const TopoDS_Shape&            Sbase,
                              const TopoDS_Wire&             W,
                              const occ::handle<Geom_Plane>& Plane,
                              const gp_Ax1&                  Axis,
                              const double                   Height1,
                              const double                   Height2,
                              const int                      Fuse,
                              bool&                          Sliding);

  Standard_EXPORT void Init(const TopoDS_Shape&            Sbase,
                            const TopoDS_Wire&             W,
                            const occ::handle<Geom_Plane>& Plane,
                            const gp_Ax1&                  Axis,
                            const double                   Height1,
                            const double                   Height2,
                            const int                      Fuse,
                            bool&                          Sliding);

  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool Propagate(NCollection_List<TopoDS_Shape>& L,
                                 const TopoDS_Face&              F,
                                 const gp_Pnt&                   FPoint,
                                 const gp_Pnt&                   LPoint,
                                 bool&                           falseside);

private:
  gp_Ax1                  myAxe;
  double                  myHeight1;
  double                  myHeight2;
  bool                    mySliding;
  occ::handle<Geom_Plane> myPln;
  double                  myBnd;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 mySlface;
  NCollection_List<TopoDS_Shape> myListOfEdges;
  double                         myTol;
  double                         myAngle1;
  double                         myAngle2;
};

inline BRepFeat_MakeRevolutionForm::BRepFeat_MakeRevolutionForm()
    : myHeight1(0.0),
      myHeight2(0.0),
      mySliding(false),
      myBnd(0.0),
      myTol(0.0),
      myAngle1(RealLast()),
      myAngle2(RealLast())
{
}

inline BRepFeat_MakeRevolutionForm::BRepFeat_MakeRevolutionForm(const TopoDS_Shape& Sbase,
                                                                const TopoDS_Wire&  W,
                                                                const occ::handle<Geom_Plane>& P,
                                                                const gp_Ax1&                  Axis,
                                                                const double                   H1,
                                                                const double                   H2,
                                                                const int                      Fuse,
                                                                bool& Sliding)

{
  Init(Sbase, W, P, Axis, H1, H2, Fuse, Sliding);
}
