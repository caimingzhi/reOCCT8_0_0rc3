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

#include <SelectMgr_AndFilter.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Filter.hpp>
#include <NCollection_List.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_AndFilter, SelectMgr_CompositionFilter)

SelectMgr_AndFilter::SelectMgr_AndFilter() = default;

bool SelectMgr_AndFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const
{
  NCollection_List<occ::handle<SelectMgr_Filter>>::Iterator it(myFilters);
  for (; it.More(); it.Next())
    if (!it.Value()->IsOk(anobj))
      return false;
  return true;
}
