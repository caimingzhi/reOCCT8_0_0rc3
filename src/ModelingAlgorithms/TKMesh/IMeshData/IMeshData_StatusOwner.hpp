#pragma once

#include <IMeshData_Status.hpp>

class IMeshData_StatusOwner
{
public:
  virtual ~IMeshData_StatusOwner() = default;

  bool IsEqual(const IMeshData_Status theValue) const { return (myStatus == theValue); }

  bool IsSet(const IMeshData_Status theValue) const { return (myStatus & theValue) != 0; }

  void SetStatus(const IMeshData_Status theValue) { myStatus |= theValue; }

  void UnsetStatus(const IMeshData_Status theValue) { myStatus &= ~theValue; }

  int GetStatusMask() const { return myStatus; }

protected:
  IMeshData_StatusOwner()
      : myStatus(IMeshData_NoError)
  {
  }

private:
  int myStatus;
};
