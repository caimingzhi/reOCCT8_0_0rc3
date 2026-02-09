

#include <Geom_Curve.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Trsf.hpp>
#include <HelixGeom_BuilderHelix.hpp>
#include <HelixGeom_BuilderHelixCoil.hpp>
#include <NCollection_Sequence.hpp>

HelixGeom_BuilderHelix::HelixGeom_BuilderHelix()

  = default;

HelixGeom_BuilderHelix::~HelixGeom_BuilderHelix() = default;

void HelixGeom_BuilderHelix::SetPosition(const gp_Ax2& aAx2)
{
  myPosition = aAx2;
}

const gp_Ax2& HelixGeom_BuilderHelix::Position() const
{
  return myPosition;
}

void HelixGeom_BuilderHelix::Perform()
{
  myErrorStatus   = 0;
  myWarningStatus = 0;

  int                        iErr, aN, i, aNbC;
  double                     aTwoPI, dT, aT1x, aT2x, aTR;
  HelixGeom_BuilderHelixCoil aBHC;

  myCurves.Clear();
  myTolReached = -1.;
  aTwoPI       = 2. * M_PI;
  aBHC.SetTolerance(myTolerance);
  aBHC.SetApproxParameters(myCont, myMaxDegree, myMaxSeg);

  dT = myT2 - myT1;
  aN = (int)(dT / aTwoPI);
  if (!aN)
  {
    aBHC.SetCurveParameters(myT1, myT2, myPitch, myRStart, myTaperAngle, myIsClockWise);
    aBHC.Perform();
    iErr = aBHC.ErrorStatus();
    if (iErr)
    {
      myErrorStatus = 2;
      return;
    }
    const NCollection_Sequence<occ::handle<Geom_Curve>>& aSC = aBHC.Curves();
    const occ::handle<Geom_Curve>&                       aC  = aSC(1);
    myCurves.Append(aC);
    myTolReached = aBHC.ToleranceReached();
  }
  else
  {

    bool   bIsCylindrical;
    double aTolAngle;

    aTolAngle      = 1.e-4;
    bIsCylindrical = fabs(myTaperAngle) < aTolAngle;
    aT1x           = myT1;
    aT2x           = myT1 + aTwoPI;
    for (i = 1; i <= aN; ++i)
    {
      if (i > 1 && bIsCylindrical)
      {

        occ::handle<Geom_Curve> aCi;
        gp_Pnt                  aP1, aPi;

        const occ::handle<Geom_Curve>& aC1 = myCurves(1);
        aC1->D0(aC1->FirstParameter(), aP1);
        aPi.SetCoord(aP1.X(), aP1.Y(), aP1.Z() + (i - 1) * myPitch);
        aCi = occ::down_cast<Geom_Curve>(aC1->Translated(aP1, aPi));

        myCurves.Append(aCi);
        aT1x = aT2x;
        aT2x = aT1x + aTwoPI;

        continue;
      }

      aBHC.SetCurveParameters(aT1x, aT2x, myPitch, myRStart, myTaperAngle, myIsClockWise);

      aBHC.Perform();
      iErr = aBHC.ErrorStatus();
      if (iErr)
      {
        myErrorStatus = 2;
        return;
      }

      const NCollection_Sequence<occ::handle<Geom_Curve>>& aSC = aBHC.Curves();
      const occ::handle<Geom_Curve>&                       aC  = aSC(1);
      myCurves.Append(aC);
      aTR = aBHC.ToleranceReached();
      if (aTR > myTolReached)
      {
        myTolReached = aTR;
      }

      aT1x = aT2x;
      aT2x = aT1x + aTwoPI;
    }

    aT2x       = myT2;
    double eps = 1.e-7 * aTwoPI;
    if (fabs(aT2x - aT1x) > eps)
    {
      aBHC.SetCurveParameters(aT1x, aT2x, myPitch, myRStart, myTaperAngle, myIsClockWise);
      aBHC.Perform();
      iErr = aBHC.ErrorStatus();
      if (iErr)
      {
        myErrorStatus = 2;
        return;
      }

      const NCollection_Sequence<occ::handle<Geom_Curve>>& aSC = aBHC.Curves();
      const occ::handle<Geom_Curve>&                       aC  = aSC(1);
      myCurves.Append(aC);
      aTR = aBHC.ToleranceReached();
      if (aTR > myTolReached)
      {
        myTolReached = aTR;
      }
    }
  }

  gp_Trsf aTrsf;
  gp_Ax3  aAx3, aAx3x(myPosition);

  aTrsf.SetDisplacement(aAx3, aAx3x);

  aNbC = myCurves.Length();
  for (i = 1; i <= aNbC; ++i)
  {
    occ::handle<Geom_Curve>& aC = myCurves(i);
    aC->Transform(aTrsf);
  }
}
