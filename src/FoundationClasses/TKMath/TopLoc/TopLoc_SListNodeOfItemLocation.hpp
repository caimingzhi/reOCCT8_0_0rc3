#pragma once

#include <Standard.hpp>

#include <TopLoc_SListOfItemLocation.hpp>
#include <TopLoc_ItemLocation.hpp>
#include <Standard_Transient.hpp>

class TopLoc_SListNodeOfItemLocation : public Standard_Transient
{

public:
  TopLoc_SListNodeOfItemLocation(const TopLoc_ItemLocation&        I,
                                 const TopLoc_SListOfItemLocation& aTail);

  TopLoc_SListOfItemLocation& Tail() const;

  TopLoc_ItemLocation& Value() const;

  DEFINE_STANDARD_RTTIEXT(TopLoc_SListNodeOfItemLocation, Standard_Transient)

private:
  TopLoc_SListOfItemLocation myTail;
  TopLoc_ItemLocation        myValue;
};

#include <TopLoc_ItemLocation.hpp>

inline TopLoc_SListNodeOfItemLocation::TopLoc_SListNodeOfItemLocation(
  const TopLoc_ItemLocation&        I,
  const TopLoc_SListOfItemLocation& T)
    : myTail(T),
      myValue(I)
{
}

inline TopLoc_SListOfItemLocation& TopLoc_SListNodeOfItemLocation::Tail() const
{
  return (TopLoc_SListOfItemLocation&)myTail;
}

inline TopLoc_ItemLocation& TopLoc_SListNodeOfItemLocation::Value() const
{
  return (TopLoc_ItemLocation&)myValue;
}
