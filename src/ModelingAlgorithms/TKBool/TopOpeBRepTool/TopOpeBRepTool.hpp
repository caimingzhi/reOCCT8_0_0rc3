#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TopOpeBRepTool_OutCurveType.hpp>
class TopoDS_Face;
class TopoDS_Solid;

class TopOpeBRepTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool PurgeClosingEdges(
    const TopoDS_Face&                                                     F,
    const TopoDS_Face&                                                     FF,
    const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld,
    NCollection_IndexedMap<TopoDS_Shape>&                                  MshNOK);

  Standard_EXPORT static bool PurgeClosingEdges(
    const TopoDS_Face&                                                     F,
    const NCollection_List<TopoDS_Shape>&                                  LOF,
    const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld,
    NCollection_IndexedMap<TopoDS_Shape>&                                  MshNOK);

  Standard_EXPORT static bool CorrectONUVISO(const TopoDS_Face& F, TopoDS_Face& Fsp);

  Standard_EXPORT static bool MakeFaces(const TopoDS_Face&                          F,
                                        const NCollection_List<TopoDS_Shape>&       LOF,
                                        const NCollection_IndexedMap<TopoDS_Shape>& MshNOK,
                                        NCollection_List<TopoDS_Shape>&             LOFF);

  Standard_EXPORT static bool Regularize(
    const TopoDS_Face&              aFace,
    NCollection_List<TopoDS_Shape>& aListOfFaces,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      ESplits);

  Standard_EXPORT static bool RegularizeWires(
    const TopoDS_Face& aFace,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OldWiresNewWires,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      ESplits);

  Standard_EXPORT static bool RegularizeFace(
    const TopoDS_Face&                                  aFace,
    const NCollection_DataMap<TopoDS_Shape,
                              NCollection_List<TopoDS_Shape>,
                              TopTools_ShapeMapHasher>& OldWiresnewWires,
    NCollection_List<TopoDS_Shape>&                     aListOfFaces);

  Standard_EXPORT static bool RegularizeShells(
    const TopoDS_Solid& aSolid,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OldSheNewShe,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      FSplits);

  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRepTool_OutCurveType OCT,
                                                 Standard_OStream&                 S);
};
