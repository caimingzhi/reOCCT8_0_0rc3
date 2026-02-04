#pragma once


#include <AIS_Animation.hpp>
#include <AIS_InteractiveContext.hpp>

//! Animation defining object transformation.
class AIS_BaseAnimationObject : public AIS_Animation
{
  DEFINE_STANDARD_RTTIEXT(AIS_BaseAnimationObject, AIS_Animation)
protected:
  //! Constructor with initialization.
  //! @param[in] theAnimationName animation identifier
  //! @param[in] theContext       interactive context where object have been displayed
  //! @param[in] theObject        object to apply local transformation
  Standard_EXPORT AIS_BaseAnimationObject(const TCollection_AsciiString& theAnimationName,
                                          const occ::handle<AIS_InteractiveContext>& theContext,
                                          const occ::handle<AIS_InteractiveObject>&  theObject);

  //! Update the transformation.
  Standard_EXPORT void updateTrsf(const gp_Trsf& theTrsf);

private:
  //! Invalidate the viewer for proper update.
  Standard_EXPORT void invalidateViewer();

protected:
  occ::handle<AIS_InteractiveContext> myContext; //!< context where object is displayed
  occ::handle<AIS_InteractiveObject>  myObject;  //!< presentation object to set location
};

