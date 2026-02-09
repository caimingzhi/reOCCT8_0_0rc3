

#include <Graphic3d_TransformPersScaledAbove.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TransformPersScaledAbove, Graphic3d_TransformPers)

Graphic3d_TransformPersScaledAbove::Graphic3d_TransformPersScaledAbove(const double  theScale,
                                                                       const gp_Pnt& thePnt)
    : Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, thePnt),
      myScale(theScale)
{
}

double Graphic3d_TransformPersScaledAbove::persistentScale(
  const occ::handle<Graphic3d_Camera>& theCamera,
  const int                            theViewportWidth,
  const int                            theViewportHeight) const
{
  double aScale = base_type::persistentScale(theCamera, theViewportWidth, theViewportHeight);
  if (aScale < myScale)
  {

    return myScale;
  }
  return aScale;
}
