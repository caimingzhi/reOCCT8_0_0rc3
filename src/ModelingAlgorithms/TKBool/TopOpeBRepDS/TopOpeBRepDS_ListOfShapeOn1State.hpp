#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Boolean.hpp>

//! represent a list of shape
class TopOpeBRepDS_ListOfShapeOn1State
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_ListOfShapeOn1State();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& ListOnState() const;

  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeListOnState();

  Standard_EXPORT bool IsSplit() const;

  Standard_EXPORT void Split(const bool B = true);

  Standard_EXPORT void Clear();

private:
  NCollection_List<TopoDS_Shape> myList;
  int                            mySplits;
};
