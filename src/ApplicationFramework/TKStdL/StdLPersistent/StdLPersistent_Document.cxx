// Copyright (c) 2015 OPEN CASCADE SAS
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

#include <StdLPersistent_Document.hpp>
#include <StdLPersistent_Data.hpp>
#include <StdObjMgt_ReadData.hpp>
#include <StdObjMgt_WriteData.hpp>

#include <TDocStd_Document.hpp>
#include <TDocStd_Owner.hpp>

//=======================================================================
// function : Read
// purpose  : Read persistent data from a file
//=======================================================================
void StdLPersistent_Document::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myData;
}

//=======================================================================
// function : Write
// purpose  : Write persistent data to a file
//=======================================================================
void StdLPersistent_Document::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myData;
}

//=======================================================================
// function : PChildren
// purpose  : Gets persistent child objects
//=======================================================================
void StdLPersistent_Document::PChildren(
  StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
{
  theChildren.Append(myData);
}

//=======================================================================
// function : Import
// purpose  : Import transient document from the persistent data
//=======================================================================
void StdLPersistent_Document::ImportDocument(const occ::handle<TDocStd_Document>& theDocument) const
{
  if (theDocument.IsNull() || myData.IsNull())
    return;

  occ::handle<TDF_Data> aData = myData->Import();
  if (aData.IsNull())
    return;

  theDocument->SetData(aData);
  TDocStd_Owner::SetDocument(aData, theDocument);
}
