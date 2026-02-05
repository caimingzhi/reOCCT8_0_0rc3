#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
class BRepBuilderAPI_MakeShape;

class BRepBuilderAPI_Collect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_Collect();

  Standard_EXPORT void Add(const TopoDS_Shape& SI, BRepBuilderAPI_MakeShape& MKS);

  Standard_EXPORT void AddGenerated(const TopoDS_Shape& S, const TopoDS_Shape& Gen);

  Standard_EXPORT void AddModif(const TopoDS_Shape& S, const TopoDS_Shape& Mod);

  Standard_EXPORT void Filter(const TopoDS_Shape& SF);

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape,
                                            NCollection_List<TopoDS_Shape>,
                                            TopTools_ShapeMapHasher>&
                        Modification() const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape,
                                            NCollection_List<TopoDS_Shape>,
                                            TopTools_ShapeMapHasher>&
                        Generated() const;

private:
  TopoDS_Shape                                           myInitialShape;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myDeleted;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myMod;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> myGen;
};
