// Created on: 2002-10-31
// Created by: Michael SAZONOV
// Copyright (c) 2002-2014 OPEN CASCADE SAS
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

#include <BinDrivers.hpp>
#include <BinDrivers_DocumentRetrievalDriver.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <BinMDataStd.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMNaming_NamedShapeDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Type.hpp>
#include <Standard_NotImplemented.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TNaming_NamedShape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinDrivers_DocumentRetrievalDriver, BinLDrivers_DocumentRetrievalDriver)

//=================================================================================================

BinDrivers_DocumentRetrievalDriver::BinDrivers_DocumentRetrievalDriver() = default;

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return BinDrivers::AttributeDrivers(theMessageDriver);
}

//=================================================================================================

void BinDrivers_DocumentRetrievalDriver::ReadShapeSection(
  BinLDrivers_DocumentSection& /*theSection*/,
  Standard_IStream& theIS,
  const bool /*isMess*/,
  const Message_ProgressRange& theRange)

{
  // Read Shapes
  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    try
    {
      OCC_CATCH_SIGNALS
      occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
        occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
      aNamedShapeDriver->ReadShapeSection(theIS, theRange);
    }
    catch (Standard_Failure const& anException)
    {
      const TCollection_ExtendedString aMethStr("BinDrivers_DocumentRetrievalDriver: ");
      myMsgDriver->Send(aMethStr + "error of Shape Section " + anException.what(), Message_Fail);
    }
  }
}

//=================================================================================================

void BinDrivers_DocumentRetrievalDriver::CheckShapeSection(
  const Storage_Position& /*ShapeSectionPos*/,
  Standard_IStream& /*IS*/)
{
}

//=================================================================================================

void BinDrivers_DocumentRetrievalDriver::Clear()
{
  // Clear NamedShape driver
  occ::handle<BinMDF_ADriver> aDriver;
  if (myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver))
  {
    occ::handle<BinMNaming_NamedShapeDriver> aNamedShapeDriver =
      occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
    aNamedShapeDriver->Clear();
  }
  BinLDrivers_DocumentRetrievalDriver::Clear();
}

//=================================================================================================

void BinDrivers_DocumentRetrievalDriver::EnableQuickPartReading(
  const occ::handle<Message_Messenger>& theMessageDriver,
  bool                                  theValue)
{
  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers(theMessageDriver);
  if (myDrivers.IsNull())
    return;

  occ::handle<BinMDF_ADriver> aDriver;
  myDrivers->GetDriver(STANDARD_TYPE(TNaming_NamedShape), aDriver);
  occ::handle<BinMNaming_NamedShapeDriver> aShapesDriver =
    occ::down_cast<BinMNaming_NamedShapeDriver>(aDriver);
  if (aShapesDriver.IsNull())
    throw Standard_NotImplemented("Internal Error - TNaming_NamedShape is not found!");

  aShapesDriver->EnableQuickPart(theValue);
}
