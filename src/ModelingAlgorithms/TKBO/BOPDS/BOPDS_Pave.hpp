#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class BOPDS_Pave
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_Pave();

  void SetIndex(const int theIndex);

  int Index() const;

  void SetParameter(const double theParameter);

  double Parameter() const;

  void Contents(int& theIndex, double& theParameter) const;

  bool IsLess(const BOPDS_Pave& theOther) const;

  bool operator<(const BOPDS_Pave& theOther) const { return IsLess(theOther); }

  bool IsEqual(const BOPDS_Pave& theOther) const;

  bool operator==(const BOPDS_Pave& theOther) const { return IsEqual(theOther); }

  Standard_EXPORT void Dump() const;

protected:
  int    myIndex;
  double myParameter;
};

namespace std
{
  template <>
  struct hash<BOPDS_Pave>
  {
    size_t operator()(const BOPDS_Pave& thePave) const noexcept
    {
      size_t aCombination[2];
      aCombination[0] = opencascade::hash(thePave.Index());
      aCombination[1] = opencascade::hash(thePave.Parameter());
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std

inline BOPDS_Pave::BOPDS_Pave()
{
  myIndex     = -1;
  myParameter = 99.;
}

inline void BOPDS_Pave::SetIndex(const int theIndex)
{
  myIndex = theIndex;
}

inline int BOPDS_Pave::Index() const
{
  return myIndex;
}

inline void BOPDS_Pave::SetParameter(const double theParameter)
{
  myParameter = theParameter;
}

inline double BOPDS_Pave::Parameter() const
{
  return myParameter;
}

inline void BOPDS_Pave::Contents(int& theIndex, double& theParameter) const
{
  theIndex     = myIndex;
  theParameter = myParameter;
}

inline bool BOPDS_Pave::IsLess(const BOPDS_Pave& theOther) const
{
  return myParameter < theOther.myParameter;
}

inline bool BOPDS_Pave::IsEqual(const BOPDS_Pave& theOther) const
{
  bool bFlag;

  bFlag = ((myIndex == theOther.myIndex) && (myParameter == theOther.myParameter));
  return bFlag;
}
