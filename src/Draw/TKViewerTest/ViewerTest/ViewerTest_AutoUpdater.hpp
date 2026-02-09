#pragma once

#include <AIS_InteractiveContext.hpp>
#include <V3d_View.hpp>

class TCollection_AsciiString;

class ViewerTest_AutoUpdater
{
public:
  enum RedrawMode
  {
    RedrawMode_Auto = -1,
    RedrawMode_Forced,
    RedrawMode_Suppressed
  };

public:
  Standard_EXPORT ViewerTest_AutoUpdater(const occ::handle<AIS_InteractiveContext>& theContext,
                                         const occ::handle<V3d_View>&               theView);

  Standard_EXPORT ~ViewerTest_AutoUpdater();

  Standard_EXPORT bool parseRedrawMode(const TCollection_AsciiString& theArg);

  Standard_EXPORT void Invalidate();

  Standard_EXPORT void Update();

private:
  occ::handle<AIS_InteractiveContext> myContext;
  occ::handle<V3d_View>               myView;
  ViewerTest_AutoUpdater::RedrawMode  myToUpdate;
  bool                                myWasAutoUpdate;
};
