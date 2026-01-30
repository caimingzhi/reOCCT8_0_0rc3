// Copyright (c) 2020 OPEN CASCADE SAS
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

#ifndef _Aspect_XRAction_HeaderFile
#define _Aspect_XRAction_HeaderFile

#include <Aspect_XRActionType.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

//! XR action definition.
class Aspect_XRAction : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_XRAction, Standard_Transient)
public:
  //! Return action id.
  const TCollection_AsciiString& Id() const { return myId; }

  //! Return action type.
  Aspect_XRActionType Type() const { return myType; }

  //! Return TRUE if action is defined.
  bool IsValid() const { return myRawHandle != 0; }

  //! Return action handle.
  uint64_t RawHandle() const { return myRawHandle; }

  //! Set action handle.
  void SetRawHandle(uint64_t theHande) { myRawHandle = theHande; }

  //! Main constructor.
  Aspect_XRAction(const TCollection_AsciiString& theId, const Aspect_XRActionType theType)
      : myId(theId),
        myRawHandle(0),
        myType(theType)
  {
  }

protected:
  TCollection_AsciiString myId;        //!< action id
  uint64_t                myRawHandle; //!< action handle
  Aspect_XRActionType     myType;      //!< action type
};

//! Map of actions with action Id as a key.

#endif // _Aspect_XRAction_HeaderFile
