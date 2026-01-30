// Created on: 2004-11-24
// Created by: Michael SAZONOV
// Copyright (c) 2004-2014 OPEN CASCADE SAS
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

// The original implementation Copyright: (C) RINA S.p.A

#include <XmlLDrivers.hpp>
#include <XmlTObjDrivers.hpp>
#include <XmlTObjDrivers_DocumentStorageDriver.hpp>
#include <XmlTObjDrivers_DocumentRetrievalDriver.hpp>
#include <XmlTObjDrivers_ModelDriver.hpp>
#include <XmlTObjDrivers_ObjectDriver.hpp>
#include <XmlTObjDrivers_ReferenceDriver.hpp>
#include <XmlTObjDrivers_XYZDriver.hpp>
#include <XmlTObjDrivers_IntSparseArrayDriver.hpp>

#include <Plugin_Macro.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID XmlStorageDriver("f78ff4a0-a779-11d5-aab4-0050044b1af1");
static Standard_GUID XmlRetrievalDriver("f78ff4a1-a779-11d5-aab4-0050044b1af1");

const occ::handle<Standard_Transient>& XmlTObjDrivers::Factory(const Standard_GUID& aGUID)
{
  if (aGUID == XmlStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlTObjDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd =
      new XmlTObjDrivers_DocumentStorageDriver("Copyright: Open CASCADE 2004"); // default copyright
    return model_sd;
  }

  if (aGUID == XmlRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlTObjDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new XmlTObjDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  return XmlLDrivers::Factory(aGUID);
}

//=================================================================================================

void XmlTObjDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("TObjXml",
                       "Xml TObj OCAF Document",
                       "xml",
                       new XmlTObjDrivers_DocumentRetrievalDriver,
                       new XmlTObjDrivers_DocumentStorageDriver("Copyright: Open Cascade, 2004"));
}

//=================================================================================================

void XmlTObjDrivers::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                                const occ::handle<Message_Messenger>&   anMsgDrv)
{
  aDriverTable->AddDriver(new XmlTObjDrivers_ModelDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlTObjDrivers_ObjectDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlTObjDrivers_ReferenceDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlTObjDrivers_XYZDriver(anMsgDrv));
  aDriverTable->AddDriver(new XmlTObjDrivers_IntSparseArrayDriver(anMsgDrv));
}

PLUGIN(XmlTObjDrivers)
