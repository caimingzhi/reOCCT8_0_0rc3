// Created on: 1995-03-22
// Created by: Jean-Louis  Frenkel
// Copyright (c) 1995-1999 Matra Datavision
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

#ifndef _CDF_StoreList_HeaderFile
#define _CDF_StoreList_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <CDM_Document.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Transient.hpp>
#include <PCDM_StoreStatus.hpp>

class CDM_Document;
class CDM_MetaData;
class TCollection_ExtendedString;

class CDF_StoreList : public Standard_Transient
{

public:
  Standard_EXPORT CDF_StoreList(const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT bool IsConsistent() const;

  //! stores each object of the storelist in the reverse
  //! order of which they had been added.
  Standard_EXPORT PCDM_StoreStatus
    Store(occ::handle<CDM_MetaData>&   aMetaData,
          TCollection_ExtendedString&  aStatusAssociatedText,
          const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void Init();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<CDM_Document> Value() const;

  DEFINE_STANDARD_RTTIEXT(CDF_StoreList, Standard_Transient)

private:
  Standard_EXPORT void Add(const occ::handle<CDM_Document>& aDocument);

  NCollection_Map<occ::handle<CDM_Document>>           myItems;
  NCollection_List<occ::handle<CDM_Document>>          myStack;
  NCollection_Map<occ::handle<CDM_Document>>::Iterator myIterator;
  occ::handle<CDM_Document>                            myMainDocument;
};

#endif // _CDF_StoreList_HeaderFile
