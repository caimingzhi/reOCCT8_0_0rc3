#include <AIS_AnimationObject.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_AnimationObject, AIS_BaseAnimationObject)

AIS_AnimationObject::AIS_AnimationObject(const TCollection_AsciiString& theAnimationName,
                                         const occ::handle<AIS_InteractiveContext>& theContext,
                                         const occ::handle<AIS_InteractiveObject>&  theObject,
                                         const gp_Trsf&                             theTrsfStart,
                                         const gp_Trsf&                             theTrsfEnd)
    : AIS_BaseAnimationObject(theAnimationName, theContext, theObject),
      myTrsfLerp(theTrsfStart, theTrsfEnd)
{
}

void AIS_AnimationObject::update(const AIS_AnimationProgress& theProgress)
{
  if (myObject.IsNull())
  {
    return;
  }

  gp_Trsf aTrsf;
  myTrsfLerp.Interpolate(theProgress.LocalNormalized, aTrsf);
  updateTrsf(aTrsf);
}
