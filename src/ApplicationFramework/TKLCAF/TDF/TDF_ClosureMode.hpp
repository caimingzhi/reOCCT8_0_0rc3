// Created by: DAUTRY Philippe
// Copyright (c) 1997-1999 Matra Datavision
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

#ifndef _TDF_ClosureMode_HeaderFile
#define _TDF_ClosureMode_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! This class provides options closure management.
class TDF_ClosureMode
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an object with all modes set to <aMode>.
  Standard_EXPORT TDF_ClosureMode(const bool aMode = true);

  //! Sets the mode "Descendants" to <aStatus>.
  //!
  //! "Descendants" mode means we add to the data set
  //! the children labels of each USER GIVEN label. We
  //! do not do that with the labels found applying
  //! UpToFirstLevel option.
  void Descendants(const bool aStatus);

  //! Returns true if the mode "Descendants" is set.
  bool Descendants() const;

  //! Sets the mode "References" to <aStatus>.
  //!
  //! "References" mode means we add to the data set
  //! the descendants of an attribute, by calling the
  //! attribute method Descendants().
  void References(const bool aStatus);

  //! Returns true if the mode "References" is set.
  bool References() const;

private:
  int myFlags;
};
// Created by: DAUTRY Philippe
// Copyright (c) 1997-1999 Matra Datavision
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

//      	-------------------

// Version:	0.0
// Version	Date		Purpose
//		0.0	May 26 1997	Creation

#define DescendantsFlag 1
#define ReferencesFlag 2

// #define DummyFlag      4

inline void TDF_ClosureMode::Descendants(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | DescendantsFlag) : (myFlags & ~DescendantsFlag);
}

inline bool TDF_ClosureMode::Descendants() const
{
  return (myFlags & DescendantsFlag) != 0;
}

inline void TDF_ClosureMode::References(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | ReferencesFlag) : (myFlags & ~ReferencesFlag);
}

inline bool TDF_ClosureMode::References() const
{
  return (myFlags & ReferencesFlag) != 0;
}


#endif // _TDF_ClosureMode_HeaderFile
