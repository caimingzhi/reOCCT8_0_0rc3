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

// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

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
