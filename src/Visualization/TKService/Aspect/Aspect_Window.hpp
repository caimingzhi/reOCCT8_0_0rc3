#pragma once

#include <Aspect_Background.hpp>
#include <Aspect_GradientBackground.hpp>
#include <Aspect_FBConfig.hpp>
#include <Aspect_FillMethod.hpp>
#include <Quantity_Color.hpp>
#include <Aspect_GradientFillMethod.hpp>
#include <Aspect_TypeOfResize.hpp>
#include <Aspect_Drawable.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

class Aspect_DisplayConnection;

class Aspect_Window : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_Window, Standard_Transient)
public:
  Standard_EXPORT bool IsVirtual() const;

  Standard_EXPORT void SetVirtual(const bool theVirtual);

  NCollection_Vec2<int> TopLeft() const
  {
    NCollection_Vec2<int> aTopLeft, aBotRight;
    Position(aTopLeft.x(), aTopLeft.y(), aBotRight.x(), aBotRight.y());
    return aTopLeft;
  }

  NCollection_Vec2<int> Dimensions() const
  {
    NCollection_Vec2<int> aSize;
    Size(aSize.x(), aSize.y());
    return aSize;
  }

  const occ::handle<Aspect_DisplayConnection>& DisplayConnection() const { return myDisplay; }

  Standard_EXPORT Aspect_Background Background() const;

  Standard_EXPORT Aspect_FillMethod BackgroundFillMethod() const;

  Standard_EXPORT Aspect_GradientBackground GradientBackground() const;

  Standard_EXPORT void SetBackground(const Aspect_Background& theBack);

  Standard_EXPORT void SetBackground(const Quantity_Color& theColor);

  Standard_EXPORT void SetBackground(const Aspect_GradientBackground& theBackground);

  Standard_EXPORT void SetBackground(const Quantity_Color&           theFirstColor,
                                     const Quantity_Color&           theSecondColor,
                                     const Aspect_GradientFillMethod theFillMethod);

public:
  Standard_EXPORT virtual bool IsMapped() const = 0;

  Standard_EXPORT virtual void Map() const = 0;

  Standard_EXPORT virtual void Unmap() const = 0;

  Standard_EXPORT virtual Aspect_TypeOfResize DoResize() = 0;

  Standard_EXPORT virtual bool DoMapping() const = 0;

  Standard_EXPORT virtual double Ratio() const = 0;

  Standard_EXPORT virtual void Position(int& X1, int& Y1, int& X2, int& Y2) const = 0;

  Standard_EXPORT virtual void Size(int& Width, int& Height) const = 0;

  Standard_EXPORT virtual Aspect_Drawable NativeHandle() const = 0;

  Standard_EXPORT virtual Aspect_Drawable NativeParentHandle() const = 0;

  Standard_EXPORT virtual Aspect_FBConfig NativeFBConfig() const = 0;

  virtual void SetTitle(const TCollection_AsciiString& theTitle) { (void)theTitle; }

  virtual void InvalidateContent(const occ::handle<Aspect_DisplayConnection>& theDisp)
  {
    (void)theDisp;
  }

public:
  virtual double DevicePixelRatio() const { return 1.0; }

  virtual NCollection_Vec2<double> ConvertPointToBacking(
    const NCollection_Vec2<double>& thePnt) const
  {
    return thePnt * DevicePixelRatio();
  }

  virtual NCollection_Vec2<double> ConvertPointFromBacking(
    const NCollection_Vec2<double>& thePnt) const
  {
    return thePnt / DevicePixelRatio();
  }

public:
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT Aspect_Window();

protected:
  occ::handle<Aspect_DisplayConnection> myDisplay;
  Aspect_Background                     MyBackground;
  Aspect_GradientBackground             MyGradientBackground;
  Aspect_FillMethod                     MyBackgroundFillMethod;
  bool                                  MyIsVirtual;
};
