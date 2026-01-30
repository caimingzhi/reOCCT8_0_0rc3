// Created on: 1992-02-03
// Created by: Christian CAILLET
// Copyright (c) 1992-1999 Matra Datavision
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

#include <Interface_ReaderLib.hpp>

#include <Interface_NodeOfReaderLib.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ReaderModule.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_GlobalNodeOfReaderLib.hpp>

#define TheObject occ::handle<Standard_Transient>
#define TheObject_hxx <Standard_Transient.hpp>
#define Handle_TheModule occ::handle<Interface_ReaderModule>
#define TheModule Interface_ReaderModule
#define TheModule_hxx <Interface_ReaderModule.hpp>
#define Handle_TheProtocol occ::handle<Interface_Protocol>
#define TheProtocol Interface_Protocol
#define TheProtocol_hxx <Interface_Protocol.hpp>
#define LibCtl_GlobalNode Interface_GlobalNodeOfReaderLib
#define LibCtl_GlobalNode_hxx <Interface_GlobalNodeOfReaderLib.hpp>
#define LibCtl_Node Interface_NodeOfReaderLib
#define LibCtl_Node_hxx <Interface_NodeOfReaderLib.hpp>
#define Handle_LibCtl_GlobalNode occ::handle<Interface_GlobalNodeOfReaderLib>
#define Handle_LibCtl_Node occ::handle<Interface_NodeOfReaderLib>
#define LibCtl_Library Interface_ReaderLib
#define LibCtl_Library_hxx <Interface_ReaderLib.hpp>
#include <LibCtl_Library.hpp>
