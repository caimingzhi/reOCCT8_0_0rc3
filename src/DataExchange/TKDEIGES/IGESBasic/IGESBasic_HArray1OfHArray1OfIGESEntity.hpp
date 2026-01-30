// Created on: 1993-01-09
// Created by: CKY / Contract Toubro-Larsen (Arun MENON)
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

#ifndef _IGESBasic_HArray1OfHArray1OfIGESEntity_HeaderFile
#define _IGESBasic_HArray1OfHArray1OfIGESEntity_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

class IGESBasic_HArray1OfHArray1OfIGESEntity : public Standard_Transient
{

public:
  Standard_EXPORT IGESBasic_HArray1OfHArray1OfIGESEntity(const int low, const int up);

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void SetValue(
    const int                                                                 num,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& val);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> Value(
    const int num) const;

  DEFINE_STANDARD_RTTI_INLINE(IGESBasic_HArray1OfHArray1OfIGESEntity, Standard_Transient)

private:
  NCollection_Array1<occ::handle<Standard_Transient>> thelist;
};

#endif // _IGESBasic_HArray1OfHArray1OfIGESEntity_HeaderFile
