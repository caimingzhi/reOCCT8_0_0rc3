#pragma once

#include <AIS_Animation.hpp>
#include <AIS_InteractiveContext.hpp>

class AIS_BaseAnimationObject : public AIS_Animation
{
  DEFINE_STANDARD_RTTIEXT(AIS_BaseAnimationObject, AIS_Animation)
protected:
  Standard_EXPORT AIS_BaseAnimationObject(const TCollection_AsciiString& theAnimationName,
                                          const occ::handle<AIS_InteractiveContext>& theContext,
                                          const occ::handle<AIS_InteractiveObject>&  theObject);

  Standard_EXPORT void updateTrsf(const gp_Trsf& theTrsf);

private:
  Standard_EXPORT void invalidateViewer();

protected:
  occ::handle<AIS_InteractiveContext> myContext;
  occ::handle<AIS_InteractiveObject>  myObject;
};
