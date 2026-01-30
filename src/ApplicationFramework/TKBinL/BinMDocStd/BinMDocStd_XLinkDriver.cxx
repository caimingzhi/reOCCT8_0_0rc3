// Created on: 2004-05-13
// Created by: Sergey ZARITCHNY
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

#include <BinMDF_ADriver.hpp>
#include <BinMDocStd_XLinkDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_XLink.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDocStd_XLinkDriver, BinMDF_ADriver)

//=================================================================================================

BinMDocStd_XLinkDriver::BinMDocStd_XLinkDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDocStd_XLink)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDocStd_XLinkDriver::NewEmpty() const
{
  return new TDocStd_XLink();
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================

bool BinMDocStd_XLinkDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   BinObjMgt_RRelocationTable&) const
{
  TCollection_AsciiString aStr;
  bool                    ok = theSource >> aStr;
  if (ok)
  {
    occ::handle<TDocStd_XLink> anAtt = occ::down_cast<TDocStd_XLink>(theTarget);
    anAtt->DocumentEntry(aStr);
    aStr.Clear();
    ok = theSource >> aStr;
    if (ok)
      anAtt->LabelEntry(aStr);
  }
  return ok;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================

void BinMDocStd_XLinkDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   BinObjMgt_Persistent&             theTarget,
                                   NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDocStd_XLink> anAtt = occ::down_cast<TDocStd_XLink>(theSource);
  theTarget << anAtt->DocumentEntry() << anAtt->LabelEntry();
}
