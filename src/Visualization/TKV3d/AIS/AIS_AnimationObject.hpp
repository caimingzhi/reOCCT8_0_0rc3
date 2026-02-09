#pragma once

#include <AIS_BaseAnimationObject.hpp>
#include <gp_TrsfNLerp.hpp>

class AIS_AnimationObject : public AIS_BaseAnimationObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationObject, AIS_BaseAnimationObject)
public:
  Standard_EXPORT AIS_AnimationObject(const TCollection_AsciiString&             theAnimationName,
                                      const occ::handle<AIS_InteractiveContext>& theContext,
                                      const occ::handle<AIS_InteractiveObject>&  theObject,
                                      const gp_Trsf&                             theTrsfStart,
                                      const gp_Trsf&                             theTrsfEnd);

protected:
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

private:
  NCollection_Lerp<gp_Trsf> myTrsfLerp;
};
