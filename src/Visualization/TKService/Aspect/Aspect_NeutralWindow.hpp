#pragma once

#include <Aspect_Window.hpp>

class Aspect_NeutralWindow : public Aspect_Window
{
  DEFINE_STANDARD_RTTIEXT(Aspect_NeutralWindow, Aspect_Window)
public:
  Standard_EXPORT Aspect_NeutralWindow();

  Aspect_Drawable NativeHandle() const override { return myHandle; }

  Aspect_Drawable NativeParentHandle() const override { return myParentHandle; }

  Aspect_FBConfig NativeFBConfig() const override { return myFBConfig; }

  bool SetNativeHandle(Aspect_Drawable theWindow)
  {
    return SetNativeHandles(theWindow, 0, nullptr);
  }

  Standard_EXPORT bool SetNativeHandles(Aspect_Drawable theWindow,
                                        Aspect_Drawable theParentWindow,
                                        Aspect_FBConfig theFbConfig);

  bool IsMapped() const override { return myIsMapped; }

  void Map() const override { myIsMapped = true; }

  void Unmap() const override { myIsMapped = false; }

  Aspect_TypeOfResize DoResize() override { return Aspect_TOR_UNKNOWN; }

  bool DoMapping() const override { return true; }

  double Ratio() const override
  {
    return (myWidth != 0 && myHeight != 0) ? double(myWidth) / double(myHeight) : 1.0;
  }

  void Position(int& theX1, int& theY1, int& theX2, int& theY2) const override
  {
    theX1 = myPosX;
    theX2 = myPosX + myWidth;
    theY1 = myPosY;
    theY2 = myPosY + myHeight;
  }

  Standard_EXPORT bool SetPosition(int theX1, int theY1);

  Standard_EXPORT bool SetPosition(int theX1, int theY1, int theX2, int theY2);

  void Size(int& theWidth, int& theHeight) const override
  {
    theWidth  = myWidth;
    theHeight = myHeight;
  }

  Standard_EXPORT bool SetSize(const int theWidth, const int theHeight);

protected:
  Aspect_Drawable myHandle;
  Aspect_Drawable myParentHandle;
  Aspect_FBConfig myFBConfig;
  int             myPosX;
  int             myPosY;
  int             myWidth;
  int             myHeight;
  mutable bool    myIsMapped;
};
