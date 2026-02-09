#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Real.hpp>
#include <Standard_ShortReal.hpp>
#include <gp_XY.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Ax2d.hpp>

#include <array>

template <typename RealType>
class Bnd_B2
{
public:
  DEFINE_STANDARD_ALLOC

  constexpr Bnd_B2() noexcept;

  constexpr Bnd_B2(const gp_XY& theCenter, const gp_XY& theHSize) noexcept;

  constexpr Bnd_B2(const std::array<RealType, 2>& theCenter,
                   const std::array<RealType, 2>& theHSize) noexcept;

  constexpr bool IsVoid() const noexcept;

  void Clear() noexcept;

  void Add(const gp_XY& thePnt);

  void Add(const gp_Pnt2d& thePnt);

  void Add(const Bnd_B2<RealType>& theBox);

  gp_XY CornerMin() const noexcept;

  gp_XY CornerMax() const noexcept;

  constexpr double SquareExtent() const noexcept;

  void Enlarge(const double theDiff) noexcept;

  bool Limit(const Bnd_B2<RealType>& theOtherBox);

  [[nodiscard]] Bnd_B2<RealType> Transformed(const gp_Trsf2d& theTrsf) const;

  constexpr bool IsOut(const gp_XY& thePnt) const noexcept;

  bool IsOut(const gp_XY& theCenter,
             const double theRadius,
             const bool   isCircleHollow = false) const;

  constexpr bool IsOut(const Bnd_B2<RealType>& theOtherBox) const noexcept;

  bool IsOut(const Bnd_B2<RealType>& theOtherBox, const gp_Trsf2d& theTrsf) const;

  bool IsOut(const gp_Ax2d& theLine) const;

  bool IsOut(const gp_XY& theP0, const gp_XY& theP1) const;

  constexpr bool IsIn(const Bnd_B2<RealType>& theBox) const noexcept;

  bool IsIn(const Bnd_B2<RealType>& theBox, const gp_Trsf2d& theTrsf) const;

  void SetCenter(const gp_XY& theCenter) noexcept;

  void SetCenter(const std::array<RealType, 2>& theCenter) noexcept;

  void SetHSize(const gp_XY& theHSize) noexcept;

  void SetHSize(const std::array<RealType, 2>& theHSize) noexcept;

  constexpr const std::array<RealType, 2>& Center() const noexcept;

  constexpr const std::array<RealType, 2>& HSize() const noexcept;

protected:
  static constexpr bool compareDist(const RealType aHSize[2], const RealType aDist[2]) noexcept
  {
    return (std::abs(aDist[0]) > aHSize[0] || std::abs(aDist[1]) > aHSize[1]);
  }

  static bool compareDistD(const gp_XY& aHSize, const gp_XY& aDist) noexcept
  {
    return (std::abs(aDist.X()) > aHSize.X() || std::abs(aDist.Y()) > aHSize.Y());
  }

  static constexpr RealType THE_RealLast = RealType(1e30);

private:
  std::array<RealType, 2> myCenter;
  std::array<RealType, 2> myHSize;
};

template <typename RealType>
constexpr inline Bnd_B2<RealType>::Bnd_B2() noexcept
    : myCenter{THE_RealLast, THE_RealLast},
      myHSize{-THE_RealLast, -THE_RealLast}
{
}

template <typename RealType>
constexpr inline Bnd_B2<RealType>::Bnd_B2(const gp_XY& theCenter, const gp_XY& theHSize) noexcept
    : myCenter{RealType(theCenter.X()), RealType(theCenter.Y())},
      myHSize{RealType(theHSize.X()), RealType(theHSize.Y())}
{
}

template <typename RealType>
constexpr inline Bnd_B2<RealType>::Bnd_B2(const std::array<RealType, 2>& theCenter,
                                          const std::array<RealType, 2>& theHSize) noexcept
    : myCenter(theCenter),
      myHSize(theHSize)
{
}

template <typename RealType>
inline void Bnd_B2<RealType>::Clear() noexcept
{
  myCenter[0] = THE_RealLast;
  myCenter[1] = THE_RealLast;
  myHSize[0]  = -THE_RealLast;
  myHSize[1]  = -THE_RealLast;
}

template <typename RealType>
constexpr inline bool Bnd_B2<RealType>::IsVoid() const noexcept
{
  return (myHSize[0] < -1e-5);
}

template <typename RealType>
inline void Bnd_B2<RealType>::Add(const gp_Pnt2d& thePnt)
{
  Add(thePnt.XY());
}

template <typename RealType>
inline void Bnd_B2<RealType>::Add(const Bnd_B2<RealType>& theBox)
{
  if (!theBox.IsVoid())
  {
    Add(theBox.CornerMin());
    Add(theBox.CornerMax());
  }
}

template <typename RealType>
inline gp_XY Bnd_B2<RealType>::CornerMin() const noexcept
{
  return gp_XY(myCenter[0] - myHSize[0], myCenter[1] - myHSize[1]);
}

template <typename RealType>
inline gp_XY Bnd_B2<RealType>::CornerMax() const noexcept
{
  return gp_XY(myCenter[0] + myHSize[0], myCenter[1] + myHSize[1]);
}

template <typename RealType>
constexpr inline double Bnd_B2<RealType>::SquareExtent() const noexcept
{
  return 4 * (myHSize[0] * myHSize[0] + myHSize[1] * myHSize[1]);
}

template <typename RealType>
inline void Bnd_B2<RealType>::SetCenter(const gp_XY& theCenter) noexcept
{
  myCenter[0] = RealType(theCenter.X());
  myCenter[1] = RealType(theCenter.Y());
}

template <typename RealType>
inline void Bnd_B2<RealType>::SetHSize(const gp_XY& theHSize) noexcept
{
  myHSize[0] = RealType(theHSize.X());
  myHSize[1] = RealType(theHSize.Y());
}

template <typename RealType>
inline void Bnd_B2<RealType>::SetCenter(const std::array<RealType, 2>& theCenter) noexcept
{
  myCenter = theCenter;
}

template <typename RealType>
inline void Bnd_B2<RealType>::SetHSize(const std::array<RealType, 2>& theHSize) noexcept
{
  myHSize = theHSize;
}

template <typename RealType>
constexpr inline const std::array<RealType, 2>& Bnd_B2<RealType>::Center() const noexcept
{
  return myCenter;
}

template <typename RealType>
constexpr inline const std::array<RealType, 2>& Bnd_B2<RealType>::HSize() const noexcept
{
  return myHSize;
}

template <typename RealType>
inline void Bnd_B2<RealType>::Enlarge(const double aDiff) noexcept
{
  const RealType aD = RealType(std::abs(aDiff));
  myHSize[0] += aD;
  myHSize[1] += aD;
}

template <typename RealType>
constexpr inline bool Bnd_B2<RealType>::IsOut(const gp_XY& thePnt) const noexcept
{
  return (std::abs(RealType(thePnt.X()) - myCenter[0]) > myHSize[0]
          || std::abs(RealType(thePnt.Y()) - myCenter[1]) > myHSize[1]);
}

template <typename RealType>
constexpr inline bool Bnd_B2<RealType>::IsOut(const Bnd_B2<RealType>& theBox) const noexcept
{
  return (std::abs(theBox.myCenter[0] - myCenter[0]) > theBox.myHSize[0] + myHSize[0]
          || std::abs(theBox.myCenter[1] - myCenter[1]) > theBox.myHSize[1] + myHSize[1]);
}

template <typename RealType>
constexpr inline bool Bnd_B2<RealType>::IsIn(const Bnd_B2<RealType>& theBox) const noexcept
{
  return (std::abs(theBox.myCenter[0] - myCenter[0]) < theBox.myHSize[0] - myHSize[0]
          && std::abs(theBox.myCenter[1] - myCenter[1]) < theBox.myHSize[1] - myHSize[1]);
}

template <typename RealType>
void Bnd_B2<RealType>::Add(const gp_XY& thePnt)
{
  if (IsVoid())
  {
    myCenter[0] = RealType(thePnt.X());
    myCenter[1] = RealType(thePnt.Y());
    myHSize[0]  = 0.;
    myHSize[1]  = 0.;
  }
  else
  {
    const RealType aDiff[2] = {RealType(thePnt.X()) - myCenter[0],
                               RealType(thePnt.Y()) - myCenter[1]};
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
  }
}

template <typename RealType>
bool Bnd_B2<RealType>::Limit(const Bnd_B2<RealType>& theBox)
{
  bool           aResult(false);
  const RealType diffC[2] = {theBox.myCenter[0] - myCenter[0], theBox.myCenter[1] - myCenter[1]};
  const RealType sumH[2]  = {theBox.myHSize[0] + myHSize[0], theBox.myHSize[1] + myHSize[1]};

  if (!compareDist(sumH, diffC))
  {
    const RealType diffH[2] = {theBox.myHSize[0] - myHSize[0], theBox.myHSize[1] - myHSize[1]};
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
    aResult = true;
  }
  return aResult;
}

template <typename RealType>
Bnd_B2<RealType> Bnd_B2<RealType>::Transformed(const gp_Trsf2d& theTrsf) const
{
  Bnd_B2<RealType>  aResult;
  const gp_TrsfForm aForm     = theTrsf.Form();
  const double      aScale    = theTrsf.ScaleFactor();
  const double      aScaleAbs = std::abs(aScale);
  if (aForm == gp_Identity)
    aResult = *this;
  else if (aForm == gp_Translation || aForm == gp_PntMirror || aForm == gp_Scale)
  {
    aResult.myCenter[0] = (RealType)(myCenter[0] * aScale + theTrsf.TranslationPart().X());
    aResult.myCenter[1] = (RealType)(myCenter[1] * aScale + theTrsf.TranslationPart().Y());
    aResult.myHSize[0]  = (RealType)(myHSize[0] * aScaleAbs);
    aResult.myHSize[1]  = (RealType)(myHSize[1] * aScaleAbs);
  }
  else
  {
    gp_XY aCenter((double)myCenter[0], (double)myCenter[1]);
    theTrsf.Transforms(aCenter);
    aResult.myCenter[0] = (RealType)aCenter.X();
    aResult.myCenter[1] = (RealType)aCenter.Y();

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);
    aResult.myHSize[0] =
      (RealType)(aScaleAbs * (std::abs(aMat[0]) * myHSize[0] + std::abs(aMat[1]) * myHSize[1]));
    aResult.myHSize[1] =
      (RealType)(aScaleAbs * (std::abs(aMat[2]) * myHSize[0] + std::abs(aMat[3]) * myHSize[1]));
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B2<RealType>::IsOut(const gp_XY& theCenter,
                             const double theRadius,
                             const bool   isCircleHollow) const
{
  bool aResult(true);
  if (!isCircleHollow)
  {

    const double aDist[2] = {std::abs(theCenter.X() - double(myCenter[0])) - double(myHSize[0]),
                             std::abs(theCenter.Y() - double(myCenter[1])) - double(myHSize[1])};
    double       aD(0.);
    if (aDist[0] > 0.)
      aD = aDist[0] * aDist[0];
    if (aDist[1] > 0.)
      aD += aDist[1] * aDist[1];
    aResult = (aD > theRadius * theRadius);
  }
  else
  {
    const double aDistC[2] = {std::abs(theCenter.X() - double(myCenter[0])),
                              std::abs(theCenter.Y() - double(myCenter[1]))};

    double aDist[2] = {aDistC[0] - double(myHSize[0]), aDistC[1] - double(myHSize[1])};
    double aD(0.);
    if (aDist[0] > 0.)
      aD = aDist[0] * aDist[0];
    if (aDist[1] > 0.)
      aD += aDist[1] * aDist[1];
    if (aD < theRadius * theRadius)
    {

      aDist[0] = aDistC[0] + double(myHSize[0]);
      aDist[1] = aDistC[1] + double(myHSize[1]);
      if (aDist[0] * aDist[0] + aDist[1] * aDist[1] > theRadius * theRadius)
        aResult = false;
    }
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B2<RealType>::IsOut(const Bnd_B2<RealType>& theBox, const gp_Trsf2d& theTrsf) const
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
            > RealType(theBox.myHSize[1] * aScaleAbs) + myHSize[1]);
  }
  else
  {

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);

    gp_XY aCenter((double)theBox.myCenter[0], (double)theBox.myCenter[1]);
    theTrsf.Transforms(aCenter);
    const double aDist[2] = {aCenter.X() - (double)myCenter[0], aCenter.Y() - (double)myCenter[1]};
    const double aMatAbs[4] = {std::abs(aMat[0]),
                               std::abs(aMat[1]),
                               std::abs(aMat[2]),
                               std::abs(aMat[3])};
    if (std::abs(aDist[0])
          > (aScaleAbs * (aMatAbs[0] * theBox.myHSize[0] + aMatAbs[1] * theBox.myHSize[1])
             + (double)myHSize[0])
        || std::abs(aDist[1])
             > (aScaleAbs * (aMatAbs[2] * theBox.myHSize[0] + aMatAbs[3] * theBox.myHSize[1])
                + (double)myHSize[1]))
      aResult = true;

    else
    {

      if ((std::abs(aMat[0] * aDist[0] + aMat[2] * aDist[1])
           > theBox.myHSize[0] * aScaleAbs + (aMatAbs[0] * myHSize[0] + aMatAbs[2] * myHSize[1]))
          || (std::abs(aMat[1] * aDist[0] + aMat[3] * aDist[1])
              > theBox.myHSize[1] * aScaleAbs
                  + (aMatAbs[1] * myHSize[0] + aMatAbs[3] * myHSize[1])))
        aResult = true;
    }
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B2<RealType>::IsOut(const gp_Ax2d& theLine) const
{
  if (IsVoid())
    return true;

  const double aProd[3] = {
    theLine.Direction().XY()
      ^ (gp_XY(myCenter[0] - theLine.Location().X(), myCenter[1] - theLine.Location().Y())),
    theLine.Direction().X() * double(myHSize[1]),
    theLine.Direction().Y() * double(myHSize[0])};
  return (std::abs(aProd[0]) > (std::abs(aProd[1]) + std::abs(aProd[2])));
}

template <typename RealType>
bool Bnd_B2<RealType>::IsOut(const gp_XY& theP0, const gp_XY& theP1) const
{
  bool aResult(true);
  if (!IsVoid())
  {

    const gp_XY  aSegDelta(theP1 - theP0);
    const double aProd[3] = {aSegDelta ^ (gp_XY(myCenter[0], myCenter[1]) - theP0),
                             aSegDelta.X() * double(myHSize[1]),
                             aSegDelta.Y() * double(myHSize[0])};
    if (std::abs(aProd[0]) < (std::abs(aProd[1]) + std::abs(aProd[2])))
    {

      const gp_XY aHSeg(0.5 * aSegDelta.X(), 0.5 * aSegDelta.Y());
      const gp_XY aHSegAbs(std::abs(aHSeg.X()), std::abs(aHSeg.Y()));
      aResult = compareDistD(gp_XY((double)myHSize[0], (double)myHSize[1]) + aHSegAbs,
                             theP0 + aHSeg - gp_XY((double)myCenter[0], (double)myCenter[1]));
    }
  }
  return aResult;
}

template <typename RealType>
bool Bnd_B2<RealType>::IsIn(const Bnd_B2<RealType>& theBox, const gp_Trsf2d& theTrsf) const
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
            < RealType(theBox.myHSize[1] * aScaleAbs) - myHSize[1]);
  }
  else
  {

    const double* aMat = &theTrsf.HVectorialPart().Value(1, 1);
    gp_XY         aCenter((double)theBox.myCenter[0], (double)theBox.myCenter[1]);
    theTrsf.Transforms(aCenter);
    const double aDist[2] = {aCenter.X() - (double)myCenter[0], aCenter.Y() - (double)myCenter[1]};
    if ((std::abs(aMat[0] * aDist[0] + aMat[2] * aDist[1])
         < theBox.myHSize[0] * aScaleAbs
             - (std::abs(aMat[0]) * myHSize[0] + std::abs(aMat[2]) * myHSize[1]))
        && (std::abs(aMat[1] * aDist[0] + aMat[3] * aDist[1])
            < theBox.myHSize[1] * aScaleAbs
                - (std::abs(aMat[1]) * myHSize[0] + std::abs(aMat[3]) * myHSize[1])))
      aResult = true;
  }
  return aResult;
}

using Bnd_B2d = Bnd_B2<double>;

using Bnd_B2f = Bnd_B2<float>;
