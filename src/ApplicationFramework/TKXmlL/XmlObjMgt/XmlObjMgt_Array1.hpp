#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <XmlObjMgt_DOMString.hpp>

//! The class Array1 represents unidimensional
//! array of fixed size known at run time.
//! The range of the index is user defined.
//! Warning: Programs clients of such class must be independent
//! of the range of the first element. Then, a C++ for
//! loop must be written like this
//! for (i = A->Lower(); i <= A->Upper(); i++)
class XmlObjMgt_Array1
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create an array of lower bound <Low> and
  //! upper bound <Up>. Range error is raised
  //! when <Up> is less than <Low>.
  Standard_EXPORT XmlObjMgt_Array1(const int Low, const int Up);

  //! for restoration from DOM_Element which is child of
  //! theParent:
  //! <theParent ...>
  //! <theName ...>
  Standard_EXPORT XmlObjMgt_Array1(const XmlObjMgt_Element&   theParent,
                                   const XmlObjMgt_DOMString& theName);

  //! Create DOM_Element representing the array, under 'theParent'
  Standard_EXPORT void CreateArrayElement(XmlObjMgt_Element&         theParent,
                                          const XmlObjMgt_DOMString& theName);

  //! Returns the DOM element of <me>.
  const XmlObjMgt_Element& Element() const;

  //! Returns the number of elements of <me>.
  int Length() const;

  //! Returns the lower bound.
  int Lower() const;

  //! Returns the upper bound.
  int Upper() const;

  //! Set the <Index>th element of the array to <Value>.
  Standard_EXPORT void SetValue(const int Index, XmlObjMgt_Element& Value);

  //! Returns the value of <Index>th element of the array.
  Standard_EXPORT XmlObjMgt_Element Value(const int Index) const;

private:
  XmlObjMgt_Element myElement;
  int               myFirst;
  int               myLast;
};
// Created on: 2001-08-01
// Created by: Alexander GRIGORIEV
// Copyright (c) 2001-2014 OPEN CASCADE SAS
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

inline const XmlObjMgt_Element& XmlObjMgt_Array1::Element() const
{
  return myElement;
}

//=================================================================================================

inline int XmlObjMgt_Array1::Length() const
{
  return myLast - myFirst + 1;
}

//=================================================================================================

inline int XmlObjMgt_Array1::Lower() const
{
  return myFirst;
}

//=================================================================================================

inline int XmlObjMgt_Array1::Upper() const
{
  return myLast;
}


