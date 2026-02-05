#pragma once

#include <Prs3d_LineAspect.hpp>

//! A framework to define the display attributes of isoparameters.
//! This framework can be used to modify the default
//! setting for isoparameters in Prs3d_Drawer.
class Prs3d_IsoAspect : public Prs3d_LineAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_IsoAspect, Prs3d_LineAspect)
public:
  //! Constructs a framework to define display attributes of isoparameters.
  //! These include:
  //! -   the color attribute aColor
  //! -   the type of line aType
  //! -   the width value aWidth
  //! -   aNumber, the number of isoparameters to be displayed.
  Prs3d_IsoAspect(const Quantity_Color&   theColor,
                  const Aspect_TypeOfLine theType,
                  const double            theWidth,
                  const int               theNumber)
      : Prs3d_LineAspect(theColor, theType, theWidth),
        myNumber(theNumber)
  {
  }

  //! defines the number of U or V isoparametric curves
  //! to be drawn for a single face.
  //! Default value: 10
  void SetNumber(const int theNumber) { myNumber = theNumber; }

  //! returns the number of U or V isoparametric curves drawn for a single face.
  int Number() const { return myNumber; }

protected:
  int myNumber;
};
