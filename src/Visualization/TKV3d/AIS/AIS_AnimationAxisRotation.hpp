#pragma once

#include <AIS_BaseAnimationObject.hpp>
#include <gp_TrsfNLerp.hpp>

//! Animation defining object transformation.
class AIS_AnimationAxisRotation : public AIS_BaseAnimationObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationAxisRotation, AIS_BaseAnimationObject)
public:
  //! Constructor with initialization.
  //! @param[in] theAnimationName animation identifier
  //! @param[in] theContext       interactive context where object have been displayed
  //! @param[in] theObject        object to apply rotation
  //! @param[in] theAxis          rotation axis
  //! @param[in] theAngleStart    rotation angle at the start of animation
  //! @param[in] theAngleEnd      rotation angle at the end   of animation
  Standard_EXPORT AIS_AnimationAxisRotation(const TCollection_AsciiString& theAnimationName,
                                            const occ::handle<AIS_InteractiveContext>& theContext,
                                            const occ::handle<AIS_InteractiveObject>&  theObject,
                                            const gp_Ax1&                              theAxis,
                                            const double theAngleStart,
                                            const double theAngleEnd);

protected:
  //! Update the progress.
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

private:
  gp_Ax1 myRotAxis;    //!< rotation axis
  double myAngleStart; //!< start angle for rotation
  double myAngleEnd;   //!< end angle for rotation
};
