#include <XCAFView_Object.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XCAFView_Object, Standard_Transient)

//=================================================================================================

XCAFView_Object::XCAFView_Object()
{
  myClippingExpression      = new TCollection_HAsciiString();
  myFrontPlaneClipping      = false;
  myBackPlaneClipping       = false;
  myViewVolumeSidesClipping = false;
  myGDTPoints               = nullptr;
}

//=================================================================================================

XCAFView_Object::XCAFView_Object(const occ::handle<XCAFView_Object>& theObj)
{
  myType                    = theObj->myType;
  myProjectionPoint         = theObj->myProjectionPoint;
  myViewDirection           = theObj->myViewDirection;
  myUpDirection             = theObj->myUpDirection;
  myZoomFactor              = theObj->myZoomFactor;
  myWindowHorizontalSize    = theObj->myWindowHorizontalSize;
  myWindowVerticalSize      = theObj->myWindowVerticalSize;
  myClippingExpression      = theObj->myClippingExpression;
  myFrontPlaneClipping      = theObj->myFrontPlaneClipping;
  myFrontPlaneDistance      = theObj->myFrontPlaneDistance;
  myBackPlaneClipping       = theObj->myBackPlaneClipping;
  myBackPlaneDistance       = theObj->myBackPlaneDistance;
  myViewVolumeSidesClipping = theObj->myViewVolumeSidesClipping;
  myGDTPoints               = nullptr;
}
