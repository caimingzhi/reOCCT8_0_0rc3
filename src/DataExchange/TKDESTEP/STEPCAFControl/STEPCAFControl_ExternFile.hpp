#pragma once


#include <Standard.hpp>

#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
#include <Standard_Transient.hpp>
class XSControl_WorkSession;
class TCollection_HAsciiString;

//! Auxiliary class serving as container for data resulting
//! from translation of external file
class STEPCAFControl_ExternFile : public Standard_Transient
{

public:
  //! Creates an empty structure
  Standard_EXPORT STEPCAFControl_ExternFile();

  void SetWS(const occ::handle<XSControl_WorkSession>& WS);

  occ::handle<XSControl_WorkSession> GetWS() const;

  void SetLoadStatus(const IFSelect_ReturnStatus stat);

  IFSelect_ReturnStatus GetLoadStatus() const;

  void SetTransferStatus(const bool isok);

  bool GetTransferStatus() const;

  void SetWriteStatus(const IFSelect_ReturnStatus stat);

  IFSelect_ReturnStatus GetWriteStatus() const;

  void SetName(const occ::handle<TCollection_HAsciiString>& name);

  occ::handle<TCollection_HAsciiString> GetName() const;

  void SetLabel(const TDF_Label& L);

  TDF_Label GetLabel() const;

  DEFINE_STANDARD_RTTIEXT(STEPCAFControl_ExternFile, Standard_Transient)

private:
  occ::handle<XSControl_WorkSession>    myWS;
  IFSelect_ReturnStatus                 myLoadStatus;
  bool                                  myTransferStatus;
  IFSelect_ReturnStatus                 myWriteStatus;
  occ::handle<TCollection_HAsciiString> myName;
  TDF_Label                             myLabel;
};
// Created on: 2000-09-28
// Created by: Andrey BETENEV
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

inline void STEPCAFControl_ExternFile::SetWS(const occ::handle<XSControl_WorkSession>& WS)
{
  myWS = WS;
}

//=================================================================================================

inline occ::handle<XSControl_WorkSession> STEPCAFControl_ExternFile::GetWS() const
{
  return myWS;
}

//=================================================================================================

inline void STEPCAFControl_ExternFile::SetLoadStatus(const IFSelect_ReturnStatus stat)
{
  myLoadStatus = stat;
}

//=================================================================================================

inline IFSelect_ReturnStatus STEPCAFControl_ExternFile::GetLoadStatus() const
{
  return myLoadStatus;
}

//=================================================================================================

inline void STEPCAFControl_ExternFile::SetTransferStatus(const bool isok)
{
  myTransferStatus = isok;
}

//=================================================================================================

inline bool STEPCAFControl_ExternFile::GetTransferStatus() const
{
  return myTransferStatus;
}

//=================================================================================================

inline void STEPCAFControl_ExternFile::SetWriteStatus(const IFSelect_ReturnStatus stat)
{
  myWriteStatus = stat;
}

//=================================================================================================

inline IFSelect_ReturnStatus STEPCAFControl_ExternFile::GetWriteStatus() const
{
  return myWriteStatus;
}

//=================================================================================================

inline void STEPCAFControl_ExternFile::SetName(const occ::handle<TCollection_HAsciiString>& name)
{
  myName = name;
}

//=================================================================================================

inline occ::handle<TCollection_HAsciiString> STEPCAFControl_ExternFile::GetName() const
{
  return myName;
}

/*
//=================================================================================================

inline void STEPCAFControl_ExternFile::SetShape (const TopoDS_Shape &Shape)
{
  myShape = Shape;
}

//=================================================================================================

inline TopoDS_Shape STEPCAFControl_ExternFile::GetShape () const
{
  return myShape;
}
*/

//=================================================================================================

inline void STEPCAFControl_ExternFile::SetLabel(const TDF_Label& Label)
{
  myLabel = Label;
}

//=================================================================================================

inline TDF_Label STEPCAFControl_ExternFile::GetLabel() const
{
  return myLabel;
}


