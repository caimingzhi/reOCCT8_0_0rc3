#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
class TopoDS_Face;
class TopoDS_Edge;

class TopOpeBRepTool_REGUS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_REGUS();

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& S() const;

  Standard_EXPORT bool MapS();

  Standard_EXPORT static bool WireToFace(const TopoDS_Face&                    Fanc,
                                         const NCollection_List<TopoDS_Shape>& nWs,
                                         NCollection_List<TopoDS_Shape>&       nFs);

  Standard_EXPORT static bool SplitF(const TopoDS_Face&              Fanc,
                                     NCollection_List<TopoDS_Shape>& FSplits);

  Standard_EXPORT bool SplitFaces();

  Standard_EXPORT bool REGU();

  Standard_EXPORT void SetFsplits(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      Fsplits);

  Standard_EXPORT void GetFsplits(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      Fsplits) const;

  Standard_EXPORT void SetOshNsh(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OshNsh);

  Standard_EXPORT void GetOshNsh(
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      OshNsh) const;

  Standard_EXPORT bool InitBlock();

  Standard_EXPORT bool NextinBlock();

  Standard_EXPORT bool NearestF(const TopoDS_Edge&                    e,
                                const NCollection_List<TopoDS_Shape>& lof,
                                TopoDS_Face&                          ffound) const;

private:
  bool hasnewsplits;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myFsplits;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
               myOshNsh;
  TopoDS_Shape myS;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mymapeFsstatic;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                mymapeFs;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mymapemult;
  int                                                           mynF;
  int                                                           myoldnF;
  TopoDS_Shape                                                  myf;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>        myedstoconnect;
  NCollection_List<TopoDS_Shape>                                mylFinBlock;
};
