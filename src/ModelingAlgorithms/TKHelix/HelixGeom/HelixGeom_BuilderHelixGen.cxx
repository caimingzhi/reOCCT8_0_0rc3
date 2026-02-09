

#include <HelixGeom_BuilderHelixGen.hpp>

#include <cmath>

HelixGeom_BuilderHelixGen::HelixGeom_BuilderHelixGen()
    : myT1(0.0),
      myT2(2.0 * M_PI),
      myPitch(1.0),
      myRStart(1.0),
      myTaperAngle(0.0),
      myIsClockWise(true)
{
}

HelixGeom_BuilderHelixGen::~HelixGeom_BuilderHelixGen() = default;

void HelixGeom_BuilderHelixGen::SetCurveParameters(const double aT1,
                                                   const double aT2,
                                                   const double aPitch,
                                                   const double aRStart,
                                                   const double aTaperAngle,
                                                   const bool   aIsCW)
{

  myT1          = aT1;
  myT2          = aT2;
  myPitch       = aPitch;
  myRStart      = aRStart;
  myTaperAngle  = aTaperAngle;
  myIsClockWise = aIsCW;
}

void HelixGeom_BuilderHelixGen::CurveParameters(double& aT1,
                                                double& aT2,
                                                double& aPitch,
                                                double& aRStart,
                                                double& aTaperAngle,
                                                bool&   aIsClockWise) const
{
  aT1          = myT1;
  aT2          = myT2;
  aPitch       = myPitch;
  aRStart      = myRStart;
  aTaperAngle  = myTaperAngle;
  aIsClockWise = myIsClockWise;
}
