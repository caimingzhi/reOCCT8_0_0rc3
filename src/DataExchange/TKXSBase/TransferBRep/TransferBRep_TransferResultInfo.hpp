#pragma once

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
