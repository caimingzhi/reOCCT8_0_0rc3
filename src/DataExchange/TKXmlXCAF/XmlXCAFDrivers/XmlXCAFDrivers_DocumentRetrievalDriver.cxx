// Created on: 2001-09-11
// Created by: Julia DOROVSKIKH
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

#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <XmlDrivers.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMXCAFDoc.hpp>
#include <XmlXCAFDrivers_DocumentRetrievalDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlXCAFDrivers_DocumentRetrievalDriver,
                           XmlDrivers_DocumentRetrievalDriver)

//=================================================================================================

XmlXCAFDrivers_DocumentRetrievalDriver::XmlXCAFDrivers_DocumentRetrievalDriver() = default;

//=================================================================================================

occ::handle<XmlMDF_ADriverTable> XmlXCAFDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMsgDrv)
{
  // Standard drivers
  occ::handle<XmlMDF_ADriverTable> aTable = XmlDrivers::AttributeDrivers(theMsgDrv);

  // Native drivers
  XmlMXCAFDoc::AddDrivers(aTable, theMsgDrv);

  return aTable;
}
