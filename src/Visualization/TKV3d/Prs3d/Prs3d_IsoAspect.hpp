#pragma once

#include <Prs3d_LineAspect.hpp>

class Prs3d_IsoAspect : public Prs3d_LineAspect
{
  DEFINE_STANDARD_RTTIEXT(Prs3d_IsoAspect, Prs3d_LineAspect)
public:
  Prs3d_IsoAspect(const Quantity_Color&   theColor,
                  const Aspect_TypeOfLine theType,
                  const double            theWidth,
                  const int               theNumber)
      : Prs3d_LineAspect(theColor, theType, theWidth),
        myNumber(theNumber)
  {
  }

  void SetNumber(const int theNumber) { myNumber = theNumber; }

  int Number() const { return myNumber; }

protected:
  int myNumber;
};
