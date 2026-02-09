

#include <AIS_AnimationAxisRotation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_AnimationAxisRotation, AIS_BaseAnimationObject)

AIS_AnimationAxisRotation::AIS_AnimationAxisRotation(
  const TCollection_AsciiString&             theAnimationName,
  const occ::handle<AIS_InteractiveContext>& theContext,
  const occ::handle<AIS_InteractiveObject>&  theObject,
  const gp_Ax1&                              theAxis,
  const double                               theAngleStart,
  const double                               theAngleEnd)
    : AIS_BaseAnimationObject(theAnimationName, theContext, theObject),
      myRotAxis(theAxis),
      myAngleStart(theAngleStart),
      myAngleEnd(theAngleEnd)
{
}

void AIS_AnimationAxisRotation::update(const AIS_AnimationProgress& theProgress)
{
  if (myObject.IsNull())
  {
    return;
  }

  gp_Trsf aTrsf;
  double  aCurrentAngle =
    (1.0 - theProgress.LocalNormalized) * myAngleStart + theProgress.LocalNormalized * myAngleEnd;
  aTrsf.SetRotation(myRotAxis, aCurrentAngle);
  updateTrsf(aTrsf);
}
