#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_CString.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Message_ProgressRange.hpp>

class ShapeProcess_ShapeContext;
class TopoDS_Shape;

class ShapeProcessAPI_ApplySequence
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeProcessAPI_ApplySequence(const char* rscName, const char* seqName = "");

  Standard_EXPORT occ::handle<ShapeProcess_ShapeContext>& Context();

  Standard_EXPORT TopoDS_Shape
    PrepareShape(const TopoDS_Shape&          shape,
                 const bool                   fillmap     = false,
                 const TopAbs_ShapeEnum       until       = TopAbs_SHAPE,
                 const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void ClearMap();

  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Map() const;

  Standard_EXPORT void PrintPreparationResult() const;

private:
  occ::handle<ShapeProcess_ShapeContext>                                   myContext;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
  TCollection_AsciiString                                                  mySeq;
};
