#pragma once

#include <AIS_BaseAnimationObject.hpp>
#include <gp_TrsfNLerp.hpp>

//! Animation defining object transformation.
class AIS_AnimationObject : public AIS_BaseAnimationObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationObject, AIS_BaseAnimationObject)
public:
  //! Constructor with initialization.
  //! Note that start/end transformations specify exactly local transformation of the object,
  //! not the transformation to be applied to existing local transformation.
  //! @param[in] theAnimationName animation identifier
  //! @param[in] theContext       interactive context where object have been displayed
  //! @param[in] theObject        object to apply local transformation
  //! @param[in] theTrsfStart     local transformation at the start of animation (e.g.
  //! theObject->LocalTransformation())
  //! @param[in] theTrsfEnd       local transformation at the end   of animation
  Standard_EXPORT AIS_AnimationObject(const TCollection_AsciiString&             theAnimationName,
                                      const occ::handle<AIS_InteractiveContext>& theContext,
                                      const occ::handle<AIS_InteractiveObject>&  theObject,
                                      const gp_Trsf&                             theTrsfStart,
                                      const gp_Trsf&                             theTrsfEnd);

protected:
  //! Update the progress.
  Standard_EXPORT void update(const AIS_AnimationProgress& theProgress) override;

private:
  NCollection_Lerp<gp_Trsf> myTrsfLerp; //!< interpolation tool
};
