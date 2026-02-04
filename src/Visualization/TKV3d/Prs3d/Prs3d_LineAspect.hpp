#pragma once


#include <Graphic3d_AspectLine3d.hpp>
#include <Prs3d_BasicAspect.hpp>
#include <Quantity_Color.hpp>

//! A framework for defining how a line will be displayed
//! in a presentation. Aspects of line display include
//! width, color and type of line.
//! The definition set by this class is then passed to the
//! attribute manager Prs3d_Drawer.
//! Any object which requires a value for line aspect as
//! an argument may then be given the attribute manager
//! as a substitute argument in the form of a field such as myDrawer for example.
class Prs3d_LineAspect : public Prs3d_BasicAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_LineAspect, Prs3d_BasicAspect)
public:
  //! Constructs a framework for line aspect defined by
  //! -   the color aColor
  //! -   the type of line aType and
  //! -   the line thickness aWidth.
  //! Type of line refers to whether the line is solid or dotted, for example.
  Standard_EXPORT Prs3d_LineAspect(const Quantity_Color&   theColor,
                                   const Aspect_TypeOfLine theType,
                                   const double            theWidth);

  Prs3d_LineAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect)
      : myAspect(theAspect)
  {
  }

  //! Sets the line color defined at the time of construction.
  //! Default value: Quantity_NOC_YELLOW
  void SetColor(const Quantity_Color& theColor) { myAspect->SetColor(theColor); }

  //! Sets the type of line defined at the time of construction.
  //! This could, for example, be solid, dotted or made up of dashes.
  //! Default value: Aspect_TOL_SOLID
  void SetTypeOfLine(const Aspect_TypeOfLine theType) { myAspect->SetType(theType); }

  //! Sets the line width defined at the time of construction.
  //! Default value: 1.
  void SetWidth(const double theWidth) { myAspect->SetWidth(theWidth); }

  //! Returns the line aspect. This is defined as the set of
  //! color, type and thickness attributes.
  const occ::handle<Graphic3d_AspectLine3d>& Aspect() const { return myAspect; }

  void SetAspect(const occ::handle<Graphic3d_AspectLine3d>& theAspect) { myAspect = theAspect; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  occ::handle<Graphic3d_AspectLine3d> myAspect;
};

