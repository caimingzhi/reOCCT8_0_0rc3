#pragma once

#include <Graphic3d_AspectLine3d.hpp>
#include <Prs3d_BasicAspect.hpp>

class Prs3d_ArrowAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_ArrowAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_ArrowAspect();

  Standard_EXPORT Prs3d_ArrowAspect(const double anAngle, const double aLength);

  Standard_EXPORT Prs3d_ArrowAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect);

  Standard_EXPORT void SetAngle(const double anAngle);

  double Angle() const { return myAngle; }

  void SetLength(const double theLength) { myLength = theLength; }

  double Length() const { return myLength; }

  void SetZoomable(bool theIsZoomable) { myIsZoomable = theIsZoomable; }

  bool IsZoomable() const { return myIsZoomable; }

  void SetColor(const Quantity_Color& theColor) { myArrowAspect->SetColor(theColor); }

  const occ::handle<Graphic3d_AspectLine3d>& Aspect() const { return myArrowAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect)
  {
    myArrowAspect = theAspect;
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectLine3d> myArrowAspect;
  double                              myAngle;
  double                              myLength;
  bool                                myIsZoomable;
};
