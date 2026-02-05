#pragma once

#include <V3d_View.hpp>

//! Setting additional flag to store 2D mode of the View to avoid scene rotation by mouse/key events
class ViewerTest_V3dView : public V3d_View
{
  DEFINE_STANDARD_RTTIEXT(ViewerTest_V3dView, V3d_View)
public:
  //! Initializes the view.
  Standard_EXPORT ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                     const V3d_TypeOfView           theType     = V3d_ORTHOGRAPHIC,
                                     bool                           theIs2dMode = false);

  //! Initializes the view by copying.
  Standard_EXPORT ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                     const occ::handle<V3d_View>&   theView);

  //! Returns true if 2D mode is set for the view
  bool IsViewIn2DMode() const { return myIs2dMode; }

  //! Sets 2D mode for the view
  void SetView2DMode(bool the2dMode) { myIs2dMode = the2dMode; }

public:
  //! Returns true if active view in 2D mode.
  Standard_EXPORT static bool IsCurrentViewIn2DMode();

  //! Set if active view in 2D mode.
  Standard_EXPORT static void SetCurrentView2DMode(bool theIs2d);

private:
  bool myIs2dMode; //!< 2D mode flag
};
