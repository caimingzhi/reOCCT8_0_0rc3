#include <IntCurveSurface_IntersectionPoint.hpp>

IntCurveSurface_IntersectionPoint::IntCurveSurface_IntersectionPoint()
    : myUSurf(0.0),
      myVSurf(0.0),
      myUCurv(0.0)
{
}

IntCurveSurface_IntersectionPoint::IntCurveSurface_IntersectionPoint(
  const gp_Pnt&                           P,
  const double                            USurf,
  const double                            VSurf,
  const double                            UCurv,
  const IntCurveSurface_TransitionOnCurve TrOnCurv)
    : myP(P),
      myUSurf(USurf),
      myVSurf(VSurf),
      myUCurv(UCurv),
      myTrOnCurv(TrOnCurv)
{
}

void IntCurveSurface_IntersectionPoint::SetValues(const gp_Pnt&                           P,
                                                  const double                            USurf,
                                                  const double                            VSurf,
                                                  const double                            UCurv,
                                                  const IntCurveSurface_TransitionOnCurve TrOnCurv)
{
  myP        = P;
  myUSurf    = USurf;
  myVSurf    = VSurf;
  myUCurv    = UCurv;
  myTrOnCurv = TrOnCurv;
}

void IntCurveSurface_IntersectionPoint::Values(gp_Pnt&                            P,
                                               double&                            USurf,
                                               double&                            VSurf,
                                               double&                            UCurv,
                                               IntCurveSurface_TransitionOnCurve& TrOnCurv) const
{
  P        = myP;
  USurf    = myUSurf;
  VSurf    = myVSurf;
  UCurv    = myUCurv;
  TrOnCurv = myTrOnCurv;
}

void IntCurveSurface_IntersectionPoint::Dump() const
{
  std::cout << "IntersectionPoint: P(" << myP.X() << "," << myP.Y() << "," << myP.Z() << ")"
            << std::endl;
  std::cout << "                 : USurf(" << myUSurf << ")  VSurf(" << myVSurf << ")   UCurve("
            << myUCurv << ")" << std::endl;
  std::cout << "                 : TransitionOnSurf ";

  switch (myTrOnCurv)
  {
    case IntCurveSurface_Tangent:
      std::cout << " Tangent ";
      break;
    case IntCurveSurface_In:
      std::cout << " In ";
      break;
    case IntCurveSurface_Out:
      std::cout << " Out ";
      break;

    default:
      std::cout << " XXXXX ";
  }
  std::cout << std::endl;
}
