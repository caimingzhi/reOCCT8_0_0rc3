#include <Geom2dHatch_Element.hpp>

#include <Geom2dAdaptor_Curve.hpp>

//=================================================================================================

Geom2dHatch_Element::Geom2dHatch_Element() = default;

//=================================================================================================

Geom2dHatch_Element::Geom2dHatch_Element(const Geom2dAdaptor_Curve& Curve,
                                         const TopAbs_Orientation   Orientation)
    : myCurve(Curve),
      myOrientation(Orientation)
{
}

//=======================================================================
// Function : Curve
// Purpose  : Returns the curve associated to the hatching.
//=======================================================================

const Geom2dAdaptor_Curve& Geom2dHatch_Element::Curve() const
{
  return myCurve;
}

//=======================================================================
// Function : ChangeCurve
// Purpose  : Returns the curve associated to the hatching.
//=======================================================================

Geom2dAdaptor_Curve& Geom2dHatch_Element::ChangeCurve()
{
  return myCurve;
}

//=======================================================================
// Function : Orientation
// Purpose  : Sets the orientation of the element.
//=======================================================================

void Geom2dHatch_Element::Orientation(const TopAbs_Orientation Orientation)
{
  myOrientation = Orientation;
}

//=======================================================================
// Function : Orientation
// Purpose  : Returns the orientation of the element.
//=======================================================================

TopAbs_Orientation Geom2dHatch_Element::Orientation() const
{
  return myOrientation;
}
