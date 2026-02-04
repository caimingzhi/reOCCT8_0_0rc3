#pragma once


#include <Graphic3d_Aspects.hpp>

//! Creates and updates a group of attributes for 3d line primitives.
//! This group contains the color, the type of line, and its thickness.
class Graphic3d_AspectLine3d : public Graphic3d_Aspects
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_AspectLine3d, Graphic3d_Aspects)
public:
  //! Creates a context table for line primitives
  //! defined with the following default values:
  //!
  //! Color = Quantity_NOC_YELLOW;
  //! Type  = Aspect_TOL_SOLID;
  //! Width = 1.0;
  Standard_EXPORT Graphic3d_AspectLine3d();

  //! Creates a context table for line primitives defined with the specified values.
  //! Warning: theWidth is the "line width scale factor".
  //! The nominal line width is 1 pixel.
  //! The width of the line is determined by applying the line width scale factor to this nominal
  //! line width. The supported line widths vary by 1-pixel units.
  Standard_EXPORT Graphic3d_AspectLine3d(const Quantity_Color& theColor,
                                         Aspect_TypeOfLine     theType,
                                         double                theWidth);

  //! Return line type.
  Aspect_TypeOfLine Type() const { return myLineType; }

  //! Modifies the type of line.
  void SetType(const Aspect_TypeOfLine theType) { SetLineType(theType); }

  //! Return line width.
  float Width() const { return myLineWidth; }

  //! Modifies the line thickness.
  //! Warning: Raises Standard_OutOfRange if the width is a negative value.
  void SetWidth(const double theWidth) { SetWidth((float)theWidth); }

  //! Modifies the line thickness.
  //! Warning: Raises Standard_OutOfRange if the width is a negative value.
  void SetWidth(float theWidth) { SetLineWidth(theWidth); }
};

