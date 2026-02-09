#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BRepOffset_Analyse.hpp>
#include <BRepOffset_Offset.hpp>
#include <BRepAlgo_Image.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

enum BiTgte_ContactType
{
  BiTgte_FaceFace,
  BiTgte_FaceEdge,
  BiTgte_FaceVertex,
  BiTgte_EdgeEdge,
  BiTgte_EdgeVertex,
  BiTgte_VertexVertex
};

#include <Bnd_Box.hpp>
class BRepAlgo_AsDes;
class TopoDS_Face;
class TopoDS_Edge;
class Geom_Surface;
class Geom_Curve;
class Geom2d_Curve;
class BRepOffset_Offset;
class BRepOffset_Inter3d;

class BiTgte_Blend
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BiTgte_Blend();

  Standard_EXPORT BiTgte_Blend(const TopoDS_Shape& S,
                               const double        Radius,
                               const double        Tol,
                               const bool          NUBS);

  Standard_EXPORT void Init(const TopoDS_Shape& S,
                            const double        Radius,
                            const double        Tol,
                            const bool          NUBS);

  Standard_EXPORT void Clear();

  Standard_EXPORT void SetFaces(const TopoDS_Face& F1, const TopoDS_Face& F2);

  Standard_EXPORT void SetEdge(const TopoDS_Edge& Edge);

  Standard_EXPORT void SetStoppingFace(const TopoDS_Face& Face);

  Standard_EXPORT void Perform(const bool BuildShape = true);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape& Shape() const;

  Standard_EXPORT int NbSurfaces() const;

  Standard_EXPORT occ::handle<Geom_Surface> Surface(const int Index) const;

  Standard_EXPORT const TopoDS_Face& Face(const int Index) const;

  Standard_EXPORT void CenterLines(NCollection_List<TopoDS_Shape>& LC) const;

  Standard_EXPORT occ::handle<Geom_Surface> Surface(const TopoDS_Shape& CenterLine) const;

  Standard_EXPORT const TopoDS_Face& Face(const TopoDS_Shape& CenterLine) const;

  Standard_EXPORT BiTgte_ContactType ContactType(const int Index) const;

  Standard_EXPORT const TopoDS_Shape& SupportShape1(const int Index) const;

  Standard_EXPORT const TopoDS_Shape& SupportShape2(const int Index) const;

  Standard_EXPORT occ::handle<Geom_Curve> CurveOnShape1(const int Index) const;

  Standard_EXPORT occ::handle<Geom_Curve> CurveOnShape2(const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> PCurveOnFace1(const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> PCurve1OnFillet(const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> PCurveOnFace2(const int Index) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> PCurve2OnFillet(const int Index) const;

  Standard_EXPORT int NbBranches();

  Standard_EXPORT void IndicesOfBranche(const int Index, int& From, int& To) const;

  Standard_EXPORT void ComputeCenters();

private:
  Standard_EXPORT void ComputeSurfaces();

  Standard_EXPORT void ComputeShape();

  Standard_EXPORT bool Intersect(
    const TopoDS_Shape&                                                        Init,
    const TopoDS_Face&                                                         Face,
    const NCollection_DataMap<TopoDS_Shape, Bnd_Box, TopTools_ShapeMapHasher>& MapSBox,
    const BRepOffset_Offset&                                                   OF1,
    BRepOffset_Inter3d&                                                        Inter);

  double       myRadius;
  double       myTol;
  bool         myNubs;
  TopoDS_Shape myShape;
  TopoDS_Shape myResult;
  bool         myBuildShape;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myAncestors;
  NCollection_DataMap<
    TopoDS_Shape,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>,
    TopTools_ShapeMapHasher>
    myCreated;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                                myCutEdges;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                 myFaces;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                 myEdges;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                        myStopFaces;
  BRepOffset_Analyse                                                            myAnalyse;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>                 myCenters;
  NCollection_DataMap<TopoDS_Shape, BRepOffset_Offset, TopTools_ShapeMapHasher> myMapSF;
  BRepAlgo_Image                                                                myInitOffsetFace;
  BRepAlgo_Image                                                                myImage;
  BRepAlgo_Image                                                                myImageOffset;
  occ::handle<BRepAlgo_AsDes>                                                   myAsDes;
  int                                                                           myNbBranches;
  occ::handle<NCollection_HArray1<int>>                                         myIndices;
  bool                                                                          myDone;
};
