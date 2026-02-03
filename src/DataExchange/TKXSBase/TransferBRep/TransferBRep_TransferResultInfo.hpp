// Created on: 1999-08-11
// Created by: Roman LYGIN
// Copyright (c) 1999 Matra Datavision
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

#ifndef _TransferBRep_TransferResultInfo_HeaderFile
#define _TransferBRep_TransferResultInfo_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! Data structure for storing information on transfer result.
//! At the moment it dispatches information for the following types:
//! - result,
//! - result + warning(s),
//! - result + fail(s),
//! - result + warning(s) + fail(s)
//! - no result,
//! - no result + warning(s),
//! - no result + fail(s),
//! - no result + warning(s) + fail(s),
class TransferBRep_TransferResultInfo : public Standard_Transient
{

public:
  //! Creates object with all fields nullified.
  Standard_EXPORT TransferBRep_TransferResultInfo();

  //! Resets all the fields.
  Standard_EXPORT void Clear();

  int& Result();

  int& ResultWarning();

  int& ResultFail();

  int& ResultWarningFail();

  int& NoResult();

  int& NoResultWarning();

  int& NoResultFail();

  int& NoResultWarningFail();

  DEFINE_STANDARD_RTTIEXT(TransferBRep_TransferResultInfo, Standard_Transient)

private:
  int myR;
  int myRW;
  int myRF;
  int myRWF;
  int myNR;
  int myNRW;
  int myNRF;
  int myNRWF;
};
// Created on: 1999-08-11
// Created by: Roman LYGIN
// Copyright (c) 1999-1999 Matra Datavision
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

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::Result()
{
  return myR;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::ResultWarning()
{
  return myRW;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::ResultFail()
{
  return myRF;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::ResultWarningFail()
{
  return myRWF;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::NoResult()
{
  return myNR;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::NoResultWarning()
{
  return myNRW;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::NoResultFail()
{
  return myNRF;
}

//=================================================================================================

inline int& TransferBRep_TransferResultInfo::NoResultWarningFail()
{
  return myNRWF;
}


#endif // _TransferBRep_TransferResultInfo_HeaderFile
