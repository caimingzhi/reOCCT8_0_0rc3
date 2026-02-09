#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Macro.hpp>
class TopLoc_SListNodeOfItemLocation;
class TopLoc_ItemLocation;

class TopLoc_SListOfItemLocation
{
public:
  DEFINE_STANDARD_ALLOC

  TopLoc_SListOfItemLocation() = default;

  Standard_EXPORT TopLoc_SListOfItemLocation(const TopLoc_ItemLocation&        anItem,
                                             const TopLoc_SListOfItemLocation& aTail);

  TopLoc_SListOfItemLocation(const TopLoc_SListOfItemLocation& Other)

    = default;

  Standard_EXPORT TopLoc_SListOfItemLocation& Assign(const TopLoc_SListOfItemLocation& Other);

  TopLoc_SListOfItemLocation& operator=(const TopLoc_SListOfItemLocation& Other)
  {
    return Assign(Other);
  }

  TopLoc_SListOfItemLocation(TopLoc_SListOfItemLocation&& theOther) noexcept
      : myNode(std::move(theOther.myNode))
  {
  }

  TopLoc_SListOfItemLocation& operator=(TopLoc_SListOfItemLocation&& theOther) noexcept
  {
    myNode = std::move(theOther.myNode);
    return *this;
  }

  bool IsEmpty() const { return myNode.IsNull(); }

  void Clear() { myNode.Nullify(); }

  ~TopLoc_SListOfItemLocation() { Clear(); }

  Standard_EXPORT const TopLoc_ItemLocation& Value() const;

  Standard_EXPORT const TopLoc_SListOfItemLocation& Tail() const;

  void Construct(const TopLoc_ItemLocation& anItem)
  {
    Assign(TopLoc_SListOfItemLocation(anItem, *this));
  }

  void ToTail() { Assign(Tail()); }

  bool More() const { return !IsEmpty(); }

  void Next() { ToTail(); }

private:
  occ::handle<TopLoc_SListNodeOfItemLocation> myNode;
};
