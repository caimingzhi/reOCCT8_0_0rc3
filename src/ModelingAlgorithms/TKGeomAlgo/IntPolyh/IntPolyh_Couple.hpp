#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_HashUtils.hpp>

//! The class represents the couple of indices with additional
//! characteristics such as analyzed flag and an angle.
//! In IntPolyh_MaillageAffinage algorithm the class is used as a
//! couple of interfering triangles with the intersection angle.
class IntPolyh_Couple
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor
  IntPolyh_Couple()
      : myIndex1(-1),
        myIndex2(-1),
        myAnalyzed(false),
        myAngle(-2.0)
  {
  }

  //! Constructor
  IntPolyh_Couple(const int theTriangle1, const int theTriangle2, const double theAngle = -2.0)
      : myIndex1(theTriangle1),
        myIndex2(theTriangle2),
        myAnalyzed(false),
        myAngle(theAngle)
  {
  }

  //! Returns the first index
  int FirstValue() const { return myIndex1; }

  //! Returns the second index
  int SecondValue() const { return myIndex2; }

  //! Returns TRUE if the couple has been analyzed
  bool IsAnalyzed() const { return myAnalyzed; }

  //! Returns the angle
  double Angle() const { return myAngle; }

  //! Sets the triangles
  void SetCoupleValue(const int theInd1, const int theInd2)
  {
    myIndex1 = theInd1;
    myIndex2 = theInd2;
  }

  //! Sets the analyzed flag
  void SetAnalyzed(const bool theAnalyzed) { myAnalyzed = theAnalyzed; }

  //! Sets the angle
  void SetAngle(const double theAngle) { myAngle = theAngle; }

  //! Returns true if the Couple is equal to <theOther>
  bool IsEqual(const IntPolyh_Couple& theOther) const
  {
    return (myIndex1 == theOther.myIndex1 && myIndex2 == theOther.myIndex2)
           || (myIndex1 == theOther.myIndex2 && myIndex2 == theOther.myIndex1);
  }

  //! Returns true if the Couple is equal to <theOther>
  bool operator==(const IntPolyh_Couple& theOther) const { return IsEqual(theOther); }

  // Dump
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
      // Combine two int values into a single hash value.
      int aCombination[2]{theCouple.FirstValue(), theCouple.SecondValue()};
      if (aCombination[0] > aCombination[1])
      {
        std::swap(aCombination[0], aCombination[1]);
      }
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std
