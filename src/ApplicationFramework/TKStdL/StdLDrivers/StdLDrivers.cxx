// Created on: 2000-09-07
// Created by: TURIN Anatoliy
// Copyright (c) 2000-2015 OPEN CASCADE SAS
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

#include <StdLDrivers.hpp>
#include <StdLDrivers_DocumentRetrievalDriver.hpp>
#include <StdLPersistent.hpp>

#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <Plugin_Macro.hpp>

#include <PCDM_StorageDriver.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID StdLRetrievalDriver("bd696001-5b34-11d1-b5ba-00a0c9064368");

//=======================================================================
// function : Factory
// purpose  : Depending from the ID, returns a list of storage
//           or retrieval attribute drivers. Used for plugin
//=======================================================================
occ::handle<Standard_Transient> StdLDrivers::Factory(const Standard_GUID& aGUID)
{
  if (aGUID == StdLRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "StdLDrivers : Retrieval Plugin" << std::endl;
#endif

    static occ::handle<StdLDrivers_DocumentRetrievalDriver> model_rd =
      new StdLDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  throw Standard_Failure("StdLDrivers : unknown GUID");
}

//=================================================================================================

void StdLDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("OCC-StdLite",
                       "Lite OCAF Document",
                       "stdl",
                       new StdLDrivers_DocumentRetrievalDriver,
                       nullptr);
}

//=================================================================================================

void StdLDrivers::BindTypes(StdObjMgt_MapOfInstantiators& theMap)
{
  StdLPersistent::BindTypes(theMap);
}

// Declare entry point PLUGINFACTORY
PLUGIN(StdLDrivers)
