#pragma once

#include <AIS_InteractiveContext.hpp>
#include <V3d_View.hpp>

class TCollection_AsciiString;

//! Auxiliary tool to control view updates.
class ViewerTest_AutoUpdater
{
public:
  //! Enumeration to control auto-update
  enum RedrawMode
  {
    RedrawMode_Auto = -1,
    RedrawMode_Forced,
    RedrawMode_Suppressed
  };

public:
  //! Constructor
  Standard_EXPORT ViewerTest_AutoUpdater(const occ::handle<AIS_InteractiveContext>& theContext,
                                         const occ::handle<V3d_View>&               theView);

  //! Destructor to automatically update view
  Standard_EXPORT ~ViewerTest_AutoUpdater();

  //! Parse redraw mode argument
  Standard_EXPORT bool parseRedrawMode(const TCollection_AsciiString& theArg);

  //! Disable autoupdate
  Standard_EXPORT void Invalidate();

  //! Finally update view
  Standard_EXPORT void Update();

private:
  occ::handle<AIS_InteractiveContext> myContext;
  occ::handle<V3d_View>               myView;
  ViewerTest_AutoUpdater::RedrawMode  myToUpdate;
  bool                                myWasAutoUpdate;
};
