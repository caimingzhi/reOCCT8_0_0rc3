#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>
#include <gp_Trsf.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomFill_Trihedron.hpp>
class BRepFill_LocationLaw;
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Vertex;
class gp_Pnt;
class BRepFill_Sweep;

class BRepFill_Pipe
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Pipe();

  Standard_EXPORT BRepFill_Pipe(const TopoDS_Wire&       Spine,
                                const TopoDS_Shape&      Profile,
                                const GeomFill_Trihedron aMode         = GeomFill_IsCorrectedFrenet,
                                const bool               ForceApproxC1 = false,
                                const bool               GeneratePartCase = false);

  Standard_EXPORT void Perform(const TopoDS_Wire&  Spine,
                               const TopoDS_Shape& Profile,
                               const bool          GeneratePartCase = false);

  Standard_EXPORT const TopoDS_Shape& Spine() const;

  Standard_EXPORT const TopoDS_Shape& Profile() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT double ErrorOnSurface() const;

  Standard_EXPORT const TopoDS_Shape& FirstShape() const;

  Standard_EXPORT const TopoDS_Shape& LastShape() const;

  Standard_EXPORT void Generated(const TopoDS_Shape& S, NCollection_List<TopoDS_Shape>& L);

  Standard_EXPORT TopoDS_Face Face(const TopoDS_Edge& ESpine, const TopoDS_Edge& EProfile);

  Standard_EXPORT TopoDS_Edge Edge(const TopoDS_Edge& ESpine, const TopoDS_Vertex& VProfile);

  Standard_EXPORT TopoDS_Shape Section(const TopoDS_Vertex& VSpine) const;

  Standard_EXPORT TopoDS_Wire PipeLine(const gp_Pnt& Point);

private:
  Standard_EXPORT TopoDS_Shape MakeShape(const TopoDS_Shape& S,
                                         const TopoDS_Shape& theOriginalS,
                                         const TopoDS_Shape& FirstShape,
                                         const TopoDS_Shape& LastShape);

  Standard_EXPORT int FindEdge(const TopoDS_Shape& S, const TopoDS_Edge& E, int& Init) const;

  Standard_EXPORT int FindVertex(const TopoDS_Shape& S, const TopoDS_Vertex& V, int& Init) const;

  Standard_EXPORT void DefineRealSegmax();

  Standard_EXPORT void RebuildTopOrBottomFace(const TopoDS_Shape& aFace, const bool IsTop) const;

  Standard_EXPORT void BuildHistory(const BRepFill_Sweep& theSweep, const TopoDS_Shape& theSection);

  TopoDS_Wire                                            mySpine;
  TopoDS_Shape                                           myProfile;
  TopoDS_Shape                                           myShape;
  gp_Trsf                                                myTrsf;
  occ::handle<BRepFill_LocationLaw>                      myLoc;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>         mySections;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>         myFaces;
  occ::handle<NCollection_HArray2<TopoDS_Shape>>         myEdges;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myReversedEdges;
  NCollection_DataMap<TopoDS_Shape,
                      occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                      TopTools_ShapeMapHasher>
    myTapes;
  NCollection_DataMap<TopoDS_Shape,
                      occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                      TopTools_ShapeMapHasher>
               myRails;
  int          myCurIndexOfSectionEdge;
  TopoDS_Shape myFirst;
  TopoDS_Shape myLast;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                     myGenMap;
  int                myDegmax;
  int                mySegmax;
  GeomAbs_Shape      myContinuity;
  GeomFill_Trihedron myMode;
  bool               myForceApproxC1;
  double             myErrorOnSurf;
};
