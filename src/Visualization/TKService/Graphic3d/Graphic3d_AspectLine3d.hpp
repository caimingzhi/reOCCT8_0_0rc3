#pragma once

#include <Graphic3d_Aspects.hpp>

class Graphic3d_AspectLine3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectLine3d, Graphic3d_Aspects)
public:
  Standard_EXPORT Graphic3d_AspectLine3d();

  Standard_EXPORT Graphic3d_AspectLine3d(const Quantity_Color& theColor,
                                         Aspect_TypeOfLine     theType,
                                         double                theWidth);

  Aspect_TypeOfLine Type() const { return myLineType; }

  void SetType(const Aspect_TypeOfLine theType) { SetLineType(theType); }

  float Width() const { return myLineWidth; }

  void SetWidth(const double theWidth) { SetWidth((float)theWidth); }

  void SetWidth(float theWidth) { SetLineWidth(theWidth); }
};
