#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Real.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_IndexedMap.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;
class BRepOffset_Analyse;
class TopoDS_Wire;
class TopoDS_Shape;
class BRepAlgo_AsDes;
class BRepAlgo_Image;
class Geom_Curve;

class BRepOffset_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void EdgeVertices(const TopoDS_Edge& E,
                                           TopoDS_Vertex&     V1,
                                           TopoDS_Vertex&     V2);

  Standard_EXPORT static void OrientSection(const TopoDS_Edge&  E,
                                            const TopoDS_Face&  F1,
                                            const TopoDS_Face&  F2,
                                            TopAbs_Orientation& O1,
                                            TopAbs_Orientation& O2);

  Standard_EXPORT static bool FindCommonShapes(const TopoDS_Face&              theF1,
                                               const TopoDS_Face&              theF2,
                                               NCollection_List<TopoDS_Shape>& theLE,
                                               NCollection_List<TopoDS_Shape>& theLV);

  Standard_EXPORT static bool FindCommonShapes(const TopoDS_Shape&             theS1,
                                               const TopoDS_Shape&             theS2,
                                               const TopAbs_ShapeEnum          theType,
                                               NCollection_List<TopoDS_Shape>& theLSC);

  Standard_EXPORT static void Inter3D(const TopoDS_Face&              F1,
                                      const TopoDS_Face&              F2,
                                      NCollection_List<TopoDS_Shape>& LInt1,
                                      NCollection_List<TopoDS_Shape>& LInt2,
                                      const TopAbs_State              Side,
                                      const TopoDS_Edge&              RefEdge,
                                      const TopoDS_Face&              RefFace1,
                                      const TopoDS_Face&              RefFace2);

  Standard_EXPORT static bool TryProject(const TopoDS_Face&                    F1,
                                         const TopoDS_Face&                    F2,
                                         const NCollection_List<TopoDS_Shape>& Edges,
                                         NCollection_List<TopoDS_Shape>&       LInt1,
                                         NCollection_List<TopoDS_Shape>&       LInt2,
                                         const TopAbs_State                    Side,
                                         const double                          TolConf);

  Standard_EXPORT static void PipeInter(const TopoDS_Face&              F1,
                                        const TopoDS_Face&              F2,
                                        NCollection_List<TopoDS_Shape>& LInt1,
                                        NCollection_List<TopoDS_Shape>& LInt2,
                                        const TopAbs_State              Side);

  Standard_EXPORT static void Inter2d(const TopoDS_Face&              F,
                                      const TopoDS_Edge&              E1,
                                      const TopoDS_Edge&              E2,
                                      NCollection_List<TopoDS_Shape>& LV,
                                      const double                    Tol);

  Standard_EXPORT static void InterOrExtent(const TopoDS_Face&              F1,
                                            const TopoDS_Face&              F2,
                                            NCollection_List<TopoDS_Shape>& LInt1,
                                            NCollection_List<TopoDS_Shape>& LInt2,
                                            const TopAbs_State              Side);

  Standard_EXPORT static void CheckBounds(const TopoDS_Face&        F,
                                          const BRepOffset_Analyse& Analyse,
                                          bool&                     enlargeU,
                                          bool&                     enlargeVfirst,
                                          bool&                     enlargeVlast);

  Standard_EXPORT static bool EnLargeFace(const TopoDS_Face& F,
                                          TopoDS_Face&       NF,
                                          const bool         ChangeGeom,
                                          const bool         UpDatePCurve       = false,
                                          const bool         enlargeU           = true,
                                          const bool         enlargeVfirst      = true,
                                          const bool         enlargeVlast       = true,
                                          const int          theExtensionMode   = 1,
                                          const double       theLenBeforeUfirst = -1.,
                                          const double       theLenAfterUlast   = -1.,
                                          const double       theLenBeforeVfirst = -1.,
                                          const double       theLenAfterVlast   = -1.);

  Standard_EXPORT static void ExtentFace(
    const TopoDS_Face&                                                        F,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& ConstShapes,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& ToBuild,
    const TopAbs_State                                                        Side,
    const double                                                              TolConf,
    TopoDS_Face&                                                              NF);

  Standard_EXPORT static void BuildNeighbour(
    const TopoDS_Wire&                                                        W,
    const TopoDS_Face&                                                        F,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& NOnV1,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& NOnV2);

  Standard_EXPORT static void MapVertexEdges(
    const TopoDS_Shape& S,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      MVE);

  Standard_EXPORT static TopoDS_Shape Deboucle3D(
    const TopoDS_Shape&                                           S,
    const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& Boundary);

  Standard_EXPORT static void CorrectOrientation(
    const TopoDS_Shape&                                                  SI,
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& NewEdges,
    occ::handle<BRepAlgo_AsDes>&                                         AsDes,
    BRepAlgo_Image&                                                      InitOffset,
    const double                                                         Offset);

  Standard_EXPORT static double Gabarit(const occ::handle<Geom_Curve>& aCurve);

  Standard_EXPORT static bool CheckPlanesNormals(const TopoDS_Face& theFace1,
                                                 const TopoDS_Face& theFace2,
                                                 const double       theTolAng = 1.e-8);
};
