

#include <Geom_BSplineCurve.hpp>
#include <HelixGeom_BuilderHelixCoil.hpp>
#include <HelixGeom_HelixCurve.hpp>
#include <HelixGeom_Tools.hpp>

HelixGeom_BuilderHelixCoil::HelixGeom_BuilderHelixCoil()

{
  myT1          = 0.;
  myT2          = 2. * M_PI;
  myPitch       = 1.;
  myRStart      = 1.;
  myTaperAngle  = 0.;
  myIsClockWise = true;
}

HelixGeom_BuilderHelixCoil::~HelixGeom_BuilderHelixCoil() = default;

void HelixGeom_BuilderHelixCoil::Perform()
{
  myErrorStatus   = 0;
  myWarningStatus = 0;

  int                               iErr;
  HelixGeom_HelixCurve              aAdaptor;
  occ::handle<HelixGeom_HelixCurve> aHAdaptor;
  occ::handle<Geom_BSplineCurve>    aBC;

  myCurves.Clear();

  aAdaptor.Load(myT1, myT2, myPitch, myRStart, myTaperAngle, myIsClockWise);
  aHAdaptor = new HelixGeom_HelixCurve(aAdaptor);

  iErr = HelixGeom_Tools::ApprCurve3D(aHAdaptor,
                                      myTolerance,
                                      myCont,
                                      myMaxSeg,
                                      myMaxDegree,
                                      aBC,
                                      myTolReached);
  if (iErr)
  {
    myErrorStatus = 2;
  }
  else
  {
    myCurves.Append(aBC);
  }
}
