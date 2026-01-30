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

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <STEPSelections_SelectForTransfer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_TransientProcess.hpp>
#include <XSControl_TransferReader.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPSelections_SelectForTransfer, XSControl_SelectForTransfer)

//=================================================================================================

STEPSelections_SelectForTransfer::STEPSelections_SelectForTransfer() = default;

//=================================================================================================

STEPSelections_SelectForTransfer::STEPSelections_SelectForTransfer(
  const occ::handle<XSControl_TransferReader>& TR)
{
  SetReader(TR);
}

//=================================================================================================

Interface_EntityIterator STEPSelections_SelectForTransfer::RootResult(
  const Interface_Graph& /*G*/) const
{
  Interface_EntityIterator                                            iter;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> roots =
    Reader()->TransientProcess()->RootsForTransfer();
  int nb = roots->Length();
  for (int i = 1; i <= nb; i++)
    iter.GetOneItem(roots->Value(i));
  return iter;
}
