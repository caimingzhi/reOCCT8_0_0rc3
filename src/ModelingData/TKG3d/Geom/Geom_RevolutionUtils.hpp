#pragma once

#include <gp_Ax1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>

namespace Geom_RevolutionUtils
{

  inline void CalculateD0(const gp_Pnt& theCurvePt,
                          const double  theU,
                          const gp_Ax1& theAxis,
                          gp_Pnt&       theP)
  {
    theP = theCurvePt;
    gp_Trsf aRotation;
    aRotation.SetRotation(theAxis, theU);
    theP.Transform(aRotation);
  }

  inline void CalculateD1(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const double  theU,
                          const gp_Ax1& theAxis,
                          gp_Pnt&       theP,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V)
  {
    theP = theCurvePt;

    gp_XYZ aCQ = theCurvePt.XYZ() - theAxis.Location().XYZ();
    theD1U     = gp_Vec(theAxis.Direction().XYZ().Crossed(aCQ));

    if (theD1U.SquareMagnitude() < Precision::SquareConfusion())
    {
      theD1U.SetCoord(0.0, 0.0, 0.0);
    }

    gp_Trsf aRotation;
    aRotation.SetRotation(theAxis, theU);
    theP.Transform(aRotation);
    theD1U.Transform(aRotation);
    theD1V = theCurveD1;
    theD1V.Transform(aRotation);
  }

  inline void CalculateD2(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const gp_Vec& theCurveD2,
                          const double  theU,
                          const gp_Ax1& theAxis,
                          gp_Pnt&       theP,
                          gp_Vec&       theD1U,
                          gp_Vec&       theD1V,
                          gp_Vec&       theD2U,
                          gp_Vec&       theD2V,
                          gp_Vec&       theD2UV)
  {
    theP = theCurvePt;

    gp_XYZ        aCQ  = theCurvePt.XYZ() - theAxis.Location().XYZ();
    const gp_XYZ& aDir = theAxis.Direction().XYZ();
    theD1U             = gp_Vec(aDir.Crossed(aCQ));

    if (theD1U.SquareMagnitude() < Precision::SquareConfusion())
    {
      theD1U.SetCoord(0.0, 0.0, 0.0);
    }
    theD2U  = gp_Vec(aDir.Dot(aCQ) * aDir - aCQ);
    theD2UV = gp_Vec(aDir.Crossed(theCurveD1.XYZ()));

    gp_Trsf aRotation;
    aRotation.SetRotation(theAxis, theU);
    theP.Transform(aRotation);
    theD1U.Transform(aRotation);
    theD1V = theCurveD1;
    theD1V.Transform(aRotation);
    theD2U.Transform(aRotation);
    theD2V = theCurveD2;
    theD2V.Transform(aRotation);
    theD2UV.Transform(aRotation);
  }

  inline void CalculateD3(const gp_Pnt& theCurvePt,
                          const gp_Vec& theCurveD1,
                          const gp_Vec& theCurveD2,
                          const gp_Vec& theCurveD3,
                          const double  theU,
                          const gp_Ax1& theAxis,
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
    theP = theCurvePt;

    gp_XYZ        aCQ  = theCurvePt.XYZ() - theAxis.Location().XYZ();
    const gp_XYZ& aDir = theAxis.Direction().XYZ();
    theD1U             = gp_Vec(aDir.Crossed(aCQ));

    if (theD1U.SquareMagnitude() < Precision::SquareConfusion())
    {
      theD1U.SetCoord(0.0, 0.0, 0.0);
    }
    theD2U   = gp_Vec(aDir.Dot(aCQ) * aDir - aCQ);
    theD2UV  = gp_Vec(aDir.Crossed(theCurveD1.XYZ()));
    theD3U   = -theD1U;
    theD3UUV = gp_Vec(aDir.Dot(theCurveD1.XYZ()) * aDir - theCurveD1.XYZ());
    theD3UVV = gp_Vec(aDir.Crossed(theCurveD2.XYZ()));

    gp_Trsf aRotation;
    aRotation.SetRotation(theAxis, theU);
    theP.Transform(aRotation);
    theD1U.Transform(aRotation);
    theD1V = theCurveD1;
    theD1V.Transform(aRotation);
    theD2U.Transform(aRotation);
    theD2V = theCurveD2;
    theD2V.Transform(aRotation);
    theD2UV.Transform(aRotation);
    theD3U.Transform(aRotation);
    theD3V = theCurveD3;
    theD3V.Transform(aRotation);
    theD3UUV.Transform(aRotation);
    theD3UVV.Transform(aRotation);
  }

  inline gp_Vec CalculateDN(const gp_Vec& theCurvePtOrDN,
                            const double  theU,
                            const gp_Ax1& theAxis,
                            const int     theDerU,
                            const int     theDerV)
  {

    (void)theDerV;

    gp_Trsf aRotation;
    aRotation.SetRotation(theAxis, theU);

    gp_Vec aResult;
    if (theDerU == 0)
    {

      aResult = theCurvePtOrDN;
    }
    else
    {

      const gp_XYZ& aDir = theAxis.Direction().XYZ();
      if (theDerU % 4 == 1)
      {
        aResult = gp_Vec(aDir.Crossed(theCurvePtOrDN.XYZ()));
      }
      else if (theDerU % 4 == 2)
      {
        aResult = gp_Vec(aDir.Dot(theCurvePtOrDN.XYZ()) * aDir - theCurvePtOrDN.XYZ());
      }
      else if (theDerU % 4 == 3)
      {
        aResult = gp_Vec(aDir.Crossed(theCurvePtOrDN.XYZ())) * (-1.0);
      }
      else
      {
        aResult = gp_Vec(theCurvePtOrDN.XYZ() - aDir.Dot(theCurvePtOrDN.XYZ()) * aDir);
      }
    }

    aResult.Transform(aRotation);
    return aResult;
  }

  template <typename CurveType>
  inline void D0(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_Ax1&    theAxis,
                 gp_Pnt&          theP)
  {
    gp_Pnt aCurvePt;
    theBasis.D0(theV, aCurvePt);
    CalculateD0(aCurvePt, theU, theAxis, theP);
  }

  template <typename CurveType>
  inline void D1(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_Ax1&    theAxis,
                 gp_Pnt&          theP,
                 gp_Vec&          theD1U,
                 gp_Vec&          theD1V)
  {
    gp_Pnt aCurvePt;
    gp_Vec aCurveD1;
    theBasis.D1(theV, aCurvePt, aCurveD1);
    CalculateD1(aCurvePt, aCurveD1, theU, theAxis, theP, theD1U, theD1V);
  }

  template <typename CurveType>
  inline void D2(const double     theU,
                 const double     theV,
                 const CurveType& theBasis,
                 const gp_Ax1&    theAxis,
                 gp_Pnt&          theP,
                 gp_Vec&          theD1U,
                 gp_Vec&          theD1V,
                 gp_Vec&          theD2U,
                 gp_Vec&          theD2V,
                 gp_Vec&          theD2UV)
  {
    gp_Pnt aCurvePt;
    gp_Vec aCurveD1, aCurveD2;
    theBasis.D2(theV, aCurvePt, aCurveD1, aCurveD2);
    CalculateD2(aCurvePt,
                aCurveD1,
                aCurveD2,
                theU,
                theAxis,
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
                 const gp_Ax1&    theAxis,
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
    theBasis.D3(theV, aCurvePt, aCurveD1, aCurveD2, aCurveD3);
    CalculateD3(aCurvePt,
                aCurveD1,
                aCurveD2,
                aCurveD3,
                theU,
                theAxis,
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
                   const double     theV,
                   const CurveType& theBasis,
                   const gp_Ax1&    theAxis,
                   const int        theDerU,
                   const int        theDerV)
  {
    gp_Vec aCurvePtOrDN;
    if (theDerU == 0)
    {
      aCurvePtOrDN = theBasis.DN(theV, theDerV);
    }
    else if (theDerV == 0)
    {
      gp_Pnt aP;
      theBasis.D0(theV, aP);
      aCurvePtOrDN = gp_Vec(aP.XYZ() - theAxis.Location().XYZ());
    }
    else
    {
      aCurvePtOrDN = theBasis.DN(theV, theDerV);
    }

    return CalculateDN(aCurvePtOrDN, theU, theAxis, theDerU, theDerV);
  }

} // namespace Geom_RevolutionUtils
