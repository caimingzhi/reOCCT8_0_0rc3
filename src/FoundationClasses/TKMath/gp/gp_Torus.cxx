

#include <gp_Torus.hpp>

#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Standard_DimensionError.hpp>

void gp_Torus::Coefficients(NCollection_Array1<double>& theCoef) const
{

  const int aLowIndex = theCoef.Lower();
  Standard_DimensionError_Raise_if(theCoef.Length() < 35,
                                   "gp_Torus::theCoefficients(): Dimension mismatch");

  gp_Trsf aTr;
  aTr.SetTransformation(pos);
  const double aT11 = aTr.Value(1, 1);
  const double aT12 = aTr.Value(1, 2);
  const double aT13 = aTr.Value(1, 3);
  const double aT14 = aTr.Value(1, 4);
  const double aT21 = aTr.Value(2, 1);
  const double aT22 = aTr.Value(2, 2);
  const double aT23 = aTr.Value(2, 3);
  const double aT24 = aTr.Value(2, 4);
  const double aT31 = aTr.Value(3, 1);
  const double aT32 = aTr.Value(3, 2);
  const double aT33 = aTr.Value(3, 3);
  const double aT34 = aTr.Value(3, 4);

  const double aTcol1sq    = aT11 * aT11 + aT21 * aT21 + aT31 * aT31;
  const double aTcol2sq    = aT12 * aT12 + aT22 * aT22 + aT32 * aT32;
  const double aTcol3sq    = aT13 * aT13 + aT23 * aT23 + aT33 * aT33;
  const double aTcol4sq    = aT14 * aT14 + aT24 * aT24 + aT34 * aT34;
  const double aTcol1Tcol2 = aT11 * aT12 + aT21 * aT22 + aT31 * aT32;
  const double aTcol1Tcol3 = aT11 * aT13 + aT21 * aT23 + aT31 * aT33;
  const double aTcol2Tcol3 = aT12 * aT13 + aT22 * aT23 + aT32 * aT33;
  const double aTcol1Tcol4 = aT11 * aT14 + aT21 * aT24 + aT31 * aT34;
  const double aTcol2Tcol4 = aT12 * aT14 + aT22 * aT24 + aT32 * aT34;
  const double aTcol3Tcol4 = aT13 * aT14 + aT23 * aT24 + aT33 * aT34;

  const double aSumRadius = (majorRadius * majorRadius + minorRadius * minorRadius);
  const double aSubRadius = (majorRadius * majorRadius - minorRadius * minorRadius);

  theCoef(aLowIndex)      = aTcol1sq * aTcol1sq;
  theCoef(aLowIndex + 1)  = aTcol2sq * aTcol2sq;
  theCoef(aLowIndex + 2)  = aTcol3sq * aTcol3sq;
  theCoef(aLowIndex + 3)  = 4.0 * aTcol1sq * aTcol1Tcol2;
  theCoef(aLowIndex + 4)  = 4.0 * aTcol1sq * aTcol1Tcol3;
  theCoef(aLowIndex + 5)  = 4.0 * aTcol2sq * aTcol1Tcol2;
  theCoef(aLowIndex + 6)  = 4.0 * aTcol2sq * aTcol2Tcol3;
  theCoef(aLowIndex + 7)  = 4.0 * aTcol3sq * aTcol1Tcol3;
  theCoef(aLowIndex + 8)  = 4.0 * aTcol3sq * aTcol2Tcol3;
  theCoef(aLowIndex + 9)  = 2.0 * (aTcol1sq * aTcol2sq + 2.0 * aTcol1Tcol2 * aTcol1Tcol2);
  theCoef(aLowIndex + 10) = 2.0 * (aTcol1sq * aTcol3sq + 2.0 * aTcol1Tcol3 * aTcol1Tcol3);
  theCoef(aLowIndex + 11) = 2.0 * (aTcol2sq * aTcol3sq + 2.0 * aTcol2Tcol3 * aTcol2Tcol3);
  theCoef(aLowIndex + 12) = 4.0 * (aTcol1sq * aTcol2Tcol3 + 2.0 * aTcol1Tcol2 * aTcol1Tcol3);
  theCoef(aLowIndex + 13) = 4.0 * (aTcol2sq * aTcol1Tcol3 + 2.0 * aTcol1Tcol2 * aTcol2Tcol3);
  theCoef(aLowIndex + 14) = 4.0 * (aTcol3sq * aTcol1Tcol2 + 2.0 * aTcol1Tcol3 * aTcol2Tcol3);

  theCoef(aLowIndex + 15) = 4.0 * aTcol1sq * aTcol1Tcol4;
  theCoef(aLowIndex + 16) = 4.0 * aTcol2sq * aTcol2Tcol4;
  theCoef(aLowIndex + 17) = 4.0 * aTcol3sq * aTcol3Tcol4;
  theCoef(aLowIndex + 18) = 4.0 * (aTcol1sq * aTcol2Tcol4 + 2.0 * aTcol1Tcol4 * aTcol1Tcol2);
  theCoef(aLowIndex + 19) = 4.0 * (aTcol1sq * aTcol3Tcol4 + 2.0 * aTcol1Tcol4 * aTcol1Tcol3);
  theCoef(aLowIndex + 20) = 4.0 * (aTcol2sq * aTcol1Tcol4 + 2.0 * aTcol2Tcol4 * aTcol1Tcol2);
  theCoef(aLowIndex + 21) = 4.0 * (aTcol2sq * aTcol3Tcol4 + 2.0 * aTcol2Tcol4 * aTcol2Tcol3);
  theCoef(aLowIndex + 22) = 4.0 * (aTcol3sq * aTcol1Tcol4 + 2.0 * aTcol3Tcol4 * aTcol1Tcol3);
  theCoef(aLowIndex + 23) = 4.0 * (aTcol3sq * aTcol2Tcol4 + 2.0 * aTcol3Tcol4 * aTcol2Tcol3);
  theCoef(aLowIndex + 24) =
    8.0 * (aTcol1Tcol2 * aTcol3Tcol4 + aTcol2Tcol3 * aTcol1Tcol4 + aTcol2Tcol4 * aTcol1Tcol3);

  theCoef(aLowIndex + 25) = 2.0
                            * (aSubRadius * aT31 * aT31 - aSumRadius * (aT11 * aT11 + aT21 * aT21)
                               + aTcol4sq * aTcol1sq + 2.0 * aTcol1Tcol4 * aTcol1Tcol4);
  theCoef(aLowIndex + 26) = 2.0
                            * (aSubRadius * aT32 * aT32 - aSumRadius * (aT12 * aT12 + aT22 * aT22)
                               + aTcol4sq * aTcol2sq + 2.0 * aTcol2Tcol4 * aTcol2Tcol4);
  theCoef(aLowIndex + 27) = 2.0
                            * (aSubRadius * aT33 * aT33 - aSumRadius * (aT13 * aT13 + aT23 * aT23)
                               + aTcol4sq * aTcol3sq + 2.0 * aTcol3Tcol4 * aTcol3Tcol4);
  theCoef(aLowIndex + 28) = 4.0
                            * (aSubRadius * aT31 * aT32 - aSumRadius * (aT11 * aT12 + aT21 * aT22)
                               + aTcol4sq * aTcol1Tcol2 + 2.0 * aTcol1Tcol4 * aTcol2Tcol4);
  theCoef(aLowIndex + 29) = 4.0
                            * (aSubRadius * aT31 * aT33 - aSumRadius * (aT11 * aT13 + aT21 * aT23)
                               + aTcol4sq * aTcol1Tcol3 + 2.0 * aTcol1Tcol4 * aTcol3Tcol4);
  theCoef(aLowIndex + 30) = 4.0
                            * (aSubRadius * aT32 * aT33 - aSumRadius * (aT12 * aT13 + aT22 * aT23)
                               + aTcol4sq * aTcol2Tcol3 + 2.0 * aTcol2Tcol4 * aTcol3Tcol4);

  theCoef(aLowIndex + 31) = 4.0
                            * (aTcol4sq * aTcol1Tcol4 + aSubRadius * aT31 * aT34
                               - aSumRadius * (aT11 * aT14 + aT21 * aT24));
  theCoef(aLowIndex + 32) = 4.0
                            * (aTcol4sq * aTcol2Tcol4 + aSubRadius * aT32 * aT34
                               - aSumRadius * (aT12 * aT14 + aT22 * aT24));
  theCoef(aLowIndex + 33) = 4.0
                            * (aTcol4sq * aTcol3Tcol4 + aSubRadius * aT33 * aT34
                               - aSumRadius * (aT13 * aT14 + aT23 * aT24));

  theCoef(aLowIndex + 34) = 2.0 * aSubRadius * aT34 * aT34
                            - 2.0 * aSumRadius * (aT14 * aT14 + aT24 * aT24) + aTcol4sq * aTcol4sq
                            + aSubRadius * aSubRadius;
}

void gp_Torus::Mirror(const gp_Pnt& P) noexcept
{
  pos.Mirror(P);
}

gp_Torus gp_Torus::Mirrored(const gp_Pnt& P) const noexcept
{
  gp_Torus C = *this;
  C.pos.Mirror(P);
  return C;
}

void gp_Torus::Mirror(const gp_Ax1& A1) noexcept
{
  pos.Mirror(A1);
}

gp_Torus gp_Torus::Mirrored(const gp_Ax1& A1) const noexcept
{
  gp_Torus C = *this;
  C.pos.Mirror(A1);
  return C;
}

void gp_Torus::Mirror(const gp_Ax2& A2) noexcept
{
  pos.Mirror(A2);
}

gp_Torus gp_Torus::Mirrored(const gp_Ax2& A2) const noexcept
{
  gp_Torus C = *this;
  C.pos.Mirror(A2);
  return C;
}
