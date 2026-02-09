#pragma once

#include <TopTools_FormatVersion.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Message_ProgressRange.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class TopoDS_Face;
class TopoDS_Wire;
class TopoDS_Edge;
class Bnd_Box2d;
class TopoDS_Vertex;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;
class TopoDS_Shape;
class BRep_Builder;
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;
class OSD_FileSystem;

class BRepTools
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void UVBounds(const TopoDS_Face& F,
                                       double&            UMin,
                                       double&            UMax,
                                       double&            VMin,
                                       double&            VMax);

  Standard_EXPORT static void UVBounds(const TopoDS_Face& F,
                                       const TopoDS_Wire& W,
                                       double&            UMin,
                                       double&            UMax,
                                       double&            VMin,
                                       double&            VMax);

  Standard_EXPORT static void UVBounds(const TopoDS_Face& F,
                                       const TopoDS_Edge& E,
                                       double&            UMin,
                                       double&            UMax,
                                       double&            VMin,
                                       double&            VMax);

  Standard_EXPORT static void AddUVBounds(const TopoDS_Face& F, Bnd_Box2d& B);

  Standard_EXPORT static void AddUVBounds(const TopoDS_Face& F, const TopoDS_Wire& W, Bnd_Box2d& B);

  Standard_EXPORT static void AddUVBounds(const TopoDS_Face& F, const TopoDS_Edge& E, Bnd_Box2d& B);

  Standard_EXPORT static void Update(const TopoDS_Vertex& V);

  Standard_EXPORT static void Update(const TopoDS_Edge& E);

  Standard_EXPORT static void Update(const TopoDS_Wire& W);

  Standard_EXPORT static void Update(const TopoDS_Face& F);

  Standard_EXPORT static void Update(const TopoDS_Shell& S);

  Standard_EXPORT static void Update(const TopoDS_Solid& S);

  Standard_EXPORT static void Update(const TopoDS_CompSolid& C);

  Standard_EXPORT static void Update(const TopoDS_Compound& C);

  Standard_EXPORT static void Update(const TopoDS_Shape& S);

  Standard_EXPORT static void UpdateFaceUVPoints(const TopoDS_Face& theF);

  Standard_EXPORT static void Clean(const TopoDS_Shape& theShape, const bool theForce = false);

  Standard_EXPORT static void CleanGeometry(const TopoDS_Shape& theShape);

  Standard_EXPORT static void RemoveUnusedPCurves(const TopoDS_Shape& S);

public:
  Standard_EXPORT static bool Triangulation(const TopoDS_Shape& theShape,
                                            const double        theLinDefl,
                                            const bool          theToCheckFreeEdges = false);

  Standard_EXPORT static bool LoadTriangulation(
    const TopoDS_Shape&                theShape,
    const int                          theTriangulationIdx = -1,
    const bool                         theToSetAsActive    = false,
    const occ::handle<OSD_FileSystem>& theFileSystem       = occ::handle<OSD_FileSystem>());

  Standard_EXPORT static bool UnloadTriangulation(const TopoDS_Shape& theShape,
                                                  const int           theTriangulationIdx = -1);

  Standard_EXPORT static bool ActivateTriangulation(const TopoDS_Shape& theShape,
                                                    const int           theTriangulationIdx,
                                                    const bool theToActivateStrictly = false);

  Standard_EXPORT static bool LoadAllTriangulations(
    const TopoDS_Shape&                theShape,
    const occ::handle<OSD_FileSystem>& theFileSystem = occ::handle<OSD_FileSystem>());

  Standard_EXPORT static bool UnloadAllTriangulations(const TopoDS_Shape& theShape);

public:
  Standard_EXPORT static bool Compare(const TopoDS_Vertex& V1, const TopoDS_Vertex& V2);

  Standard_EXPORT static bool Compare(const TopoDS_Edge& E1, const TopoDS_Edge& E2);

  Standard_EXPORT static TopoDS_Wire OuterWire(const TopoDS_Face& F);

  Standard_EXPORT static void Map3DEdges(
    const TopoDS_Shape&                                            S,
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& M);

  Standard_EXPORT static bool IsReallyClosed(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT static void DetectClosedness(const TopoDS_Face& theFace,
                                               bool&              theUclosed,
                                               bool&              theVclosed);

  Standard_EXPORT static void Dump(const TopoDS_Shape& Sh, Standard_OStream& S);

  static void Write(const TopoDS_Shape&          theShape,
                    Standard_OStream&            theStream,
                    const Message_ProgressRange& theProgress = Message_ProgressRange())
  {
    Write(theShape, theStream, true, false, TopTools_FormatVersion_CURRENT, theProgress);
  }

  Standard_EXPORT static void Write(
    const TopoDS_Shape&          theShape,
    Standard_OStream&            theStream,
    const bool                   theWithTriangles,
    const bool                   theWithNormals,
    const TopTools_FormatVersion theVersion,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT static void Read(
    TopoDS_Shape&                Sh,
    Standard_IStream&            S,
    const BRep_Builder&          B,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  static bool Write(const TopoDS_Shape&          theShape,
                    const char*                  theFile,
                    const Message_ProgressRange& theProgress = Message_ProgressRange())
  {
    return Write(theShape, theFile, true, false, TopTools_FormatVersion_CURRENT, theProgress);
  }

  Standard_EXPORT static bool Write(
    const TopoDS_Shape&          theShape,
    const char*                  theFile,
    const bool                   theWithTriangles,
    const bool                   theWithNormals,
    const TopTools_FormatVersion theVersion,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT static bool Read(
    TopoDS_Shape&                Sh,
    const char*                  File,
    const BRep_Builder&          B,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT static double EvalAndUpdateTol(const TopoDS_Edge&               theE,
                                                 const occ::handle<Geom_Curve>&   theC3d,
                                                 const occ::handle<Geom2d_Curve>& theC2d,
                                                 const occ::handle<Geom_Surface>& theS,
                                                 const double                     theF,
                                                 const double                     theL);

  Standard_EXPORT static TopAbs_Orientation OriEdgeInFace(const TopoDS_Edge& theEdge,
                                                          const TopoDS_Face& theFace);

  Standard_EXPORT static void RemoveInternals(TopoDS_Shape& theS, const bool theForce = false);

  Standard_EXPORT static void CheckLocations(const TopoDS_Shape&             theS,
                                             NCollection_List<TopoDS_Shape>& theProblemShapes);
};
