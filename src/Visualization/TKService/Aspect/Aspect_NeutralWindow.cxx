

#include <Aspect_NeutralWindow.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Aspect_NeutralWindow, Aspect_Window)

Aspect_NeutralWindow::Aspect_NeutralWindow()
    : myHandle(0),
      myParentHandle(0),
      myFBConfig(nullptr),
      myPosX(0),
      myPosY(0),
      myWidth(0),
      myHeight(0),
      myIsMapped(true)
{
}

bool Aspect_NeutralWindow::SetNativeHandles(Aspect_Drawable theWindow,
                                            Aspect_Drawable theParentWindow,
                                            Aspect_FBConfig theFbConfig)
{
  if (myHandle == theWindow && myParentHandle == theParentWindow && myFBConfig == theFbConfig)
  {
    return false;
  }

  myHandle       = theWindow;
  myParentHandle = theParentWindow;
  myFBConfig     = theFbConfig;
  return true;
}

bool Aspect_NeutralWindow::SetPosition(int theX1, int theY1)
{
  if (myPosX == theX1 && myPosY == theY1)
  {
    return false;
  }

  myPosX = theX1;
  myPosY = theY1;
  return true;
}

bool Aspect_NeutralWindow::SetPosition(int theX1, int theY1, int theX2, int theY2)
{
  int aWidthNew  = theX2 - theX1;
  int aHeightNew = theY2 - theY1;
  if (myPosX == theX1 && myPosY == theY1 && myWidth == aWidthNew && myHeight == aHeightNew)
  {
    return false;
  }

  myPosX   = theX1;
  myWidth  = aWidthNew;
  myPosY   = theY1;
  myHeight = aHeightNew;
  return true;
}

bool Aspect_NeutralWindow::SetSize(const int theWidth, const int theHeight)
{
  if (myWidth == theWidth && myHeight == theHeight)
  {
    return false;
  }

  myWidth  = theWidth;
  myHeight = theHeight;
  return true;
}
