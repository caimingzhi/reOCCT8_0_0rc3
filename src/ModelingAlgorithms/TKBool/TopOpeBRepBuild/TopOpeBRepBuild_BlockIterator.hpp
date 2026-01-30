// Created on: 1993-02-25
// Created by: Jean Yves LEBEY
// Copyright (c) 1993-1999 Matra Datavision
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

#ifndef _TopOpeBRepBuild_BlockIterator_HeaderFile
#define _TopOpeBRepBuild_BlockIterator_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! Iterator on the elements of a block.
class TopOpeBRepBuild_BlockIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_BlockIterator();

  Standard_EXPORT TopOpeBRepBuild_BlockIterator(const int Lower, const int Upper);

  void Initialize();

  bool More() const;

  void Next();

  int Value() const;

  int Extent() const;

private:
  int myLower;
  int myUpper;
  int myValue;
};

#include <TopOpeBRepBuild_BlockIterator_1.hpp>

#endif // _TopOpeBRepBuild_BlockIterator_HeaderFile
