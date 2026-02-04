#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! The class BOPDS_IndexRange is to store
//! the information about range of two indices
class BOPDS_IndexRange
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  BOPDS_IndexRange();

  //! Modifier
  //! Sets the first index <theI1> of the range
  void SetFirst(const int theI1);

  //! Modifier
  //! Sets the second index <theI2> of the range
  void SetLast(const int theI2);

  //! Selector
  //! Returns the first index of the range
  int First() const;

  //! Selector
  //! Returns the second index of the range
  int Last() const;

  //! Modifier
  //! Sets the first index of the range  <theI1>
  //! Sets the second index of the range <theI2>
  void SetIndices(const int theI1, const int theI2);

  //! Selector
  //! Returns the first index of the range  <theI1>
  //! Returns the second index of the range <theI2>
  void Indices(int& theI1, int& theI2) const;

  //! Query
  //! Returns true if the range contains <theIndex>
  bool Contains(const int theIndex) const;

  Standard_EXPORT void Dump() const;

protected:
  int myFirst;
  int myLast;
};
// Created by: Peter KURNEV
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

//=================================================================================================

inline BOPDS_IndexRange::BOPDS_IndexRange()
    : myFirst(0),
      myLast(0)
{
}

//=================================================================================================

inline void BOPDS_IndexRange::SetFirst(const int aFirst)
{
  myFirst = aFirst;
}

//=================================================================================================

inline int BOPDS_IndexRange::First() const
{
  return myFirst;
}

//=================================================================================================

inline void BOPDS_IndexRange::SetLast(const int aLast)
{
  myLast = aLast;
}

//=================================================================================================

inline int BOPDS_IndexRange::Last() const
{
  return myLast;
}

//=================================================================================================

inline void BOPDS_IndexRange::SetIndices(const int theI1, const int theI2)
{
  myFirst = theI1;
  myLast  = theI2;
}

//=================================================================================================

inline void BOPDS_IndexRange::Indices(int& theI1, int& theI2) const
{
  theI1 = myFirst;
  theI2 = myLast;
}

//=================================================================================================

inline bool BOPDS_IndexRange::Contains(const int aIndex) const
{
  return aIndex >= myFirst && aIndex <= myLast;
}


