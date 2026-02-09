#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;

class TNaming_Translator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TNaming_Translator();

  Standard_EXPORT void Add(const TopoDS_Shape& aShape);

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const TopoDS_Shape Copied(const TopoDS_Shape& aShape) const;

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Copied() const;

  Standard_EXPORT void DumpMap(const bool isWrite = false) const;

private:
  bool myIsDone;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>
                                                                           myMap;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myDataMapOfResults;
};
