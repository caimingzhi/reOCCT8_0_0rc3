// Copyright (c) 2024 OPEN CASCADE SAS
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

#ifndef _StepRepr_BooleanRepresentationItem_HeaderFile
#define _StepRepr_BooleanRepresentationItem_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;

class StepRepr_BooleanRepresentationItem : public StepRepr_RepresentationItem
{
public:
  //! Returns a BooleanRepresentationItem
  Standard_EXPORT StepRepr_BooleanRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const bool                                   theValue);

  inline void SetValue(const bool theValue) { value = theValue; }

  inline bool Value() const { return value; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_BooleanRepresentationItem, StepRepr_RepresentationItem)

private:
  bool value;
};

#endif // _StepRepr_BooleanRepresentationItem_HeaderFile
