#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_HashUtils.hpp>

class IntPolyh_Couple
{
public:
  DEFINE_STANDARD_ALLOC

  IntPolyh_Couple()
      : myIndex1(-1),
        myIndex2(-1),
        myAnalyzed(false),
        myAngle(-2.0)
  {
  }

  IntPolyh_Couple(const int theTriangle1, const int theTriangle2, const double theAngle = -2.0)
      : myIndex1(theTriangle1),
        myIndex2(theTriangle2),
        myAnalyzed(false),
        myAngle(theAngle)
  {
  }

  int FirstValue() const { return myIndex1; }

  int SecondValue() const { return myIndex2; }

  bool IsAnalyzed() const { return myAnalyzed; }

  double Angle() const { return myAngle; }

  void SetCoupleValue(const int theInd1, const int theInd2)
  {
    myIndex1 = theInd1;
    myIndex2 = theInd2;
  }

  void SetAnalyzed(const bool theAnalyzed) { myAnalyzed = theAnalyzed; }

  void SetAngle(const double theAngle) { myAngle = theAngle; }

  bool IsEqual(const IntPolyh_Couple& theOther) const
  {
    return (myIndex1 == theOther.myIndex1 && myIndex2 == theOther.myIndex2)
           || (myIndex1 == theOther.myIndex2 && myIndex2 == theOther.myIndex1);
  }

  bool operator==(const IntPolyh_Couple& theOther) const { return IsEqual(theOther); }

  Standard_EXPORT void Dump(const int v) const;

private:
  int    myIndex1;
  int    myIndex2;
  bool   myAnalyzed;
  double myAngle;
};

namespace std
{
  template <>
  struct hash<IntPolyh_Couple>
  {
    size_t operator()(const IntPolyh_Couple& theCouple) const noexcept
    {

      int aCombination[2]{theCouple.FirstValue(), theCouple.SecondValue()};
      if (aCombination[0] > aCombination[1])
      {
        std::swap(aCombination[0], aCombination[1]);
      }
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std
