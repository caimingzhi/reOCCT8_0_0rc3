#pragma once

#include <IMeshData_Status.hpp>

//! Extension interface class providing status functionality.
class IMeshData_StatusOwner
{
public:
  //! Destructor.
  virtual ~IMeshData_StatusOwner() = default;

  //! Returns true in case if status is strictly equal to the given value.
  bool IsEqual(const IMeshData_Status theValue) const { return (myStatus == theValue); }

  //! Returns true in case if status is set.
  bool IsSet(const IMeshData_Status theValue) const { return (myStatus & theValue) != 0; }

  //! Adds status to status flags of a face.
  void SetStatus(const IMeshData_Status theValue) { myStatus |= theValue; }

  //! Adds status to status flags of a face.
  void UnsetStatus(const IMeshData_Status theValue) { myStatus &= ~theValue; }

  //! Returns complete status mask.
  int GetStatusMask() const { return myStatus; }

protected:
  //! Constructor. Initializes default status.
  IMeshData_StatusOwner()
      : myStatus(IMeshData_NoError)
  {
  }

private:
  int myStatus;
};
