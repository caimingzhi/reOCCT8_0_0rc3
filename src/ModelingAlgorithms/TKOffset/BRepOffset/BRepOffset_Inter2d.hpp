#pragma once

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Message_ProgressRange.hpp>

class BRepAlgo_AsDes;
class BRepAlgo_Image;
class BRepOffset_Analyse;
class BRepOffset_Offset;
class TopoDS_Edge;
class TopoDS_Face;

class BRepOffset_Inter2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Compute(
    const occ::handle<BRepAlgo_AsDes>&                                   AsDes,
    const TopoDS_Face&                                                   F,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& NewEdges,
    const double                                                         Tol,
    const NCollection_DataMap<TopoDS_Shape,
                              NCollection_List<TopoDS_Shape>,
                              TopTools_ShapeMapHasher>&                  theEdgeIntEdges,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>&                 theDMVV,
    const Message_ProgressRange&                                         theRange);

  Standard_EXPORT static bool ConnexIntByInt(
    const TopoDS_Face&                                                              FI,
    BRepOffset_Offset&                                                              OFI,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&       MES,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& Build,
    const occ::handle<BRepAlgo_AsDes>&                                              theAsDes,
    const occ::handle<BRepAlgo_AsDes>&                                              AsDes2d,
    const double                                                                    Offset,
    const double                                                                    Tol,
    const BRepOffset_Analyse&                                                       Analyse,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&                  FacesWithVerts,
    BRepAlgo_Image&                                                                 theImageVV,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                         theEdgeIntEdges,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& theDMVV,
    const Message_ProgressRange&                         theRange);

  Standard_EXPORT static void ConnexIntByIntInVert(
    const TopoDS_Face&                                                              FI,
    BRepOffset_Offset&                                                              OFI,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&       MES,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& Build,
    const occ::handle<BRepAlgo_AsDes>&                                              AsDes,
    const occ::handle<BRepAlgo_AsDes>&                                              AsDes2d,
    const double                                                                    Tol,
    const BRepOffset_Analyse&                                                       Analyse,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>&                            theDMVV,
    const Message_ProgressRange&                                                    theRange);

  Standard_EXPORT static bool FuseVertices(
    const NCollection_IndexedDataMap<TopoDS_Shape,
                                     NCollection_List<TopoDS_Shape>,
                                     TopTools_ShapeMapHasher>& theDMVV,
    const occ::handle<BRepAlgo_AsDes>&                         theAsDes,
    BRepAlgo_Image&                                            theImageVV);

  Standard_EXPORT static bool ExtentEdge(const TopoDS_Edge& E,
                                         TopoDS_Edge&       NE,
                                         const double       theOffset);
};
