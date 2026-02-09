#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Boolean.hpp>
class TopoDS_Shape;

class ChFiDS_Map
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_Map();

  Standard_EXPORT void Fill(const TopoDS_Shape&    S,
                            const TopAbs_ShapeEnum T1,
                            const TopAbs_ShapeEnum T2);

  Standard_EXPORT bool Contains(const TopoDS_Shape& S) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FindFromKey(const TopoDS_Shape& S) const;

  const NCollection_List<TopoDS_Shape>& operator()(const TopoDS_Shape& S) const
  {
    return FindFromKey(S);
  }

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& FindFromIndex(const int I) const;

  const NCollection_List<TopoDS_Shape>& operator()(const int I) const { return FindFromIndex(I); }

private:
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMap;
};
