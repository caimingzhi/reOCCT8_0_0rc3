#include <d3d9.h>

#include <D3DHost_GraphicDriver.hpp>
#include <D3DHost_View.hpp>

IMPLEMENT_STANDARD_RTTIEXT(D3DHost_GraphicDriver, OpenGl_GraphicDriver)

#ifdef _MSC_VER
  #pragma comment(lib, "D3D9.lib")
#endif

//=================================================================================================

D3DHost_GraphicDriver::D3DHost_GraphicDriver()
    : OpenGl_GraphicDriver(occ::handle<Aspect_DisplayConnection>(), true)
{
}

//=================================================================================================

D3DHost_GraphicDriver::~D3DHost_GraphicDriver() {}

//=================================================================================================

occ::handle<Graphic3d_CView> D3DHost_GraphicDriver::CreateView(
  const occ::handle<Graphic3d_StructureManager>& theMgr)
{
  occ::handle<D3DHost_View> aView = new D3DHost_View(theMgr, this, myCaps, &myStateCounter);
  myMapOfView.Add(aView);
  for (NCollection_List<occ::handle<Graphic3d_Layer>>::Iterator aLayerIter(myLayers);
       aLayerIter.More();
       aLayerIter.Next())
  {
    const occ::handle<Graphic3d_Layer>& aLayer = aLayerIter.Value();
    aView->InsertLayerAfter(aLayer->LayerId(), aLayer->LayerSettings(), Graphic3d_ZLayerId_UNKNOWN);
  }
  return aView;
}
