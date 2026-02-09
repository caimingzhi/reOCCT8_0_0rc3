#pragma once

enum Aspect_TypeOfHighlightMethod
{
  Aspect_TOHM_COLOR,
  Aspect_TOHM_BOUNDBOX
};

#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Quantity_ColorRGBA.hpp>

class Graphic3d_PresentationAttributes : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_PresentationAttributes, Standard_Transient)
public:
  Graphic3d_PresentationAttributes()
      : myBasicColor(Quantity_NOC_WHITE),
        myHiMethod(Aspect_TOHM_COLOR),
        myZLayer(Graphic3d_ZLayerId_Default),
        myDispMode(0)
  {
  }

  ~Graphic3d_PresentationAttributes() override = default;

  Aspect_TypeOfHighlightMethod Method() const { return myHiMethod; }

  virtual void SetMethod(const Aspect_TypeOfHighlightMethod theMethod) { myHiMethod = theMethod; }

  const Quantity_ColorRGBA& ColorRGBA() const { return myBasicColor; }

  const Quantity_Color& Color() const { return myBasicColor.GetRGB(); }

  virtual void SetColor(const Quantity_Color& theColor) { myBasicColor.ChangeRGB() = theColor; }

  float Transparency() const { return 1.0f - myBasicColor.Alpha(); }

  virtual void SetTransparency(const float theTranspCoef)
  {
    myBasicColor.SetAlpha(1.0f - theTranspCoef);
  }

  Graphic3d_ZLayerId ZLayer() const { return myZLayer; }

  virtual void SetZLayer(const Graphic3d_ZLayerId theLayer) { myZLayer = theLayer; }

  int DisplayMode() const { return myDispMode; }

  virtual void SetDisplayMode(const int theMode) { myDispMode = theMode; }

  const occ::handle<Graphic3d_AspectFillArea3d>& BasicFillAreaAspect() const
  {
    return myBasicFillAreaAspect;
  }

  virtual void SetBasicFillAreaAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect)
  {
    myBasicFillAreaAspect = theAspect;
  }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  occ::handle<Graphic3d_AspectFillArea3d> myBasicFillAreaAspect;
  Quantity_ColorRGBA                      myBasicColor;
  Aspect_TypeOfHighlightMethod            myHiMethod;
  Graphic3d_ZLayerId                      myZLayer;
  int                                     myDispMode;
};
