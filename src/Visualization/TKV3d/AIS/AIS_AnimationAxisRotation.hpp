#pragma once

#include <AIS_BaseAnimationObject.hpp>
#include <gp_TrsfNLerp.hpp>

class AIS_AnimationAxisRotation : public AIS_BaseAnimationObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationAxisRotation, AIS_BaseAnimationObject)
public:
  Standard_EXPORT AIS_AnimationAxisRotation(const TCollection_AsciiString& theAnimationName,
                                            const occ::handle<AIS_InteractiveContext>& theContext,
                                            const occ::handle<AIS_InteractiveObject>&  theObject,
                                            const gp_Ax1&                              theAxis,
                                            const double theAngleStart,
                                            const double theAngleEnd);

protected:
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

private:
  gp_Ax1 myRotAxis;
  double myAngleStart;
  double myAngleEnd;
};
