#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class Contap_Contour;
class HLRTopoBRep_Data;
class TopoDS_Face;
class TopoDS_Vertex;
class Contap_Point;
class TopoDS_Edge;

class HLRTopoBRep_DSFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Insert(
    const TopoDS_Shape&                                                              S,
    Contap_Contour&                                                                  FO,
    HLRTopoBRep_Data&                                                                DS,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST,
    const int                                                                        nbIso);

private:
  Standard_EXPORT static void InsertFace(const int          FI,
                                         const TopoDS_Face& F,
                                         Contap_Contour&    FO,
                                         HLRTopoBRep_Data&  DS,
                                         const bool         withPCurve);

  Standard_EXPORT static TopoDS_Vertex MakeVertex(const Contap_Point& P,
                                                  const double        tol,
                                                  HLRTopoBRep_Data&   DS);

  Standard_EXPORT static void InsertVertex(const Contap_Point& P,
                                           const double        tol,
                                           const TopoDS_Edge&  E,
                                           HLRTopoBRep_Data&   DS);

  Standard_EXPORT static void ProcessEdges(HLRTopoBRep_Data& DS);
};
