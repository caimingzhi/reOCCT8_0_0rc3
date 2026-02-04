#pragma once


#include <Standard.hpp>

#include <TDocStd_Document.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

class TDocStd_ApplicationDelta : public Standard_Transient
{

public:
  Standard_EXPORT TDocStd_ApplicationDelta();

  NCollection_Sequence<occ::handle<TDocStd_Document>>& GetDocuments();

  const TCollection_ExtendedString& GetName() const;

  void SetName(const TCollection_ExtendedString& theName);

  Standard_EXPORT void Dump(Standard_OStream& anOS) const;

  DEFINE_STANDARD_RTTIEXT(TDocStd_ApplicationDelta, Standard_Transient)

private:
  NCollection_Sequence<occ::handle<TDocStd_Document>> myDocuments;
  TCollection_ExtendedString                          myName;
};
// Created on: 2002-11-21
// Created by: Vladimir ANIKIN
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

//=================================================================================================

inline NCollection_Sequence<occ::handle<TDocStd_Document>>& TDocStd_ApplicationDelta::GetDocuments()
{
  return myDocuments;
}

//=================================================================================================

inline const TCollection_ExtendedString& TDocStd_ApplicationDelta::GetName() const
{
  return myName;
}

//=================================================================================================

inline void TDocStd_ApplicationDelta::SetName(const TCollection_ExtendedString& theName)
{
  myName = theName;
}


