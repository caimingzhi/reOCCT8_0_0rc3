// Created on: 2007-08-01
// Created by: Sergey ZARITCHNY
// Copyright (c) 2007-2014 OPEN CASCADE SAS
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

#include <BinMDataStd_AsciiStringDriver.hpp>
#include <BinMDF_ADriver.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <BinMDataStd.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_AsciiStringDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataStd_AsciiStringDriver::BinMDataStd_AsciiStringDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, STANDARD_TYPE(TDataStd_AsciiString)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataStd_AsciiStringDriver::NewEmpty() const
{
  return new TDataStd_AsciiString;
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================

bool BinMDataStd_AsciiStringDriver::Paste(const BinObjMgt_Persistent&       Source,
                                          const occ::handle<TDF_Attribute>& Target,
                                          BinObjMgt_RRelocationTable&       RelocTable) const
{
  occ::handle<TDataStd_AsciiString> aStrAtt = occ::down_cast<TDataStd_AsciiString>(Target);
  TCollection_AsciiString           aString;
  bool                              ok = Source >> aString;
  if (ok)
    aStrAtt->Set(aString);
  if (RelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_9)
  { // process user defined guid
    const int&    aPos = Source.Position();
    Standard_GUID aGuid;
    ok = Source >> aGuid;
    if (!ok)
    {
      Source.SetPosition(aPos);
      aStrAtt->SetID(TDataStd_AsciiString::GetID());
      ok = true;
    }
    else
    {
      aStrAtt->SetID(aGuid);
    }
  }
  else
    aStrAtt->SetID(TDataStd_AsciiString::GetID());
  return ok;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================

void BinMDataStd_AsciiStringDriver::Paste(
  const occ::handle<TDF_Attribute>& Source,
  BinObjMgt_Persistent&             Target,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& /*RelocTable*/) const
{
  occ::handle<TDataStd_AsciiString> anAtt = occ::down_cast<TDataStd_AsciiString>(Source);
  Target << anAtt->Get();
  // process user defined guid
  if (anAtt->ID() != TDataStd_AsciiString::GetID())
    Target << anAtt->ID();
}
