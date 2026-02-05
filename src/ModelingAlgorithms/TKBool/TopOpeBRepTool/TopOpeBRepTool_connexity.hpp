#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>

class TopOpeBRepTool_connexity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_connexity();

  Standard_EXPORT TopOpeBRepTool_connexity(const TopoDS_Shape& Key);

  Standard_EXPORT void SetKey(const TopoDS_Shape& Key);

  Standard_EXPORT const TopoDS_Shape& Key() const;

  Standard_EXPORT int Item(const int OriKey, NCollection_List<TopoDS_Shape>& Item) const;

  Standard_EXPORT int AllItems(NCollection_List<TopoDS_Shape>& Item) const;

  Standard_EXPORT void AddItem(const int OriKey, const NCollection_List<TopoDS_Shape>& Item);

  Standard_EXPORT void AddItem(const int OriKey, const TopoDS_Shape& Item);

  Standard_EXPORT bool RemoveItem(const int OriKey, const TopoDS_Shape& Item);

  Standard_EXPORT bool RemoveItem(const TopoDS_Shape& Item);

  Standard_EXPORT NCollection_List<TopoDS_Shape>& ChangeItem(const int OriKey);

  Standard_EXPORT bool IsMultiple() const;

  Standard_EXPORT bool IsFaulty() const;

  Standard_EXPORT int IsInternal(NCollection_List<TopoDS_Shape>& Item) const;

private:
  TopoDS_Shape                                       theKey;
  NCollection_Array1<NCollection_List<TopoDS_Shape>> theItems;
};
