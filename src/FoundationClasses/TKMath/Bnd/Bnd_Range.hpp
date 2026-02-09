#pragma once

#include <Standard_ConstructionError.hpp>

#include <NCollection_List.hpp>

class Bnd_Range
{
public:
  Bnd_Range()
      : myFirst(0.0),
        myLast(-1.0)
  {
  }

  Bnd_Range(const double theMin, const double theMax)
      : myFirst(theMin),
        myLast(theMax)
  {
    if (myLast < myFirst)
      throw Standard_ConstructionError("Last < First");
  }

  Standard_EXPORT void Common(const Bnd_Range& theOther);

  Standard_EXPORT bool Union(const Bnd_Range& theOther);

  Standard_EXPORT void Split(const double                 theVal,
                             NCollection_List<Bnd_Range>& theList,
                             const double                 thePeriod = 0.0) const;

  Standard_EXPORT int IsIntersected(const double theVal, const double thePeriod = 0.0) const;

  void Add(const double theParameter)
  {
    if (IsVoid())
    {
      myFirst = myLast = theParameter;
      return;
    }

    myFirst = (std::min)(myFirst, theParameter);
    myLast  = (std::max)(myLast, theParameter);
  }

  void Add(const Bnd_Range& theRange)
  {
    if (theRange.IsVoid())
    {
      return;
    }
    else if (IsVoid())
    {
      *this = theRange;
    }
    myFirst = (std::min)(myFirst, theRange.myFirst);
    myLast  = (std::max)(myLast, theRange.myLast);
  }

  bool GetMin(double& thePar) const
  {
    if (IsVoid())
    {
      return false;
    }

    thePar = myFirst;
    return true;
  }

  bool GetMax(double& thePar) const
  {
    if (IsVoid())
    {
      return false;
    }

    thePar = myLast;
    return true;
  }

  bool GetBounds(double& theFirstPar, double& theLastPar) const
  {
    if (IsVoid())
    {
      return false;
    }

    theFirstPar = myFirst;
    theLastPar  = myLast;
    return true;
  }

  bool GetIntermediatePoint(const double theLambda, double& theParameter) const
  {
    if (IsVoid())
    {
      return false;
    }

    theParameter = myFirst + theLambda * (myLast - myFirst);
    return true;
  }

  double Delta() const { return (myLast - myFirst); }

  bool IsVoid() const { return (myLast < myFirst); }

  void SetVoid()
  {
    myLast  = -1.0;
    myFirst = 0.0;
  }

  void Enlarge(const double theDelta)
  {
    if (IsVoid())
    {
      return;
    }

    myFirst -= theDelta;
    myLast += theDelta;
  }

  Bnd_Range Shifted(const double theVal) const
  {
    return !IsVoid() ? Bnd_Range(myFirst + theVal, myLast + theVal) : Bnd_Range();
  }

  void Shift(const double theVal)
  {
    if (!IsVoid())
    {
      myFirst += theVal;
      myLast += theVal;
    }
  }

  void TrimFrom(const double theValLower)
  {
    if (!IsVoid())
    {
      myFirst = (std::max)(myFirst, theValLower);
    }
  }

  void TrimTo(const double theValUpper)
  {
    if (!IsVoid())
    {
      myLast = (std::min)(myLast, theValUpper);
    }
  }

  bool IsOut(double theValue) const { return IsVoid() || theValue < myFirst || theValue > myLast; }

  bool IsOut(const Bnd_Range& theRange) const
  {
    return IsVoid() || theRange.IsVoid() || theRange.myLast < myFirst || theRange.myFirst > myLast;
  }

  bool operator==(const Bnd_Range& theOther) const
  {
    return ((myFirst == theOther.myFirst) && (myLast == theOther.myLast));
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  double myFirst;
  double myLast;
};
