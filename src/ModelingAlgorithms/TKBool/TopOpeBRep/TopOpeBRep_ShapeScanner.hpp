#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepTool_BoxSort.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class TopoDS_Shape;
class TopOpeBRepTool_ShapeExplorer;

class TopOpeBRep_ShapeScanner
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_ShapeScanner();

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddBoxesMakeCOB(const TopoDS_Shape&    S,
                                       const TopAbs_ShapeEnum TS,
                                       const TopAbs_ShapeEnum TA = TopAbs_SHAPE);

  Standard_EXPORT void Init(const TopoDS_Shape& E);

  Standard_EXPORT void Init(TopOpeBRepTool_ShapeExplorer& X);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopoDS_Shape& Current() const;

  Standard_EXPORT const TopOpeBRepTool_BoxSort& BoxSort() const;

  Standard_EXPORT TopOpeBRepTool_BoxSort& ChangeBoxSort();

  Standard_EXPORT int Index() const;

  Standard_EXPORT Standard_OStream& DumpCurrent(Standard_OStream& OS) const;

private:
  TopOpeBRepTool_BoxSort          myBoxSort;
  NCollection_List<int>::Iterator myListIterator;
};
