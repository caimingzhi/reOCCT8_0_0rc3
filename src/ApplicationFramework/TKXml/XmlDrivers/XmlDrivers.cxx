// Created on: 2001-07-09
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
#include <Plugin_Macro.hpp>
#include <Standard_GUID.hpp>
#include <TDocStd_Application.hpp>
#include <XmlDrivers.hpp>
#include <XmlDrivers_DocumentRetrievalDriver.hpp>
#include <XmlDrivers_DocumentStorageDriver.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataXtd.hpp>
#include <XmlMDF.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMDocStd.hpp>
#include <XmlMFunction.hpp>
#include <XmlMNaming.hpp>

static Standard_GUID XmlStorageDriver("03a56820-8269-11d5-aab2-0050044b1af1");
static Standard_GUID XmlRetrievalDriver("03a56822-8269-11d5-aab2-0050044b1af1");

//=================================================================================================

const occ::handle<Standard_Transient>& XmlDrivers::Factory(const Standard_GUID& theGUID)
{
  if (theGUID == XmlStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd = new XmlDrivers_DocumentStorageDriver(
      "Copyright: Open Cascade, 2001-2002"); // default copyright
    return model_sd;
  }

  if (theGUID == XmlRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new XmlDrivers_DocumentRetrievalDriver();
    return model_rd;
  }

  throw Standard_Failure("XmlDrivers : unknown GUID");
}

//=================================================================================================

void XmlDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("XmlOcaf",
                       "Xml OCAF Document",
                       "xml",
                       new XmlDrivers_DocumentRetrievalDriver,
                       new XmlDrivers_DocumentStorageDriver("Copyright: Open Cascade, 2001-2002"));
}

//=================================================================================================

occ::handle<XmlMDF_ADriverTable> XmlDrivers::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  occ::handle<XmlMDF_ADriverTable> aTable = new XmlMDF_ADriverTable();
  //
  XmlMDF ::AddDrivers(aTable, theMessageDriver);
  XmlMDataStd ::AddDrivers(aTable, theMessageDriver);
  XmlMDataXtd ::AddDrivers(aTable, theMessageDriver);
  XmlMNaming ::AddDrivers(aTable, theMessageDriver);
  XmlMFunction ::AddDrivers(aTable, theMessageDriver);
  XmlMDocStd ::AddDrivers(aTable, theMessageDriver);
  //
  return aTable;
}

// Declare entry point PLUGINFACTORY
PLUGIN(XmlDrivers)
