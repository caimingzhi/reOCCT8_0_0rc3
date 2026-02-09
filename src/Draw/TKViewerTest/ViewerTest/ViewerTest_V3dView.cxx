

#include <ViewerTest_V3dView.hpp>

#include <ViewerTest.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ViewerTest_V3dView, V3d_View)

ViewerTest_V3dView::ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                       const V3d_TypeOfView           theType,
                                       bool                           theIs2dMode)
    : V3d_View(theViewer, theType),
      myIs2dMode(theIs2dMode)
{
}

ViewerTest_V3dView::ViewerTest_V3dView(const occ::handle<V3d_Viewer>& theViewer,
                                       const occ::handle<V3d_View>&   theView)
    : V3d_View(theViewer, theView),
      myIs2dMode(false)
{
  if (occ::handle<ViewerTest_V3dView> aV3dView = occ::down_cast<ViewerTest_V3dView>(theView))
  {
    myIs2dMode = aV3dView->IsViewIn2DMode();
  }
}

bool ViewerTest_V3dView::IsCurrentViewIn2DMode()
{
  if (occ::handle<ViewerTest_V3dView> aV3dView =
        occ::down_cast<ViewerTest_V3dView>(ViewerTest::CurrentView()))
  {
    return aV3dView->IsViewIn2DMode();
  }
  return false;
}

void ViewerTest_V3dView::SetCurrentView2DMode(bool theIs2d)
{
  if (occ::handle<ViewerTest_V3dView> aV3dView =
        occ::down_cast<ViewerTest_V3dView>(ViewerTest::CurrentView()))
  {
    aV3dView->SetView2DMode(theIs2d);
  }
}
