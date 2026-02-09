#pragma once

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>

namespace Geom_ExtrusionUtils
{

  inline void CalculateD0(const gp_Pnt& theCurvePt,
                          const double  theV,
                          const gp_XYZ& theDir,
                          gp_Pnt&       theP)
  {
    theP.SetXYZ(theCurvePt.XYZ() + theV * theDir);
  }

  inline void CalculateD1(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const double  theV,
                          const gp_XYZ& theDir,
                          gp_Pnt&       theP,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V)
  {
    theP.SetXYZ(theCurvePt.XYZ() + theV * theDir);
    theD1U = theCurveD1;
    theD1V.SetXYZ(theDir);
  }

  inline void CalculateD2(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const gp_Vec& theCurveD2,
                          const double  theV,
                          const gp_XYZ& theDir,
                          gp_Pnt&       theP,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V,
                          gp_Vec&       theD2U,
                          gp_Vec&       theD2V,
                          gp_Vec&       theD2UV)
  {
    theP.SetXYZ(theCurvePt.XYZ() + theV * theDir);
    theD1U = theCurveD1;
    theD1V.SetXYZ(theDir);
    theD2U = theCurveD2;
    theD2V.SetCoord(0.0, 0.0, 0.0);
    theD2UV.SetCoord(0.0, 0.0, 0.0);
  }

  inline void CalculateD3(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const gp_Vec& theCurveD2,
                          const gp_Vec& theCurveD3,
                          const double  theV,
                          const gp_XYZ& theDir,
                          gp_Pnt&       theP,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V,
                          gp_Vec&       theD2U,
                          gp_Vec&       theD2V,
                          gp_Vec&       theD2UV,
                          gp_Vec&       theD3U,
                          gp_Vec&       theD3V,
                          gp_Vec&       theD3UUV,
                          gp_Vec&       theD3UVV)
  {
    theP.SetXYZ(theCurvePt.XYZ() + theV * theDir);
    theD1U = theCurveD1;
    theD1V.SetXYZ(theDir);
    theD2U = theCurveD2;
    theD2V.SetCoord(0.0, 0.0, 0.0);
    theD2UV.SetCoord(0.0, 0.0, 0.0);
    theD3U = theCurveD3;
    theD3V.SetCoord(0.0, 0.0, 0.0);
    theD3UUV.SetCoord(0.0, 0.0, 0.0);
    theD3UVV.SetCoord(0.0, 0.0, 0.0);
  }

  inline gp_Vec CalculateDN(const gp_Vec& theCurveDN,
                            const gp_XYZ& theDir,
                            const int     theDerU,
                            const int     theDerV)
  {
    if (theDerV == 0)
      return theCurveDN;
    else if (theDerU == 0 && theDerV == 1)
      return gp_Vec(theDir);
    return gp_Vec(0.0, 0.0, 0.0);
  }

  template <typename CurveType>
  inline void D0(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_XYZ&    theDir,
                 gp_Pnt&          theP)
  {
    gp_Pnt aCurvePt;
    theBasis.D0(theU, aCurvePt);
    CalculateD0(aCurvePt, theV, theDir, theP);
  }

  template <typename CurveType>
  inline void D1(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_XYZ&    theDir,
                 gp_Pnt&          theP,
                 gp_Vec&          theD1U,
                 gp_Vec&          theD1V)
  {
    gp_Pnt aCurvePt;
    gp_Vec aCurveD1;
    theBasis.D1(theU, aCurvePt, aCurveD1);
    CalculateD1(aCurvePt, aCurveD1, theV, theDir, theP, theD1U, theD1V);
  }

  template <typename CurveType>
  inline void D2(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_XYZ&    theDir,
                 gp_Pnt&          theP,
                 gp_Vec&          theD1U,
                 gp_Vec&          theD1V,
                 gp_Vec&          theD2U,
                 gp_Vec&          theD2V,
                 gp_Vec&          theD2UV)
  {
    gp_Pnt aCurvePt;
    gp_Vec aCurveD1, aCurveD2;
    theBasis.D2(theU, aCurvePt, aCurveD1, aCurveD2);
    CalculateD2(aCurvePt,
                aCurveD1,
                aCurveD2,
                theV,
                theDir,
                theP,
                theD1U,
                theD1V,
                theD2U,
                theD2V,
                theD2UV);
  }

  template <typename CurveType>
  inline void D3(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_XYZ&    theDir,
                 gp_Pnt&          theP,
                 gp_Vec&          theD1U,
                 gp_Vec&          theD1V,
                 gp_Vec&          theD2U,
                 gp_Vec&          theD2V,
                 gp_Vec&          theD2UV,
                 gp_Vec&          theD3U,
                 gp_Vec&          theD3V,
                 gp_Vec&          theD3UUV,
                 gp_Vec&          theD3UVV)
  {
    gp_Pnt aCurvePt;
    gp_Vec aCurveD1, aCurveD2, aCurveD3;
    theBasis.D3(theU, aCurvePt, aCurveD1, aCurveD2, aCurveD3);
    CalculateD3(aCurvePt,
                aCurveD1,
                aCurveD2,
                aCurveD3,
                theV,
                theDir,
                theP,
                theD1U,
                theD1V,
                theD2U,
                theD2V,
                theD2UV,
                theD3U,
                theD3V,
                theD3UUV,
                theD3UVV);
  }

  template <typename CurveType>
  inline gp_Vec DN(const double     theU,
                   const CurveType& theBasis,
                   const gp_XYZ&    theDir,
                   const int        theDerU,
                   const int        theDerV)
  {
    gp_Vec aCurveDN = (theDerV == 0) ? theBasis.DN(theU, theDerU) : gp_Vec();
    return CalculateDN(aCurveDN, theDir, theDerU, theDerV);
  }

} // namespace Geom_ExtrusionUtils
