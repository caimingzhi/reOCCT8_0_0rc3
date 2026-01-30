// Created on: 2002-10-30
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

#include <BinMDataStd.hpp>
#include <BinMDataStd_AsciiStringDriver.hpp>
#include <BinMDataStd_BooleanArrayDriver.hpp>
#include <BinMDataStd_BooleanListDriver.hpp>
#include <BinMDataStd_ByteArrayDriver.hpp>
#include <BinMDataStd_ExpressionDriver.hpp>
#include <BinMDataStd_ExtStringArrayDriver.hpp>
#include <BinMDataStd_ExtStringListDriver.hpp>
#include <BinMDataStd_IntegerArrayDriver.hpp>
#include <BinMDataStd_IntegerDriver.hpp>
#include <BinMDataStd_IntegerListDriver.hpp>
#include <BinMDataStd_IntPackedMapDriver.hpp>
#include <BinMDataStd_NamedDataDriver.hpp>
#include <BinMDataStd_GenericExtStringDriver.hpp>
#include <BinMDataStd_RealArrayDriver.hpp>
#include <BinMDataStd_RealDriver.hpp>
#include <BinMDataStd_RealListDriver.hpp>
#include <BinMDataStd_ReferenceArrayDriver.hpp>
#include <BinMDataStd_ReferenceListDriver.hpp>
#include <BinMDataStd_GenericEmptyDriver.hpp>
#include <BinMDataStd_TreeNodeDriver.hpp>
#include <BinMDataStd_UAttributeDriver.hpp>
#include <BinMDataStd_VariableDriver.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <Message_Messenger.hpp>

//=================================================================================================

void BinMDataStd::AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                             const occ::handle<Message_Messenger>&   theMsgDriver)
{
  theDriverTable->AddDriver(new BinMDataStd_ExpressionDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_IntegerArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_IntegerDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_GenericExtStringDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_RealArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_RealDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_TreeNodeDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_UAttributeDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_VariableDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_ExtStringArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_GenericEmptyDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_IntegerListDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_RealListDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_ExtStringListDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_BooleanListDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_ReferenceListDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_BooleanArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_ReferenceArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_ByteArrayDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_NamedDataDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_AsciiStringDriver(theMsgDriver));
  theDriverTable->AddDriver(new BinMDataStd_IntPackedMapDriver(theMsgDriver));
}
