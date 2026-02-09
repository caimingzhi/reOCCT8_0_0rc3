#pragma once

#include <V3d_View.hpp>

class ViewerTest_V3dView : public V3d_View
{
  DEFINE_STANDARD_RTTIEXT(ViewerTest_V3dView, V3d_View)
public:
  Standard_EXPORT ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                     const V3d_TypeOfView           theType     = V3d_ORTHOGRAPHIC,
                                     bool                           theIs2dMode = false);

  Standard_EXPORT ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                     const occ::handle<V3d_View>&   theView);

  bool IsViewIn2DMode() const { return myIs2dMode; }

  void SetView2DMode(bool the2dMode) { myIs2dMode = the2dMode; }

public:
  Standard_EXPORT static bool IsCurrentViewIn2DMode();

  Standard_EXPORT static void SetCurrentView2DMode(bool theIs2d);

private:
  bool myIs2dMode;
};
