#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>

class gp_Pnt2d;

class CSLib_Class2d
{
public:
  enum Result
  {
    Result_Inside    = 1,
    Result_Outside   = -1,
    Result_Uncertain = 0
  };

  DEFINE_STANDARD_ALLOC

  CSLib_Class2d() = default;

  Standard_EXPORT CSLib_Class2d(const NCollection_Array1<gp_Pnt2d>& thePnts2d,
                                double                              theTolU,
                                double                              theTolV,
                                double                              theUMin,
                                double                              theVMin,
                                double                              theUMax,
                                double                              theVMax);

  Standard_EXPORT CSLib_Class2d(const NCollection_Sequence<gp_Pnt2d>& thePnts2d,
                                double                                theTolU,
                                double                                theTolV,
                                double                                theUMin,
                                double                                theVMin,
                                double                                theUMax,
                                double                                theVMax);

  CSLib_Class2d(CSLib_Class2d&& theOther) noexcept
      : myPnts2dX(std::move(theOther.myPnts2dX)),
        myPnts2dY(std::move(theOther.myPnts2dY)),
        myTolU(theOther.myTolU),
        myTolV(theOther.myTolV),
        myPointsCount(theOther.myPointsCount),
        myUMin(theOther.myUMin),
        myVMin(theOther.myVMin),
        myUMax(theOther.myUMax),
        myVMax(theOther.myVMax)
  {
  }

  CSLib_Class2d& operator=(CSLib_Class2d&& theOther) noexcept
  {
    if (this != &theOther)
    {
      myPnts2dX     = std::move(theOther.myPnts2dX);
      myPnts2dY     = std::move(theOther.myPnts2dY);
      myTolU        = theOther.myTolU;
      myTolV        = theOther.myTolV;
      myPointsCount = theOther.myPointsCount;
      myUMin        = theOther.myUMin;
      myVMin        = theOther.myVMin;
      myUMax        = theOther.myUMax;
      myVMax        = theOther.myVMax;
    }
    return *this;
  }

  Standard_EXPORT Result SiDans(const gp_Pnt2d& thePoint) const;

  Standard_EXPORT Result SiDans_OnMode(const gp_Pnt2d& thePoint, double theTol) const;

private:
  bool internalSiDans(double theX, double theY) const;

  Result internalSiDansOuOn(double theX, double theY) const;

  template <class TCol_Containers2d>
  void init(const TCol_Containers2d& thePnts2d,
            double                   theTolU,
            double                   theTolV,
            double                   theUMin,
            double                   theVMin,
            double                   theUMax,
            double                   theVMax);

  CSLib_Class2d(const CSLib_Class2d&) = delete;

  CSLib_Class2d& operator=(const CSLib_Class2d&) = delete;

private:
  NCollection_Array1<double> myPnts2dX;
  NCollection_Array1<double> myPnts2dY;
  double                     myTolU        = 0.0;
  double                     myTolV        = 0.0;
  int                        myPointsCount = 0;
  double                     myUMin        = 0.0;
  double                     myVMin        = 0.0;
  double                     myUMax        = 0.0;
  double                     myVMax        = 0.0;
};
