// Created on: 1996-09-16
// Created by: Jacques GOUSSARD
// Copyright (c) 1996-1999 Matra Datavision
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

#ifndef _LocOpe_BuildShape_HeaderFile
#define _LocOpe_BuildShape_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

class LocOpe_BuildShape
{
public:
  DEFINE_STANDARD_ALLOC

  LocOpe_BuildShape();

  //! Builds shape(s) from the list <L>. Uses only the
  //! faces of <L>.
  LocOpe_BuildShape(const NCollection_List<TopoDS_Shape>& L);

  //! Builds shape(s) from the list <L>. Uses only the
  //! faces of <L>.
  Standard_EXPORT void Perform(const NCollection_List<TopoDS_Shape>& L);

  const TopoDS_Shape& Shape() const;

private:
  TopoDS_Shape myRes;
};
// Created on: 1996-09-16
// Created by: Jacques GOUSSARD
// Copyright (c) 1996-1999 Matra Datavision
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

inline LocOpe_BuildShape::LocOpe_BuildShape() = default;

//=================================================================================================

inline LocOpe_BuildShape::LocOpe_BuildShape(const NCollection_List<TopoDS_Shape>& L)
{
  Perform(L);
}

//=================================================================================================

inline const TopoDS_Shape& LocOpe_BuildShape::Shape() const
{
  return myRes;
}


#endif // _LocOpe_BuildShape_HeaderFile
