

#include <Geom2dConvert_PPoint.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <Precision.hpp>

Geom2dConvert_PPoint::Geom2dConvert_PPoint(const double             theParameter,
                                           const Adaptor2d_Curve2d& theAdaptor)
    : myParameter(theParameter)
{
  theAdaptor.D1(theParameter, myPoint, myD1);
}

bool Geom2dConvert_PPoint::operator==(const Geom2dConvert_PPoint& theOther) const
{
  return (fabs(myParameter - theOther.Parameter()) <= Precision::PConfusion());
}

bool Geom2dConvert_PPoint::operator!=(const Geom2dConvert_PPoint& theOther) const
{
  return (fabs(myParameter - theOther.Parameter()) > Precision::PConfusion());
}
