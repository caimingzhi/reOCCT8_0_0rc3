#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class BOPDS_IndexRange
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_IndexRange();

  void SetFirst(const int theI1);

  void SetLast(const int theI2);

  int First() const;

  int Last() const;

  void SetIndices(const int theI1, const int theI2);

  void Indices(int& theI1, int& theI2) const;

  bool Contains(const int theIndex) const;

  Standard_EXPORT void Dump() const;

protected:
  int myFirst;
  int myLast;
};

inline BOPDS_IndexRange::BOPDS_IndexRange()
    : myFirst(0),
      myLast(0)
{
}

inline void BOPDS_IndexRange::SetFirst(const int aFirst)
{
  myFirst = aFirst;
}

inline int BOPDS_IndexRange::First() const
{
  return myFirst;
}

inline void BOPDS_IndexRange::SetLast(const int aLast)
{
  myLast = aLast;
}

inline int BOPDS_IndexRange::Last() const
{
  return myLast;
}

inline void BOPDS_IndexRange::SetIndices(const int theI1, const int theI2)
{
  myFirst = theI1;
  myLast  = theI2;
}

inline void BOPDS_IndexRange::Indices(int& theI1, int& theI2) const
{
  theI1 = myFirst;
  theI2 = myLast;
}

inline bool BOPDS_IndexRange::Contains(const int aIndex) const
{
  return aIndex >= myFirst && aIndex <= myLast;
}
