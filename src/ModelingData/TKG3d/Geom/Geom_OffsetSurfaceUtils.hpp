#pragma once

#include <CSLib.hpp>
#include <CSLib_NormalStatus.hpp>
#include <Geom_BSplineSurface.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_LocalArray.hpp>
#include <Precision.hpp>
#include <NCollection_Array2.hpp>

#include <cmath>

namespace Geom_OffsetSurfaceUtils
{

  constexpr double THE_D1_MAGNITUDE_TOL = 1.e-9;

  struct OsculatingInfo
  {
    bool AlongU     = false;
    bool AlongV     = false;
    bool IsOpposite = false;

    double Sign() const { return ((AlongU || AlongV) && IsOpposite) ? -1.0 : 1.0; }

    bool HasOsculating() const { return AlongU || AlongV; }
  };

  inline bool IsInfiniteCoord(const gp_Vec& theVec)
  {
    return Precision::IsInfinite(theVec.X()) || Precision::IsInfinite(theVec.Y())
           || Precision::IsInfinite(theVec.Z());
  }

  inline bool IsSingular(const gp_Vec& theD1U,
                         const gp_Vec& theD1V,
                         double        theTol = THE_D1_MAGNITUDE_TOL)
  {

    gp_Vec aD1U(theD1U);
    gp_Vec aD1V(theD1V);
    double aD1UNorm2 = aD1U.SquareMagnitude();
    double aD1VNorm2 = aD1V.SquareMagnitude();
    if (aD1UNorm2 > 1.0)
      aD1U /= std::sqrt(aD1UNorm2);
    if (aD1VNorm2 > 1.0)
      aD1V /= std::sqrt(aD1VNorm2);

    gp_Vec aNorm = aD1U.Crossed(aD1V);
    return aNorm.SquareMagnitude() <= theTol * theTol;
  }

  inline bool ComputeNormal(const gp_Vec& theD1U,
                            const gp_Vec& theD1V,
                            gp_Vec&       theNormal,
                            double        theTol = THE_D1_MAGNITUDE_TOL)
  {

    gp_Vec aD1U(theD1U);
    gp_Vec aD1V(theD1V);
    double aD1UNorm2 = aD1U.SquareMagnitude();
    double aD1VNorm2 = aD1V.SquareMagnitude();
    if (aD1UNorm2 > 1.0)
      aD1U /= std::sqrt(aD1UNorm2);
    if (aD1VNorm2 > 1.0)
      aD1V /= std::sqrt(aD1VNorm2);

    theNormal = aD1U.Crossed(aD1V);
    if (theNormal.SquareMagnitude() <= theTol * theTol)
    {
      return false;
    }
    theNormal.Normalize();
    return true;
  }

  inline gp_Vec ComputeDNormalU(const gp_Vec& theD1U,
                                const gp_Vec& theD1V,
                                const gp_Vec& theD2U,
                                const gp_Vec& theD2UV,
                                const gp_Vec& theNormal)
  {
    double aScale = (theD1U ^ theD1V).Dot(theNormal);

    gp_Vec aN1U;
    aN1U.SetX(theD2U.Y() * theD1V.Z() + theD1U.Y() * theD2UV.Z() - theD2U.Z() * theD1V.Y()
              - theD1U.Z() * theD2UV.Y());
    aN1U.SetY(-(theD2U.X() * theD1V.Z() + theD1U.X() * theD2UV.Z() - theD2U.Z() * theD1V.X()
                - theD1U.Z() * theD2UV.X()));
    aN1U.SetZ(theD2U.X() * theD1V.Y() + theD1U.X() * theD2UV.Y() - theD2U.Y() * theD1V.X()
              - theD1U.Y() * theD2UV.X());
    double aScaleU = aN1U.Dot(theNormal);
    aN1U.Subtract(aScaleU * theNormal);
    aN1U /= aScale;

    return aN1U;
  }

  inline gp_Vec ComputeDNormalV(const gp_Vec& theD1U,
                                const gp_Vec& theD1V,
                                const gp_Vec& theD2V,
                                const gp_Vec& theD2UV,
                                const gp_Vec& theNormal)
  {
    double aScale = (theD1U ^ theD1V).Dot(theNormal);

    gp_Vec aN1V;
    aN1V.SetX(theD2UV.Y() * theD1V.Z() + theD2V.Z() * theD1U.Y() - theD2UV.Z() * theD1V.Y()
              - theD2V.Y() * theD1U.Z());
    aN1V.SetY(-(theD2UV.X() * theD1V.Z() + theD2V.Z() * theD1U.X() - theD2UV.Z() * theD1V.X()
                - theD2V.X() * theD1U.Z()));
    aN1V.SetZ(theD2UV.X() * theD1V.Y() + theD2V.Y() * theD1U.X() - theD2UV.Y() * theD1V.X()
              - theD2V.X() * theD1U.Y());
    double aScaleV = aN1V.Dot(theNormal);
    aN1V.Subtract(aScaleV * theNormal);
    aN1V /= aScale;

    return aN1V;
  }

  inline bool CalculateD0(gp_Pnt&       theValue,
                          const gp_Vec& theD1U,
                          const gp_Vec& theD1V,
                          double        theOffset,
                          double        theSign = 1.0)
  {
    gp_Vec aNorm;
    if (!ComputeNormal(theD1U, theD1V, aNorm))
    {
      return false;
    }
    theValue.SetXYZ(theValue.XYZ() + theOffset * theSign * aNorm.XYZ());
    return true;
  }

  inline bool CalculateD1(gp_Pnt&       theValue,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V,
                          const gp_Vec& theD2U,
                          const gp_Vec& theD2V,
                          const gp_Vec& theD2UV,
                          double        theOffset,
                          double        theSign = 1.0)
  {
    gp_Vec aNorm;
    if (!ComputeNormal(theD1U, theD1V, aNorm))
    {
      return false;
    }

    theValue.SetXYZ(theValue.XYZ() + theOffset * theSign * aNorm.XYZ());

    gp_Vec aN1U = ComputeDNormalU(theD1U, theD1V, theD2U, theD2UV, aNorm);
    gp_Vec aN1V = ComputeDNormalV(theD1U, theD1V, theD2V, theD2UV, aNorm);

    theD1U += theOffset * theSign * aN1U;
    theD1V += theOffset * theSign * aN1V;

    return true;
  }

  template <class BasisSurfType, class OscSurfType>
  void ComputeDerivatives(int                         theMaxOrder,
                          int                         theMinOrder,
                          double                      theU,
                          double                      theV,
                          const BasisSurfType&        theBasisSurf,
                          int                         theNU,
                          int                         theNV,
                          bool                        theAlongU,
                          bool                        theAlongV,
                          const OscSurfType&          theOscSurf,
                          NCollection_Array2<gp_Vec>& theDerNUV,
                          NCollection_Array2<gp_Vec>& theDerSurf)
  {
    gp_Pnt P;
    gp_Vec DL1U, DL1V, DL2U, DL2V, DL2UV, DL3U, DL3UUV, DL3UVV, DL3V;

    if (theAlongU || theAlongV)
    {
      theMaxOrder = 0;

      const int aDerSurfLSize = (theMaxOrder + theNU + 2) * (theMaxOrder + theNV + 2);
      NCollection_LocalArray<gp_Vec, 64> aDerSurfLBuffer(aDerSurfLSize);
      NCollection_Array2<gp_Vec>         DerSurfL(aDerSurfLBuffer[0],
                                          0,
                                          theMaxOrder + theNU + 1,
                                          0,
                                          theMaxOrder + theNV + 1);
      switch (theMinOrder)
      {
        case 1:
          theOscSurf->D1(theU, theV, P, DL1U, DL1V);
          DerSurfL.SetValue(1, 0, DL1U);
          DerSurfL.SetValue(0, 1, DL1V);
          break;
        case 2:
          theOscSurf->D2(theU, theV, P, DL1U, DL1V, DL2U, DL2V, DL2UV);
          DerSurfL.SetValue(1, 0, DL1U);
          DerSurfL.SetValue(0, 1, DL1V);
          DerSurfL.SetValue(1, 1, DL2UV);
          DerSurfL.SetValue(2, 0, DL2U);
          DerSurfL.SetValue(0, 2, DL2V);
          break;
        case 3:
          theOscSurf->D3(theU, theV, P, DL1U, DL1V, DL2U, DL2V, DL2UV, DL3U, DL3V, DL3UUV, DL3UVV);
          DerSurfL.SetValue(1, 0, DL1U);
          DerSurfL.SetValue(0, 1, DL1V);
          DerSurfL.SetValue(1, 1, DL2UV);
          DerSurfL.SetValue(2, 0, DL2U);
          DerSurfL.SetValue(0, 2, DL2V);
          DerSurfL.SetValue(3, 0, DL3U);
          DerSurfL.SetValue(2, 1, DL3UUV);
          DerSurfL.SetValue(1, 2, DL3UVV);
          DerSurfL.SetValue(0, 3, DL3V);
          break;
        default:
          break;
      }

      if (theNU <= theNV)
      {
        for (int i = 0; i <= theMaxOrder + 1 + theNU; i++)
          for (int j = i; j <= theMaxOrder + theNV + 1; j++)
            if (i + j > theMinOrder)
            {
              DerSurfL.SetValue(i, j, theOscSurf->DN(theU, theV, i, j));
              theDerSurf.SetValue(i, j, theBasisSurf->DN(theU, theV, i, j));
              if (i != j && j <= theNU + 1)
              {
                theDerSurf.SetValue(j, i, theBasisSurf->DN(theU, theV, j, i));
                DerSurfL.SetValue(j, i, theOscSurf->DN(theU, theV, j, i));
              }
            }
      }
      else
      {
        for (int j = 0; j <= theMaxOrder + 1 + theNV; j++)
          for (int i = j; i <= theMaxOrder + theNU + 1; i++)
            if (i + j > theMinOrder)
            {
              DerSurfL.SetValue(i, j, theOscSurf->DN(theU, theV, i, j));
              theDerSurf.SetValue(i, j, theBasisSurf->DN(theU, theV, i, j));
              if (i != j && i <= theNV + 1)
              {
                theDerSurf.SetValue(j, i, theBasisSurf->DN(theU, theV, j, i));
                DerSurfL.SetValue(j, i, theOscSurf->DN(theU, theV, j, i));
              }
            }
      }
      for (int i = 0; i <= theMaxOrder + theNU; i++)
        for (int j = 0; j <= theMaxOrder + theNV; j++)
        {
          if (theAlongU)
            theDerNUV.SetValue(i, j, CSLib::DNNUV(i, j, DerSurfL, theDerSurf));
          if (theAlongV)
            theDerNUV.SetValue(i, j, CSLib::DNNUV(i, j, theDerSurf, DerSurfL));
        }
    }
    else
    {
      for (int i = 0; i <= theMaxOrder + theNU + 1; i++)
      {
        for (int j = i; j <= theMaxOrder + theNV + 1; j++)
        {
          if (i + j > theMinOrder)
          {
            theDerSurf.SetValue(i, j, theBasisSurf->DN(theU, theV, i, j));
            if (i != j && j <= theDerSurf.UpperRow() && i <= theDerSurf.UpperCol())
            {
              theDerSurf.SetValue(j, i, theBasisSurf->DN(theU, theV, j, i));
            }
          }
        }
      }
      for (int i = 0; i <= theMaxOrder + theNU; i++)
        for (int j = 0; j <= theMaxOrder + theNV; j++)
          theDerNUV.SetValue(i, j, CSLib::DNNUV(i, j, theDerSurf));
    }
  }

  template <class BasisSurfType>
  bool ReplaceDerivative(double               theU,
                         double               theV,
                         double               theUMin,
                         double               theUMax,
                         double               theVMin,
                         double               theVMax,
                         gp_Vec&              theDU,
                         gp_Vec&              theDV,
                         double               theSquareTol,
                         const BasisSurfType& theBasisSurf)
  {
    bool isReplaceDU = theDU.SquareMagnitude() < theSquareTol;
    bool isReplaceDV = theDV.SquareMagnitude() < theSquareTol;
    bool isReplaced  = false;

    if (isReplaceDU != isReplaceDV)
    {

      double aStep;
      if (isReplaceDV)
      {
        aStep = Precision::Confusion() * theDU.Magnitude();
        if (aStep > theUMax - theUMin)
          aStep = (theUMax - theUMin) / 100.;
      }
      else
      {
        aStep = Precision::Confusion() * theDV.Magnitude();
        if (aStep > theVMax - theVMin)
          aStep = (theVMax - theVMin) / 100.;
      }

      gp_Pnt aP;
      gp_Vec aDU, aDV;

      for (double aStepSign = -1.0; aStepSign <= 1.0 && !isReplaced; aStepSign += 2.0)
      {
        double aU = theU;
        double aV = theV;

        if (isReplaceDV)
        {
          aU = theU + aStepSign * aStep;
          if (aU < theUMin || aU > theUMax)
            continue;
        }
        else
        {
          aV = theV + aStepSign * aStep;
          if (aV < theVMin || aV > theVMax)
            continue;
        }

        theBasisSurf->D1(aU, aV, aP, aDU, aDV);

        if (isReplaceDU && aDU.SquareMagnitude() > theSquareTol)
        {
          theDU      = aDU;
          isReplaced = true;
        }
        if (isReplaceDV && aDV.SquareMagnitude() > theSquareTol)
        {
          theDV      = aDV;
          isReplaced = true;
        }
      }
    }
    return isReplaced;
  }

  inline bool ShiftPoint(double        theUStart,
                         double        theVStart,
                         double&       theU,
                         double&       theV,
                         double        theUMin,
                         double        theUMax,
                         double        theVMin,
                         double        theVMax,
                         bool          theIsUPeriodic,
                         bool          theIsVPeriodic,
                         const gp_Vec& theD1U,
                         const gp_Vec& theD1V)
  {

    bool isUSingular = (theD1U.SquareMagnitude() < THE_D1_MAGNITUDE_TOL * THE_D1_MAGNITUDE_TOL);
    bool isVSingular = (theD1V.SquareMagnitude() < THE_D1_MAGNITUDE_TOL * THE_D1_MAGNITUDE_TOL);

    double aDirU =
      (theIsUPeriodic || (isUSingular && !isVSingular) ? 0.
                                                       : 0.5 * (theUMin + theUMax) - theUStart);
    double aDirV =
      (theIsVPeriodic || (isVSingular && !isUSingular) ? 0.
                                                       : 0.5 * (theVMin + theVMax) - theVStart);
    double aDist = std::sqrt(aDirU * aDirU + aDirV * aDirV);

    double aDU   = theU - theUStart;
    double aDV   = theV - theVStart;
    double aStep = std::max(2. * std::sqrt(aDU * aDU + aDV * aDV), Precision::PConfusion());
    if (aStep >= aDist)
    {
      return false;
    }

    aStep /= aDist;
    theU += aDirU * aStep;
    theV += aDirV * aStep;

    return true;
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD0(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  const gp_Vec&           theD1U,
                  const gp_Vec&           theD1V)
  {
    const double aUStart = theU;
    const double aVStart = theV;
    double       aUMin, aUMax, aVMin, aVMax;
    theBasisSurf->Bounds(aUMin, aUMax, aVMin, aVMax);
    const bool isUPer = theBasisSurf->IsUPeriodic();
    const bool isVPer = theBasisSurf->IsVPeriodic();

    gp_Vec aD1U             = theD1U;
    gp_Vec aD1V             = theD1V;
    bool   isFirstIteration = true;

    for (;;)
    {

      if (!isFirstIteration)
      {
        theBasisSurf->D1(theU, theV, theValue, aD1U, aD1V);
      }
      isFirstIteration = false;

      if (IsInfiniteCoord(aD1U) || IsInfiniteCoord(aD1V))
      {
        return false;
      }

      if (CalculateD0(theValue, aD1U, aD1V, theOffset))
      {
        return true;
      }

      constexpr int aMaxOrder = 3;

      OsculatingInfo                   aOscInfo;
      occ::handle<Geom_BSplineSurface> aOscSurf;
      if (theOscQuery)
      {
        aOscInfo.AlongU =
          theOscQuery->UOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
        aOscInfo.AlongV =
          theOscQuery->VOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
      }

      constexpr int                                aDerNUVSize  = (aMaxOrder + 1) * (aMaxOrder + 1);
      constexpr int                                aDerSurfSize = (aMaxOrder + 2) * (aMaxOrder + 2);
      NCollection_LocalArray<gp_Vec, aDerNUVSize>  aDerNUVBuffer(aDerNUVSize);
      NCollection_LocalArray<gp_Vec, aDerSurfSize> aDerSurfBuffer(aDerSurfSize);
      NCollection_Array2<gp_Vec> aDerNUV(aDerNUVBuffer[0], 0, aMaxOrder, 0, aMaxOrder);
      NCollection_Array2<gp_Vec> aDerSurf(aDerSurfBuffer[0], 0, aMaxOrder + 1, 0, aMaxOrder + 1);

      aDerSurf.SetValue(1, 0, aD1U);
      aDerSurf.SetValue(0, 1, aD1V);

      if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
      {
        ComputeDerivatives(aMaxOrder,
                           1,
                           theU,
                           theV,
                           theBasisSurf,
                           0,
                           0,
                           aOscInfo.AlongU,
                           aOscInfo.AlongV,
                           aOscSurf,
                           aDerNUV,
                           aDerSurf);
      }
      else
      {
        occ::handle<Geom_BSplineSurface> aDummy;
        ComputeDerivatives(aMaxOrder,
                           1,
                           theU,
                           theV,
                           theBasisSurf,
                           0,
                           0,
                           false,
                           false,
                           aDummy,
                           aDerNUV,
                           aDerSurf);
      }

      gp_Dir             aNormal;
      CSLib_NormalStatus aNStatus;
      int                OrderU, OrderV;
      CSLib::Normal(aMaxOrder,
                    aDerNUV,
                    THE_D1_MAGNITUDE_TOL,
                    theU,
                    theV,
                    aUMin,
                    aUMax,
                    aVMin,
                    aVMax,
                    aNStatus,
                    aNormal,
                    OrderU,
                    OrderV);

      if (aNStatus == CSLib_InfinityOfSolutions)
      {
        gp_Vec aNewDU = aD1U;
        gp_Vec aNewDV = aD1V;
        if (ReplaceDerivative(theU,
                              theV,
                              aUMin,
                              aUMax,
                              aVMin,
                              aVMax,
                              aNewDU,
                              aNewDV,
                              THE_D1_MAGNITUDE_TOL * THE_D1_MAGNITUDE_TOL,
                              theBasisSurf))
        {
          CSLib::Normal(aNewDU, aNewDV, THE_D1_MAGNITUDE_TOL, aNStatus, aNormal);
        }
      }

      if (aNStatus == CSLib_Defined)
      {
        theValue.SetXYZ(theValue.XYZ() + theOffset * aOscInfo.Sign() * aNormal.XYZ());
        return true;
      }

      if (!ShiftPoint(aUStart,
                      aVStart,
                      theU,
                      theV,
                      aUMin,
                      aUMax,
                      aVMin,
                      aVMax,
                      isUPer,
                      isVPer,
                      aD1U,
                      aD1V))
      {
        return false;
      }
    }
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD0(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue)
  {
    gp_Vec aD1U, aD1V;
    theBasisSurf->D1(theU, theV, theValue, aD1U, aD1V);
    return EvaluateD0(theU, theV, theBasisSurf, theOffset, theOscQuery, theValue, aD1U, aD1V);
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD1(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  gp_Vec&                 theD1U,
                  gp_Vec&                 theD1V,
                  const gp_Vec&           theD2U,
                  const gp_Vec&           theD2V,
                  const gp_Vec&           theD2UV)
  {
    const double aUStart = theU;
    const double aVStart = theV;
    double       aUMin, aUMax, aVMin, aVMax;
    theBasisSurf->Bounds(aUMin, aUMax, aVMin, aVMax);
    const bool isUPer = theBasisSurf->IsUPeriodic();
    const bool isVPer = theBasisSurf->IsVPeriodic();

    gp_Vec aD2U             = theD2U;
    gp_Vec aD2V             = theD2V;
    gp_Vec aD2UV            = theD2UV;
    bool   isFirstIteration = true;

    for (;;)
    {

      if (!isFirstIteration)
      {
        theBasisSurf->D2(theU, theV, theValue, theD1U, theD1V, aD2U, aD2V, aD2UV);
      }
      isFirstIteration = false;

      if (IsInfiniteCoord(theD1U) || IsInfiniteCoord(theD1V))
      {
        return false;
      }

      gp_Vec aD1U(theD1U);
      gp_Vec aD1V(theD1V);
      double aD1UNorm2 = aD1U.SquareMagnitude();
      double aD1VNorm2 = aD1V.SquareMagnitude();
      if (aD1UNorm2 > 1.0)
        aD1U /= std::sqrt(aD1UNorm2);
      if (aD1VNorm2 > 1.0)
        aD1V /= std::sqrt(aD1VNorm2);

      bool      isSingular = false;
      const int aMaxOrder  = 3;
      gp_Vec    aNorm      = aD1U.Crossed(aD1V);

      OsculatingInfo                   aOscInfo;
      occ::handle<Geom_BSplineSurface> aOscSurf;
      if (aNorm.SquareMagnitude() <= THE_D1_MAGNITUDE_TOL * THE_D1_MAGNITUDE_TOL)
      {
        if (theOscQuery)
        {
          aOscInfo.AlongU =
            theOscQuery->UOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
          aOscInfo.AlongV =
            theOscQuery->VOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
        }
        isSingular = true;
      }

      const double aSign = aOscInfo.Sign();

      if (!isSingular)
      {
        aNorm.Normalize();
        theValue.SetXYZ(theValue.XYZ() + theOffset * aSign * aNorm.XYZ());

        gp_Vec       aN0(aNorm.XYZ()), aN1U, aN1V;
        const double aScale = (theD1U ^ theD1V).Dot(aN0);
        aN1U.SetX(aD2U.Y() * theD1V.Z() + theD1U.Y() * aD2UV.Z() - aD2U.Z() * theD1V.Y()
                  - theD1U.Z() * aD2UV.Y());
        aN1U.SetY((aD2U.X() * theD1V.Z() + theD1U.X() * aD2UV.Z() - aD2U.Z() * theD1V.X()
                   - theD1U.Z() * aD2UV.X())
                  * -1.0);
        aN1U.SetZ(aD2U.X() * theD1V.Y() + theD1U.X() * aD2UV.Y() - aD2U.Y() * theD1V.X()
                  - theD1U.Y() * aD2UV.X());
        const double aScaleU = aN1U.Dot(aN0);
        aN1U.Subtract(aScaleU * aN0);
        aN1U /= aScale;

        aN1V.SetX(aD2UV.Y() * theD1V.Z() + aD2V.Z() * theD1U.Y() - aD2UV.Z() * theD1V.Y()
                  - aD2V.Y() * theD1U.Z());
        aN1V.SetY((aD2UV.X() * theD1V.Z() + aD2V.Z() * theD1U.X() - aD2UV.Z() * theD1V.X()
                   - aD2V.X() * theD1U.Z())
                  * -1.0);
        aN1V.SetZ(aD2UV.X() * theD1V.Y() + aD2V.Y() * theD1U.X() - aD2UV.Y() * theD1V.X()
                  - aD2V.X() * theD1U.Y());
        const double aScaleV = aN1V.Dot(aN0);
        aN1V.Subtract(aScaleV * aN0);
        aN1V /= aScale;

        theD1U += theOffset * aSign * aN1U;
        theD1V += theOffset * aSign * aN1V;

        return true;
      }

      constexpr int                                aDerNUVSize  = (aMaxOrder + 2) * (aMaxOrder + 2);
      constexpr int                                aDerSurfSize = (aMaxOrder + 3) * (aMaxOrder + 3);
      NCollection_LocalArray<gp_Vec, aDerNUVSize>  aDerNUVBuffer(aDerNUVSize);
      NCollection_LocalArray<gp_Vec, aDerSurfSize> aDerSurfBuffer(aDerSurfSize);
      NCollection_Array2<gp_Vec> aDerNUV(aDerNUVBuffer[0], 0, aMaxOrder + 1, 0, aMaxOrder + 1);
      NCollection_Array2<gp_Vec> aDerSurf(aDerSurfBuffer[0], 0, aMaxOrder + 2, 0, aMaxOrder + 2);

      aDerSurf.SetValue(1, 0, theD1U);
      aDerSurf.SetValue(0, 1, theD1V);
      aDerSurf.SetValue(1, 1, aD2UV);
      aDerSurf.SetValue(2, 0, aD2U);
      aDerSurf.SetValue(0, 2, aD2V);

      if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
      {
        ComputeDerivatives(aMaxOrder,
                           2,
                           theU,
                           theV,
                           theBasisSurf,
                           1,
                           1,
                           aOscInfo.AlongU,
                           aOscInfo.AlongV,
                           aOscSurf,
                           aDerNUV,
                           aDerSurf);
      }
      else
      {
        occ::handle<Geom_BSplineSurface> aDummy;
        ComputeDerivatives(aMaxOrder,
                           2,
                           theU,
                           theV,
                           theBasisSurf,
                           1,
                           1,
                           false,
                           false,
                           aDummy,
                           aDerNUV,
                           aDerSurf);
      }

      gp_Dir             aNormal;
      CSLib_NormalStatus aNStatus;
      int                aOrderU, aOrderV;
      CSLib::Normal(aMaxOrder,
                    aDerNUV,
                    THE_D1_MAGNITUDE_TOL,
                    theU,
                    theV,
                    aUMin,
                    aUMax,
                    aVMin,
                    aVMax,
                    aNStatus,
                    aNormal,
                    aOrderU,
                    aOrderV);

      if (aNStatus == CSLib_InfinityOfSolutions)
      {
        gp_Vec aNewDU = theD1U;
        gp_Vec aNewDV = theD1V;
        if (ReplaceDerivative(theU,
                              theV,
                              aUMin,
                              aUMax,
                              aVMin,
                              aVMax,
                              aNewDU,
                              aNewDV,
                              THE_D1_MAGNITUDE_TOL * THE_D1_MAGNITUDE_TOL,
                              theBasisSurf))
        {

          aDerSurf.SetValue(1, 0, aNewDU);
          aDerSurf.SetValue(0, 1, aNewDV);
          if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
          {
            ComputeDerivatives(aMaxOrder,
                               2,
                               theU,
                               theV,
                               theBasisSurf,
                               1,
                               1,
                               aOscInfo.AlongU,
                               aOscInfo.AlongV,
                               aOscSurf,
                               aDerNUV,
                               aDerSurf);
          }
          else
          {
            occ::handle<Geom_BSplineSurface> aDummy;
            ComputeDerivatives(aMaxOrder,
                               2,
                               theU,
                               theV,
                               theBasisSurf,
                               1,
                               1,
                               false,
                               false,
                               aDummy,
                               aDerNUV,
                               aDerSurf);
          }
          CSLib::Normal(aMaxOrder,
                        aDerNUV,
                        THE_D1_MAGNITUDE_TOL,
                        theU,
                        theV,
                        aUMin,
                        aUMax,
                        aVMin,
                        aVMax,
                        aNStatus,
                        aNormal,
                        aOrderU,
                        aOrderV);
        }
      }

      if (aNStatus == CSLib_Defined)
      {

        theValue.SetXYZ(theValue.XYZ() + theOffset * aSign * aNormal.XYZ());

        theD1U = CSLib::DNNormal(1, 0, aDerNUV, aOrderU, aOrderV);
        theD1V = CSLib::DNNormal(0, 1, aDerNUV, aOrderU, aOrderV);

        theD1U.Multiply(theOffset * aSign);
        theD1U.Add(aDerSurf(1, 0));
        theD1V.Multiply(theOffset * aSign);
        theD1V.Add(aDerSurf(0, 1));
        return true;
      }

      if (!ShiftPoint(aUStart,
                      aVStart,
                      theU,
                      theV,
                      aUMin,
                      aUMax,
                      aVMin,
                      aVMax,
                      isUPer,
                      isVPer,
                      theD1U,
                      theD1V))
      {
        return false;
      }
    }
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD1(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  gp_Vec&                 theD1U,
                  gp_Vec&                 theD1V)
  {
    gp_Vec aD2U, aD2V, aD2UV;
    theBasisSurf->D2(theU, theV, theValue, theD1U, theD1V, aD2U, aD2V, aD2UV);
    return EvaluateD1(theU,
                      theV,
                      theBasisSurf,
                      theOffset,
                      theOscQuery,
                      theValue,
                      theD1U,
                      theD1V,
                      aD2U,
                      aD2V,
                      aD2UV);
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD2(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  gp_Vec&                 theD1U,
                  gp_Vec&                 theD1V,
                  gp_Vec&                 theD2U,
                  gp_Vec&                 theD2V,
                  gp_Vec&                 theD2UV,
                  const gp_Vec&           theD3U,
                  const gp_Vec&           theD3V,
                  const gp_Vec&           theD3UUV,
                  const gp_Vec&           theD3UVV)
  {
    const double aUStart = theU;
    const double aVStart = theV;
    double       aUMin, aUMax, aVMin, aVMax;
    theBasisSurf->Bounds(aUMin, aUMax, aVMin, aVMax);
    const bool isUPer = theBasisSurf->IsUPeriodic();
    const bool isVPer = theBasisSurf->IsVPeriodic();

    gp_Vec aD3U             = theD3U;
    gp_Vec aD3V             = theD3V;
    gp_Vec aD3UUV           = theD3UUV;
    gp_Vec aD3UVV           = theD3UVV;
    bool   isFirstIteration = true;

    for (;;)
    {

      if (!isFirstIteration)
      {
        theBasisSurf->D3(theU,
                         theV,
                         theValue,
                         theD1U,
                         theD1V,
                         theD2U,
                         theD2V,
                         theD2UV,
                         aD3U,
                         aD3V,
                         aD3UUV,
                         aD3UVV);
      }
      isFirstIteration = false;

      if (IsInfiniteCoord(theD1U) || IsInfiniteCoord(theD1V))
      {
        return false;
      }

      gp_Dir             aNormal;
      CSLib_NormalStatus aNStatus;
      CSLib::Normal(theD1U, theD1V, THE_D1_MAGNITUDE_TOL, aNStatus, aNormal);

      const int aMaxOrder = (aNStatus == CSLib_Defined) ? 0 : 3;

      OsculatingInfo                   aOscInfo;
      occ::handle<Geom_BSplineSurface> aOscSurf;
      if ((aNStatus != CSLib_Defined) && theOscQuery)
      {
        aOscInfo.AlongU =
          theOscQuery->UOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
        aOscInfo.AlongV =
          theOscQuery->VOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
      }

      const int                          aDerNUVSize  = (aMaxOrder + 3) * (aMaxOrder + 3);
      const int                          aDerSurfSize = (aMaxOrder + 4) * (aMaxOrder + 4);
      NCollection_LocalArray<gp_Vec, 36> aDerNUVBuffer(aDerNUVSize);
      NCollection_LocalArray<gp_Vec, 49> aDerSurfBuffer(aDerSurfSize);
      NCollection_Array2<gp_Vec> aDerNUV(aDerNUVBuffer[0], 0, aMaxOrder + 2, 0, aMaxOrder + 2);
      NCollection_Array2<gp_Vec> aDerSurf(aDerSurfBuffer[0], 0, aMaxOrder + 3, 0, aMaxOrder + 3);

      aDerSurf.SetValue(1, 0, theD1U);
      aDerSurf.SetValue(0, 1, theD1V);
      aDerSurf.SetValue(1, 1, theD2UV);
      aDerSurf.SetValue(2, 0, theD2U);
      aDerSurf.SetValue(0, 2, theD2V);
      aDerSurf.SetValue(3, 0, aD3U);
      aDerSurf.SetValue(2, 1, aD3UUV);
      aDerSurf.SetValue(1, 2, aD3UVV);
      aDerSurf.SetValue(0, 3, aD3V);

      if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
      {
        ComputeDerivatives(aMaxOrder,
                           3,
                           theU,
                           theV,
                           theBasisSurf,
                           2,
                           2,
                           aOscInfo.AlongU,
                           aOscInfo.AlongV,
                           aOscSurf,
                           aDerNUV,
                           aDerSurf);
      }
      else
      {
        occ::handle<Geom_BSplineSurface> aDummy;
        ComputeDerivatives(aMaxOrder,
                           3,
                           theU,
                           theV,
                           theBasisSurf,
                           2,
                           2,
                           false,
                           false,
                           aDummy,
                           aDerNUV,
                           aDerSurf);
      }

      int aOrderU, aOrderV;
      CSLib::Normal(aMaxOrder,
                    aDerNUV,
                    THE_D1_MAGNITUDE_TOL,
                    theU,
                    theV,
                    aUMin,
                    aUMax,
                    aVMin,
                    aVMax,
                    aNStatus,
                    aNormal,
                    aOrderU,
                    aOrderV);

      if (aNStatus == CSLib_Defined)
      {
        const double aSign = theOffset * aOscInfo.Sign();

        theValue.SetXYZ(theValue.XYZ() + aSign * aNormal.XYZ());

        theD1U =
          aDerSurf(1, 0).Added(CSLib::DNNormal(1, 0, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD1V =
          aDerSurf(0, 1).Added(CSLib::DNNormal(0, 1, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));

        theD2U  = theBasisSurf->DN(theU, theV, 2, 0);
        theD2V  = theBasisSurf->DN(theU, theV, 0, 2);
        theD2UV = theBasisSurf->DN(theU, theV, 1, 1);

        theD2U.Add(CSLib::DNNormal(2, 0, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD2V.Add(CSLib::DNNormal(0, 2, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD2UV.Add(CSLib::DNNormal(1, 1, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        return true;
      }

      if (!ShiftPoint(aUStart,
                      aVStart,
                      theU,
                      theV,
                      aUMin,
                      aUMax,
                      aVMin,
                      aVMax,
                      isUPer,
                      isVPer,
                      theD1U,
                      theD1V))
      {
        return false;
      }
    }
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD2(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  gp_Vec&                 theD1U,
                  gp_Vec&                 theD1V,
                  gp_Vec&                 theD2U,
                  gp_Vec&                 theD2V,
                  gp_Vec&                 theD2UV)
  {
    gp_Vec aD3U, aD3V, aD3UUV, aD3UVV;
    theBasisSurf->D3(theU,
                     theV,
                     theValue,
                     theD1U,
                     theD1V,
                     theD2U,
                     theD2V,
                     theD2UV,
                     aD3U,
                     aD3V,
                     aD3UUV,
                     aD3UVV);
    return EvaluateD2(theU,
                      theV,
                      theBasisSurf,
                      theOffset,
                      theOscQuery,
                      theValue,
                      theD1U,
                      theD1V,
                      theD2U,
                      theD2V,
                      theD2UV,
                      aD3U,
                      aD3V,
                      aD3UUV,
                      aD3UVV);
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateD3(double                  theU,
                  double                  theV,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Pnt&                 theValue,
                  gp_Vec&                 theD1U,
                  gp_Vec&                 theD1V,
                  gp_Vec&                 theD2U,
                  gp_Vec&                 theD2V,
                  gp_Vec&                 theD2UV,
                  gp_Vec&                 theD3U,
                  gp_Vec&                 theD3V,
                  gp_Vec&                 theD3UUV,
                  gp_Vec&                 theD3UVV)
  {
    const double aUStart = theU;
    const double aVStart = theV;
    double       aUMin, aUMax, aVMin, aVMax;
    theBasisSurf->Bounds(aUMin, aUMax, aVMin, aVMax);
    const bool isUPer = theBasisSurf->IsUPeriodic();
    const bool isVPer = theBasisSurf->IsVPeriodic();

    for (;;)
    {
      theBasisSurf->D3(theU,
                       theV,
                       theValue,
                       theD1U,
                       theD1V,
                       theD2U,
                       theD2V,
                       theD2UV,
                       theD3U,
                       theD3V,
                       theD3UUV,
                       theD3UVV);

      if (IsInfiniteCoord(theD1U) || IsInfiniteCoord(theD1V))
      {
        return false;
      }

      gp_Dir             aNormal;
      CSLib_NormalStatus aNStatus;
      CSLib::Normal(theD1U, theD1V, THE_D1_MAGNITUDE_TOL, aNStatus, aNormal);

      const int aMaxOrder = (aNStatus == CSLib_Defined) ? 0 : 3;

      OsculatingInfo                   aOscInfo;
      occ::handle<Geom_BSplineSurface> aOscSurf;
      if ((aNStatus != CSLib_Defined) && theOscQuery)
      {
        aOscInfo.AlongU =
          theOscQuery->UOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
        aOscInfo.AlongV =
          theOscQuery->VOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
      }

      const int                          aDerNUVSize  = (aMaxOrder + 4) * (aMaxOrder + 4);
      const int                          aDerSurfSize = (aMaxOrder + 5) * (aMaxOrder + 5);
      NCollection_LocalArray<gp_Vec, 49> aDerNUVBuffer(aDerNUVSize);
      NCollection_LocalArray<gp_Vec, 64> aDerSurfBuffer(aDerSurfSize);
      NCollection_Array2<gp_Vec> aDerNUV(aDerNUVBuffer[0], 0, aMaxOrder + 3, 0, aMaxOrder + 3);
      NCollection_Array2<gp_Vec> aDerSurf(aDerSurfBuffer[0], 0, aMaxOrder + 4, 0, aMaxOrder + 4);

      aDerSurf.SetValue(1, 0, theD1U);
      aDerSurf.SetValue(0, 1, theD1V);
      aDerSurf.SetValue(1, 1, theD2UV);
      aDerSurf.SetValue(2, 0, theD2U);
      aDerSurf.SetValue(0, 2, theD2V);
      aDerSurf.SetValue(3, 0, theD3U);
      aDerSurf.SetValue(2, 1, theD3UUV);
      aDerSurf.SetValue(1, 2, theD3UVV);
      aDerSurf.SetValue(0, 3, theD3V);

      if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
      {
        ComputeDerivatives(aMaxOrder,
                           3,
                           theU,
                           theV,
                           theBasisSurf,
                           3,
                           3,
                           aOscInfo.AlongU,
                           aOscInfo.AlongV,
                           aOscSurf,
                           aDerNUV,
                           aDerSurf);
      }
      else
      {
        occ::handle<Geom_BSplineSurface> aDummy;
        ComputeDerivatives(aMaxOrder,
                           3,
                           theU,
                           theV,
                           theBasisSurf,
                           3,
                           3,
                           false,
                           false,
                           aDummy,
                           aDerNUV,
                           aDerSurf);
      }

      int aOrderU, aOrderV;
      CSLib::Normal(aMaxOrder,
                    aDerNUV,
                    THE_D1_MAGNITUDE_TOL,
                    theU,
                    theV,
                    aUMin,
                    aUMax,
                    aVMin,
                    aVMax,
                    aNStatus,
                    aNormal,
                    aOrderU,
                    aOrderV);

      if (aNStatus == CSLib_Defined)
      {
        const double aSign = theOffset * aOscInfo.Sign();

        theValue.SetXYZ(theValue.XYZ() + aSign * aNormal.XYZ());

        theD1U =
          aDerSurf(1, 0).Added(CSLib::DNNormal(1, 0, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD1V =
          aDerSurf(0, 1).Added(CSLib::DNNormal(0, 1, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));

        theD2U   = theBasisSurf->DN(theU, theV, 2, 0);
        theD2V   = theBasisSurf->DN(theU, theV, 0, 2);
        theD2UV  = theBasisSurf->DN(theU, theV, 1, 1);
        theD3U   = theBasisSurf->DN(theU, theV, 3, 0);
        theD3V   = theBasisSurf->DN(theU, theV, 0, 3);
        theD3UUV = theBasisSurf->DN(theU, theV, 2, 1);
        theD3UVV = theBasisSurf->DN(theU, theV, 1, 2);

        theD2U.Add(CSLib::DNNormal(2, 0, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD2V.Add(CSLib::DNNormal(0, 2, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD2UV.Add(CSLib::DNNormal(1, 1, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD3U.Add(CSLib::DNNormal(3, 0, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD3V.Add(CSLib::DNNormal(0, 3, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD3UUV.Add(CSLib::DNNormal(2, 1, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        theD3UVV.Add(CSLib::DNNormal(1, 2, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        return true;
      }

      if (!ShiftPoint(aUStart,
                      aVStart,
                      theU,
                      theV,
                      aUMin,
                      aUMax,
                      aVMin,
                      aVMax,
                      isUPer,
                      isVPer,
                      theD1U,
                      theD1V))
      {
        return false;
      }
    }
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateDN(double                  theU,
                  double                  theV,
                  int                     theNu,
                  int                     theNv,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Vec&                 theResult,
                  const gp_Vec&           theD1U,
                  const gp_Vec&           theD1V)
  {
    const double aUStart = theU;
    const double aVStart = theV;
    double       aUMin, aUMax, aVMin, aVMax;
    theBasisSurf->Bounds(aUMin, aUMax, aVMin, aVMax);
    const bool isUPer = theBasisSurf->IsUPeriodic();
    const bool isVPer = theBasisSurf->IsVPeriodic();

    gp_Pnt aP;
    gp_Vec aD1U             = theD1U;
    gp_Vec aD1V             = theD1V;
    bool   isFirstIteration = true;

    for (;;)
    {

      if (!isFirstIteration)
      {
        theBasisSurf->D1(theU, theV, aP, aD1U, aD1V);
      }
      isFirstIteration = false;

      if (IsInfiniteCoord(aD1U) || IsInfiniteCoord(aD1V))
      {
        return false;
      }

      gp_Dir             aNormal;
      CSLib_NormalStatus aNStatus;
      CSLib::Normal(aD1U, aD1V, THE_D1_MAGNITUDE_TOL, aNStatus, aNormal);

      const int aMaxOrder = (aNStatus == CSLib_Defined) ? 0 : 3;
      int       aOrderU, aOrderV;

      const int aDerNUVSize  = (aMaxOrder + theNu + 1) * (aMaxOrder + theNv + 1);
      const int aDerSurfSize = (aMaxOrder + theNu + 2) * (aMaxOrder + theNv + 2);
      NCollection_LocalArray<gp_Vec, 49> aDerNUVBuffer(aDerNUVSize);
      NCollection_LocalArray<gp_Vec, 64> aDerSurfBuffer(aDerSurfSize);
      NCollection_Array2<gp_Vec>         aDerNUV(aDerNUVBuffer[0],
                                         0,
                                         aMaxOrder + theNu,
                                         0,
                                         aMaxOrder + theNv);
      NCollection_Array2<gp_Vec>         aDerSurf(aDerSurfBuffer[0],
                                          0,
                                          aMaxOrder + theNu + 1,
                                          0,
                                          aMaxOrder + theNv + 1);

      aDerSurf.SetValue(1, 0, aD1U);
      aDerSurf.SetValue(0, 1, aD1V);

      OsculatingInfo                   aOscInfo;
      occ::handle<Geom_BSplineSurface> aOscSurf;
      if ((aNStatus != CSLib_Defined) && theOscQuery)
      {
        aOscInfo.AlongU =
          theOscQuery->UOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
        aOscInfo.AlongV =
          theOscQuery->VOsculatingSurface(theU, theV, aOscInfo.IsOpposite, aOscSurf);
      }

      if (aOscInfo.HasOsculating() && !aOscSurf.IsNull())
      {
        ComputeDerivatives(aMaxOrder,
                           1,
                           theU,
                           theV,
                           theBasisSurf,
                           theNu,
                           theNv,
                           aOscInfo.AlongU,
                           aOscInfo.AlongV,
                           aOscSurf,
                           aDerNUV,
                           aDerSurf);
      }
      else
      {
        occ::handle<Geom_BSplineSurface> aDummy;
        ComputeDerivatives(aMaxOrder,
                           1,
                           theU,
                           theV,
                           theBasisSurf,
                           theNu,
                           theNv,
                           false,
                           false,
                           aDummy,
                           aDerNUV,
                           aDerSurf);
      }

      CSLib::Normal(aMaxOrder,
                    aDerNUV,
                    THE_D1_MAGNITUDE_TOL,
                    theU,
                    theV,
                    aUMin,
                    aUMax,
                    aVMin,
                    aVMax,
                    aNStatus,
                    aNormal,
                    aOrderU,
                    aOrderV);

      if (aNStatus == CSLib_Defined)
      {
        const double aSign = theOffset * aOscInfo.Sign();

        theResult = theBasisSurf->DN(theU, theV, theNu, theNv);
        theResult.Add(CSLib::DNNormal(theNu, theNv, aDerNUV, aOrderU, aOrderV).Multiplied(aSign));
        return true;
      }

      if (!ShiftPoint(aUStart,
                      aVStart,
                      theU,
                      theV,
                      aUMin,
                      aUMax,
                      aVMin,
                      aVMax,
                      isUPer,
                      isVPer,
                      aD1U,
                      aD1V))
      {
        return false;
      }
    }
  }

  template <class BasisSurfType, class OscSurfQueryType>
  bool EvaluateDN(double                  theU,
                  double                  theV,
                  int                     theNu,
                  int                     theNv,
                  const BasisSurfType&    theBasisSurf,
                  double                  theOffset,
                  const OscSurfQueryType& theOscQuery,
                  gp_Vec&                 theResult)
  {
    gp_Pnt aP;
    gp_Vec aD1U, aD1V;
    theBasisSurf->D1(theU, theV, aP, aD1U, aD1V);
    return EvaluateDN(theU,
                      theV,
                      theNu,
                      theNv,
                      theBasisSurf,
                      theOffset,
                      theOscQuery,
                      theResult,
                      aD1U,
                      aD1V);
  }

} // namespace Geom_OffsetSurfaceUtils
