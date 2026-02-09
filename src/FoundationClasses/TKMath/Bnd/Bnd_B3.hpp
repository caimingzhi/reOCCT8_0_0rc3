#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Real.hpp>
#include <Standard_ShortReal.hpp>
#include <gp.hpp>
#include <gp_XYZ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>

#include <array>

template <typename RealType>
class Bnd_B3
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr Bnd_B3() noexcept;

  constexpr Bnd_B3(const gp_XYZ& theCenter, const gp_XYZ& theHSize) noexcept;

  constexpr Bnd_B3(const std::array<RealType, 3>& theCenter,
                   const std::array<RealType, 3>& theHSize) noexcept;

  constexpr bool IsVoid() const noexcept;

  void Clear() noexcept;

  void Add(const gp_XYZ& thePnt);

  void Add(const gp_Pnt& thePnt);

  void Add(const Bnd_B3<RealType>& theBox);

  gp_XYZ CornerMin() const noexcept;

  gp_XYZ CornerMax() const noexcept;

  constexpr double SquareExtent() const noexcept;

  void Enlarge(const double theDiff) noexcept;

  bool Limit(const Bnd_B3<RealType>& theOtherBox);

  [[nodiscard]] Bnd_B3<RealType> Transformed(const gp_Trsf& theTrsf) const;

  constexpr bool IsOut(const gp_XYZ& thePnt) const noexcept;

  bool IsOut(const gp_XYZ& theCenter,
             const double  theRadius,
             const bool    isSphereHollow = false) const;

  constexpr bool IsOut(const Bnd_B3<RealType>& theOtherBox) const noexcept;

  bool IsOut(const Bnd_B3<RealType>& theOtherBox, const gp_Trsf& theTrsf) const;

  bool IsOut(const gp_Ax1& theLine,
             const bool    isRay            = false,
             const double  theOverthickness = 0.0) const;

  bool IsOut(const gp_Ax3& thePlane) const;

  constexpr bool IsIn(const Bnd_B3<RealType>& theBox) const noexcept;

  bool IsIn(const Bnd_B3<RealType>& theBox, const gp_Trsf& theTrsf) const;

  void SetCenter(const gp_XYZ& theCenter) noexcept;

  void SetCenter(const std::array<RealType, 3>& theCenter) noexcept;

  void SetHSize(const gp_XYZ& theHSize) noexcept;

  void SetHSize(const std::array<RealType, 3>& theHSize) noexcept;

  constexpr const std::array<RealType, 3>& Center() const noexcept;

  constexpr const std::array<RealType, 3>& HSize() const noexcept;

protected:
  static constexpr bool compareDist(const RealType aHSize[3], const RealType aDist[3]) noexcept
  {
    return (std::abs(aDist[0]) > aHSize[0] || std::abs(aDist[1]) > aHSize[1]
            || std::abs(aDist[2]) > aHSize[2]);
  }

  static bool compareDistD(const gp_XYZ& aHSize, const gp_XYZ& aDist) noexcept
  {
    return (std::abs(aDist.X()) > aHSize.X() || std::abs(aDist.Y()) > aHSize.Y()
            || std::abs(aDist.Z()) > aHSize.Z());
  }

  static constexpr RealType THE_RealLast = RealType(1e30);

private:
  std::array<RealType, 3> myCenter;
  std::array<RealType, 3> myHSize;
};

template <typename RealType>
constexpr inline Bnd_B3<RealType>::Bnd_B3() noexcept
    : myCenter{THE_RealLast, THE_RealLast, THE_RealLast},
      myHSize{-THE_RealLast, -THE_RealLast, -THE_RealLast}
{
}

template <typename RealType>
constexpr inline Bnd_B3<RealType>::Bnd_B3(const gp_XYZ& theCenter, const gp_XYZ& theHSize) noexcept
    : myCenter{RealType(theCenter.X()), RealType(theCenter.Y()), RealType(theCenter.Z())},
      myHSize{RealType(theHSize.X()), RealType(theHSize.Y()), RealType(theHSize.Z())}
{
}

template <typename RealType>
constexpr inline Bnd_B3<RealType>::Bnd_B3(const std::array<RealType, 3>& theCenter,
                                          const std::array<RealType, 3>& theHSize) noexcept
    : myCenter(theCenter),
      myHSize(theHSize)
{
}

template <typename RealType>
inline void Bnd_B3<RealType>::Clear() noexcept
{
  myCenter[0] = THE_RealLast;
  myCenter[1] = THE_RealLast;
  myCenter[2] = THE_RealLast;
  myHSize[0]  = -THE_RealLast;
  myHSize[1]  = -THE_RealLast;
  myHSize[2]  = -THE_RealLast;
}

template <typename RealType>
constexpr inline bool Bnd_B3<RealType>::IsVoid() const noexcept
{
  return (myHSize[0] < -1e-5);
}

template <typename RealType>
inline void Bnd_B3<RealType>::Add(const gp_Pnt& thePnt)
{
  Add(thePnt.XYZ());
}

template <typename RealType>
inline void Bnd_B3<RealType>::Add(const Bnd_B3<RealType>& theBox)
{
  if (!theBox.IsVoid())
  {
    Add(theBox.CornerMin());
    Add(theBox.CornerMax());
  }
}

template <typename RealType>
inline gp_XYZ Bnd_B3<RealType>::CornerMin() const noexcept
{
  return gp_XYZ(myCenter[0] - myHSize[0], myCenter[1] - myHSize[1], myCenter[2] - myHSize[2]);
}

template <typename RealType>
inline gp_XYZ Bnd_B3<RealType>::CornerMax() const noexcept
{
  return gp_XYZ(myCenter[0] + myHSize[0], myCenter[1] + myHSize[1], myCenter[2] + myHSize[2]);
}

template <typename RealType>
constexpr inline double Bnd_B3<RealType>::SquareExtent() const noexcept
{
  return 4 * (myHSize[0] * myHSize[0] + myHSize[1] * myHSize[1] + myHSize[2] * myHSize[2]);
}

template <typename RealType>
inline void Bnd_B3<RealType>::SetCenter(const gp_XYZ& theCenter) noexcept
{
  myCenter[0] = RealType(theCenter.X());
  myCenter[1] = RealType(theCenter.Y());
  myCenter[2] = RealType(theCenter.Z());
}

template <typename RealType>
inline void Bnd_B3<RealType>::SetHSize(const gp_XYZ& theHSize) noexcept
{
  myHSize[0] = RealType(theHSize.X());
  myHSize[1] = RealType(theHSize.Y());
  myHSize[2] = RealType(theHSize.Z());
}

template <typename RealType>
inline void Bnd_B3<RealType>::SetCenter(const std::array<RealType, 3>& theCenter) noexcept
{
  myCenter = theCenter;
}

template <typename RealType>
inline void Bnd_B3<RealType>::SetHSize(const std::array<RealType, 3>& theHSize) noexcept
{
  myHSize = theHSize;
}

template <typename RealType>
constexpr inline const std::array<RealType, 3>& Bnd_B3<RealType>::Center() const noexcept
{
  return myCenter;
}

template <typename RealType>
constexpr inline const std::array<RealType, 3>& Bnd_B3<RealType>::HSize() const noexcept
{
  return myHSize;
}

template <typename RealType>
inline void Bnd_B3<RealType>::Enlarge(const double aDiff) noexcept
{
  const double aD = std::abs(aDiff);
  myHSize[0] += RealType(aD);
  myHSize[1] += RealType(aD);
  myHSize[2] += RealType(aD);
}

template <typename RealType>
constexpr inline bool Bnd_B3<RealType>::IsOut(const gp_XYZ& thePnt) const noexcept
{
  return (std::abs(RealType(thePnt.X()) - myCenter[0]) > myHSize[0]
          || std::abs(RealType(thePnt.Y()) - myCenter[1]) > myHSize[1]
          || std::abs(RealType(thePnt.Z()) - myCenter[2]) > myHSize[2]);
}

template <typename RealType>
constexpr inline bool Bnd_B3<RealType>::IsOut(const Bnd_B3<RealType>& theBox) const noexcept
{
  return (std::abs(theBox.myCenter[0] - myCenter[0]) > theBox.myHSize[0] + myHSize[0]
          || std::abs(theBox.myCenter[1] - myCenter[1]) > theBox.myHSize[1] + myHSize[1]
          || std::abs(theBox.myCenter[2] - myCenter[2]) > theBox.myHSize[2] + myHSize[2]);
}

template <typename RealType>
constexpr inline bool Bnd_B3<RealType>::IsIn(const Bnd_B3<RealType>& theBox) const noexcept
{
  return (std::abs(theBox.myCenter[0] - myCenter[0]) < theBox.myHSize[0] - myHSize[0]
          && std::abs(theBox.myCenter[1] - myCenter[1]) < theBox.myHSize[1] - myHSize[1]
          && std::abs(theBox.myCenter[2] - myCenter[2]) < theBox.myHSize[2] - myHSize[2]);
}

template <typename RealType>
void Bnd_B3<RealType>::Add(const gp_XYZ& thePnt)
{
  if (IsVoid())
  {
    myCenter[0] = RealType(thePnt.X());
    myCenter[1] = RealType(thePnt.Y());
    myCenter[2] = RealType(thePnt.Z());
    myHSize[0]  = 0.;
    myHSize[1]  = 0.;
    myHSize[2]  = 0.;
  }
  else
  {
    const RealType aDiff[3] = {RealType(thePnt.X()) - myCenter[0],
                               RealType(thePnt.Y()) - myCenter[1],
                               RealType(thePnt.Z()) - myCenter[2]};
    if (aDiff[0] > myHSize[0])
    {
      const RealType aShift = (aDiff[0] - myHSize[0]) / 2;
      myCenter[0] += aShift;
      myHSize[0] += aShift;
    }
    else if (aDiff[0] < -myHSize[0])
    {
      const RealType aShift = (aDiff[0] + myHSize[0]) / 2;
      myCenter[0] += aShift;
      myHSize[0] -= aShift;
    }
    if (aDiff[1] > myHSize[1])
    {
      const RealType aShift = (aDiff[1] - myHSize[1]) / 2;
      myCenter[1] += aShift;
      myHSize[1] += aShift;
    }
    else if (aDiff[1] < -myHSize[1])
    {
      const RealType aShift = (aDiff[1] + myHSize[1]) / 2;
      myCenter[1] += aShift;
      myHSize[1] -= aShift;
    }
    if (aDiff[2] > myHSize[2])
    {
      const RealType aShift = (aDiff[2] - myHSize[2]) / 2;
      myCenter[2] += aShift;
      myHSize[2] += aShift;
    }
    else if (aDiff[2] < -myHSize[2])
    {
      const RealType aShift = (aDiff[2] + myHSize[2]) / 2;
      myCenter[2] += aShift;
      myHSize[2] -= aShift;
    }
  }
}

template <typename RealType>
bool Bnd_B3<RealType>::Limit(const Bnd_B3<RealType>& theBox)
{
  bool           aResult(false);
  const RealType diffC[3] = {theBox.myCenter[0] - myCenter[0],
                             theBox.myCenter[1] - myCenter[1],
                             theBox.myCenter[2] - myCenter[2]};
  const RealType sumH[3]  = {theBox.myHSize[0] + myHSize[0],
                             theBox.myHSize[1] + myHSize[1],
                             theBox.myHSize[2] + myHSize[2]};

  if (!compareDist(sumH, diffC))
  {
    const RealType diffH[3] = {theBox.myHSize[0] - myHSize[0],
                               theBox.myHSize[1] - myHSize[1],
                               theBox.myHSize[2] - myHSize[2]};
    if (diffC[0] - diffH[0] > 0.)
    {
      const RealType aShift = (diffC[0] - diffH[0]) / 2;
      myCenter[0] += aShift;
      myHSize[0] -= aShift;
    }
    else if (diffC[0] + diffH[0] < 0.)
    {
      const RealType aShift = (diffC[0] + diffH[0]) / 2;
      myCenter[0] += aShift;
      myHSize[0] += aShift;
    }
    if (diffC[1] - diffH[1] > 0.)
    {
      const RealType aShift = (diffC[1] - diffH[1]) / 2;
      myCenter[1] += aShift;
      myHSize[1] -= aShift;
    }
    else if (diffC[1] + diffH[1] < 0.)
    {
      const RealType aShift = (diffC[1] + diffH[1]) / 2;
      myCenter[1] += aShift;
      myHSize[1] += aShift;
    }
    if (diffC[2] - diffH[2] > 0.)
    {
      const RealType aShift = (diffC[2] - diffH[2]) / 2;
      myCenter[2] += aShift;
      myHSize[2] -= aShift;
    }
    else if (diffC[2] + diffH[2] < 0.)
    {
      const RealType aShift = (diffC[2] + diffH[2]) / 2;
      myCenter[2] += aShift;
      myHSize[2] += aShift;
    }
    aResult = true;
  }
  return aResult;
}

template <typename RealType>
Bnd_B3<RealType> Bnd_B3<RealType>::Transformed(const gp_Trsf& theTrsf) const
{
  Bnd_B3<RealType>  aResult;
  const gp_TrsfForm aForm     = theTrsf.Form();
  const double      aScale    = theTrsf.ScaleFactor();
  const double      aScaleAbs = std::abs(aScale);
  if (aForm == gp_Identity)
    aResult = *this;
  else if (aForm == gp_Translation || aForm == gp_PntMirror || aForm == gp_Scale)
  {
    aResult.myCenter[0] = (RealType)(myCenter[0] * aScale + theTrsf.TranslationPart().X());
    aResult.myCenter[1] = (RealType)(myCenter[1] * aScale + theTrsf.TranslationPart().Y());
    aResult.myCenter[2] = (RealType)(myCenter[2] * aScale + theTrsf.TranslationPart().Z());
    aResult.myHSize[0]  = (RealType)(myHSize[0] * aScaleAbs);
    aResult.myHSize[1]  = (RealType)(myHSize[1] * aScaleAbs);
    aResult.myHSize[2]  = (RealType)(myHSize[2] * aScaleAbs);
  }
  else
  {
    gp_XYZ aCenter((double)myCenter[0], (double)myCenter[1], (double)myCenter[2]);
    theTrsf.Transforms(aCenter);
    aResult.myCenter[0] = (RealType)aCenter.X();
    aResult.myCenter[1] = (RealType)aCenter.Y();
    aResult.myCenter[2] = (RealType)aCenter.Z();

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);
    aResult.myHSize[0] =
      (RealType)(aScaleAbs
                 * (std::abs(aMat[0]) * myHSize[0] + std::abs(aMat[1]) * myHSize[1]
                    + std::abs(aMat[2]) * myHSize[2]));
    aResult.myHSize[1] =
      (RealType)(aScaleAbs
                 * (std::abs(aMat[3]) * myHSize[0] + std::abs(aMat[4]) * myHSize[1]
                    + std::abs(aMat[5]) * myHSize[2]));
    aResult.myHSize[2] =
      (RealType)(aScaleAbs
                 * (std::abs(aMat[6]) * myHSize[0] + std::abs(aMat[7]) * myHSize[1]
                    + std::abs(aMat[8]) * myHSize[2]));
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B3<RealType>::IsOut(const gp_XYZ& theCenter,
                             const double  theRadius,
                             const bool    isSphereHollow) const
{
  bool aResult(true);
  if (!isSphereHollow)
  {

    const double aDist[3] = {std::abs(theCenter.X() - double(myCenter[0])) - double(myHSize[0]),
                             std::abs(theCenter.Y() - double(myCenter[1])) - double(myHSize[1]),
                             std::abs(theCenter.Z() - double(myCenter[2])) - double(myHSize[2])};
    double       aD(0.);
    if (aDist[0] > 0.)
      aD = aDist[0] * aDist[0];
    if (aDist[1] > 0.)
      aD += aDist[1] * aDist[1];
    if (aDist[2] > 0.)
      aD += aDist[2] * aDist[2];
    aResult = (aD > theRadius * theRadius);
  }
  else
  {
    const double aDistC[3] = {std::abs(theCenter.X() - double(myCenter[0])),
                              std::abs(theCenter.Y() - double(myCenter[1])),
                              std::abs(theCenter.Z() - double(myCenter[2]))};

    double aDist[3] = {aDistC[0] - double(myHSize[0]),
                       aDistC[1] - double(myHSize[1]),
                       aDistC[2] - double(myHSize[2])};
    double aD(0.);
    if (aDist[0] > 0.)
      aD = aDist[0] * aDist[0];
    if (aDist[1] > 0.)
      aD += aDist[1] * aDist[1];
    if (aDist[2] > 0.)
      aD += aDist[2] * aDist[2];
    if (aD < theRadius * theRadius)
    {

      aDist[0] = aDistC[0] + double(myHSize[0]);
      aDist[1] = aDistC[1] + double(myHSize[1]);
      aDist[2] = aDistC[2] + double(myHSize[2]);
      if (aDist[0] * aDist[0] + aDist[1] * aDist[1] + aDist[2] * aDist[2] > theRadius * theRadius)
        aResult = false;
    }
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B3<RealType>::IsOut(const Bnd_B3<RealType>& theBox, const gp_Trsf& theTrsf) const
{
  bool              aResult(false);
  const gp_TrsfForm aForm     = theTrsf.Form();
  const double      aScale    = theTrsf.ScaleFactor();
  const double      aScaleAbs = std::abs(aScale);
  if (aForm == gp_Translation || aForm == gp_Identity || aForm == gp_PntMirror || aForm == gp_Scale)
  {
    aResult =
      (std::abs(RealType(theBox.myCenter[0] * aScale + theTrsf.TranslationPart().X()) - myCenter[0])
         > RealType(theBox.myHSize[0] * aScaleAbs) + myHSize[0]
       || std::abs(RealType(theBox.myCenter[1] * aScale + theTrsf.TranslationPart().Y())
                   - myCenter[1])
            > RealType(theBox.myHSize[1] * aScaleAbs) + myHSize[1]
       || std::abs(RealType(theBox.myCenter[2] * aScale + theTrsf.TranslationPart().Z())
                   - myCenter[2])
            > RealType(theBox.myHSize[2] * aScaleAbs) + myHSize[2]);
  }
  else
  {

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);

    gp_XYZ aCenter((double)theBox.myCenter[0],
                   (double)theBox.myCenter[1],
                   (double)theBox.myCenter[2]);
    theTrsf.Transforms(aCenter);
    const double aDist[3]   = {aCenter.X() - (double)myCenter[0],
                               aCenter.Y() - (double)myCenter[1],
                               aCenter.Z() - (double)myCenter[2]};
    const double aMatAbs[9] = {std::abs(aMat[0]),
                               std::abs(aMat[1]),
                               std::abs(aMat[2]),
                               std::abs(aMat[3]),
                               std::abs(aMat[4]),
                               std::abs(aMat[5]),
                               std::abs(aMat[6]),
                               std::abs(aMat[7]),
                               std::abs(aMat[8])};
    if (std::abs(aDist[0]) > (aScaleAbs
                                * (aMatAbs[0] * theBox.myHSize[0] + aMatAbs[1] * theBox.myHSize[1]
                                   + aMatAbs[2] * theBox.myHSize[2])
                              + (double)myHSize[0])
        || std::abs(aDist[1])
             > (aScaleAbs
                  * (aMatAbs[3] * theBox.myHSize[0] + aMatAbs[4] * theBox.myHSize[1]
                     + aMatAbs[5] * theBox.myHSize[2])
                + (double)myHSize[1])
        || std::abs(aDist[2])
             > (aScaleAbs
                  * (aMatAbs[6] * theBox.myHSize[0] + aMatAbs[7] * theBox.myHSize[1]
                     + aMatAbs[8] * theBox.myHSize[2])
                + (double)myHSize[2]))
      aResult = true;

    else
    {

      if ((std::abs(aMat[0] * aDist[0] + aMat[3] * aDist[1] + aMat[6] * aDist[2])
           > theBox.myHSize[0] * aScaleAbs
               + (aMatAbs[0] * myHSize[0] + aMatAbs[3] * myHSize[1] + aMatAbs[6] * myHSize[2]))
          || (std::abs(aMat[1] * aDist[0] + aMat[4] * aDist[1] + aMat[7] * aDist[2])
              > theBox.myHSize[1] * aScaleAbs
                  + (aMatAbs[1] * myHSize[0] + aMatAbs[4] * myHSize[1] + aMatAbs[7] * myHSize[2]))
          || (std::abs(aMat[2] * aDist[0] + aMat[5] * aDist[1] + aMat[8] * aDist[2])
              > theBox.myHSize[2] * aScaleAbs
                  + (aMatAbs[2] * myHSize[0] + aMatAbs[5] * myHSize[1] + aMatAbs[8] * myHSize[2])))
        aResult = true;
    }
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B3<RealType>::IsOut(const gp_Ax3& thePlane) const
{
  if (IsVoid())
    return true;
  const gp_XYZ& anOrigin = thePlane.Location().XYZ();
  const gp_XYZ& aDir     = thePlane.Direction().XYZ();
  const gp_XYZ  aBoxCenter((double)myCenter[0], (double)myCenter[1], (double)myCenter[2]);
  const double  aDist0 = (aBoxCenter - anOrigin) * aDir;

  const double aDist1 = double(myHSize[0]) * std::abs(aDir.X())
                        + double(myHSize[1]) * std::abs(aDir.Y())
                        + double(myHSize[2]) * std::abs(aDir.Z());
  return ((aDist0 + aDist1) * (aDist0 - aDist1) > 0.);
}

template <typename RealType>
bool Bnd_B3<RealType>::IsOut(const gp_Ax1& theLine,
                             const bool    isRay,
                             const double  theOverthickness) const
{
  const double aRes = gp::Resolution() * 100.;
  if (IsVoid())
    return true;
  double        anInter0[2] = {-RealLast(), RealLast()}, anInter1[2] = {-RealLast(), RealLast()};
  const gp_XYZ& aDir = theLine.Direction().XYZ();
  const gp_XYZ  aDiff((double)myCenter[0] - theLine.Location().X(),
                     (double)myCenter[1] - theLine.Location().Y(),
                     (double)myCenter[2] - theLine.Location().Z());

  double aHSize = (double)myHSize[0] + theOverthickness;
  if (aDir.X() > aRes)
  {
    anInter0[0] = (aDiff.X() - aHSize) / aDir.X();
    anInter0[1] = (aDiff.X() + aHSize) / aDir.X();
  }
  else if (aDir.X() < -aRes)
  {
    anInter0[0] = (aDiff.X() + aHSize) / aDir.X();
    anInter0[1] = (aDiff.X() - aHSize) / aDir.X();
  }
  else

    if (std::abs(aDiff.X()) > aHSize)
    return true;

  aHSize = (double)myHSize[1] + theOverthickness;
  if (aDir.Y() > aRes)
  {
    anInter1[0] = (aDiff.Y() - aHSize) / aDir.Y();
    anInter1[1] = (aDiff.Y() + aHSize) / aDir.Y();
  }
  else if (aDir.Y() < -aRes)
  {
    anInter1[0] = (aDiff.Y() + aHSize) / aDir.Y();
    anInter1[1] = (aDiff.Y() - aHSize) / aDir.Y();
  }
  else

    if (std::abs(aDiff.Y()) > aHSize)
    return true;

  if (anInter0[0] > (anInter1[1] + aRes) || anInter0[1] < (anInter1[0] - aRes))
    return true;
  if (anInter1[0] > anInter0[0])
    anInter0[0] = anInter1[0];
  if (anInter1[1] < anInter0[1])
    anInter0[1] = anInter1[1];
  if (isRay && anInter0[1] < -aRes)
    return true;

  aHSize = (double)myHSize[2] + theOverthickness;
  if (aDir.Z() > aRes)
  {
    anInter1[0] = (aDiff.Z() - aHSize) / aDir.Z();
    anInter1[1] = (aDiff.Z() + aHSize) / aDir.Z();
  }
  else if (aDir.Z() < -aRes)
  {
    anInter1[0] = (aDiff.Z() + aHSize) / aDir.Z();
    anInter1[1] = (aDiff.Z() - aHSize) / aDir.Z();
  }
  else

    return (std::abs(aDiff.Z()) > aHSize);
  if (isRay && anInter1[1] < -aRes)
    return true;

  return (anInter0[0] > (anInter1[1] + aRes) || anInter0[1] < (anInter1[0] - aRes));
}

template <typename RealType>
bool Bnd_B3<RealType>::IsIn(const Bnd_B3<RealType>& theBox, const gp_Trsf& theTrsf) const
{
  bool              aResult(false);
  const gp_TrsfForm aForm     = theTrsf.Form();
  const double      aScale    = theTrsf.ScaleFactor();
  const double      aScaleAbs = std::abs(aScale);
  if (aForm == gp_Translation || aForm == gp_Identity || aForm == gp_PntMirror || aForm == gp_Scale)
  {
    aResult =
      (std::abs(RealType(theBox.myCenter[0] * aScale + theTrsf.TranslationPart().X()) - myCenter[0])
         < RealType(theBox.myHSize[0] * aScaleAbs) - myHSize[0]
       && std::abs(RealType(theBox.myCenter[1] * aScale + theTrsf.TranslationPart().Y())
                   - myCenter[1])
            < RealType(theBox.myHSize[1] * aScaleAbs) - myHSize[1]
       && std::abs(RealType(theBox.myCenter[2] * aScale + theTrsf.TranslationPart().Z())
                   - myCenter[2])
            < RealType(theBox.myHSize[2] * aScaleAbs) - myHSize[2]);
  }
  else
  {

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);
    gp_XYZ        aCenter((double)theBox.myCenter[0],
                   (double)theBox.myCenter[1],
                   (double)theBox.myCenter[2]);
    theTrsf.Transforms(aCenter);
    const double aDist[3] = {aCenter.X() - (double)myCenter[0],
                             aCenter.Y() - (double)myCenter[1],
                             aCenter.Z() - (double)myCenter[2]};
    if ((std::abs(aMat[0] * aDist[0] + aMat[3] * aDist[1] + aMat[6] * aDist[2])
         < theBox.myHSize[0] * aScaleAbs
             - (std::abs(aMat[0]) * myHSize[0] + std::abs(aMat[3]) * myHSize[1]
                + std::abs(aMat[6]) * myHSize[2]))
        && (std::abs(aMat[1] * aDist[0] + aMat[4] * aDist[1] + aMat[7] * aDist[2])
            < theBox.myHSize[1] * aScaleAbs
                - (std::abs(aMat[1]) * myHSize[0] + std::abs(aMat[4]) * myHSize[1]
                   + std::abs(aMat[7]) * myHSize[2]))
        && (std::abs(aMat[2] * aDist[0] + aMat[5] * aDist[1] + aMat[8] * aDist[2])
            < theBox.myHSize[2] * aScaleAbs
                - (std::abs(aMat[2]) * myHSize[0] + std::abs(aMat[5]) * myHSize[1]
                   + std::abs(aMat[8]) * myHSize[2])))
      aResult = true;
  }
  return aResult;
}

using Bnd_B3d = Bnd_B3<double>;

using Bnd_B3f = Bnd_B3<float>;
