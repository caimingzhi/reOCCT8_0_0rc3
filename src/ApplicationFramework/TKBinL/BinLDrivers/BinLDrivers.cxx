// Created on: 2002-10-29
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

#include <BinLDrivers.hpp>
#include <BinLDrivers_DocumentRetrievalDriver.hpp>
#include <BinLDrivers_DocumentStorageDriver.hpp>
#include <BinMDataStd.hpp>
#include <BinMDF.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMDocStd.hpp>
#include <BinMFunction.hpp>
#include <Plugin_Macro.hpp>
#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Transient.hpp>
#include <TDocStd_Application.hpp>

// #include <BinMNaming.hpp>
static Standard_GUID BinLStorageDriver("13a56835-8269-11d5-aab2-0050044b1af1");
static Standard_GUID BinLRetrievalDriver("13a56836-8269-11d5-aab2-0050044b1af1");

//=================================================================================================

const occ::handle<Standard_Transient>& BinLDrivers::Factory(const Standard_GUID& theGUID)
{
  if (theGUID == BinLStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinLDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd = new BinLDrivers_DocumentStorageDriver;
    return model_sd;
  }

  if (theGUID == BinLRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinLDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new BinLDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  throw Standard_Failure("BinLDrivers : unknown GUID");
}

//=================================================================================================

void BinLDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("BinLOcaf",
                       "Binary Lite OCAF Document",
                       "cbfl",
                       new BinLDrivers_DocumentRetrievalDriver,
                       new BinLDrivers_DocumentStorageDriver);
}

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinLDrivers::AttributeDrivers(
  const occ::handle<Message_Messenger>& aMsgDrv)
{
  occ::handle<BinMDF_ADriverTable> aTable = new BinMDF_ADriverTable;

  BinMDF ::AddDrivers(aTable, aMsgDrv);
  BinMDataStd ::AddDrivers(aTable, aMsgDrv);
  BinMFunction ::AddDrivers(aTable, aMsgDrv);
  BinMDocStd ::AddDrivers(aTable, aMsgDrv);

  return aTable;
}

PLUGIN(BinLDrivers)
