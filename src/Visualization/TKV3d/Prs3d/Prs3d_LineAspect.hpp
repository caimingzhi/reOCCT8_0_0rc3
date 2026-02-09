#pragma once

#include <Graphic3d_AspectLine3d.hpp>
#include <Prs3d_BasicAspect.hpp>
#include <Quantity_Color.hpp>

class Prs3d_LineAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_LineAspect, Prs3d_BasicAspect)
public:
  Standard_EXPORT Prs3d_LineAspect(const Quantity_Color&   theColor,
                                   const Aspect_TypeOfLine theType,
                                   const double            theWidth);

  Prs3d_LineAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  void SetColor(const Quantity_Color& theColor) { myAspect->SetColor(theColor); }

  void SetTypeOfLine(const Aspect_TypeOfLine theType) { myAspect->SetType(theType); }

  void SetWidth(const double theWidth) { myAspect->SetWidth(theWidth); }

  const occ::handle<Graphic3d_AspectLine3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect) { myAspect = theAspect; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectLine3d> myAspect;
};
