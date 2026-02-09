#include <Geom2dHatch_Element.hpp>

#include <Geom2dAdaptor_Curve.hpp>

Geom2dHatch_Element::Geom2dHatch_Element() = default;

Geom2dHatch_Element::Geom2dHatch_Element(const Geom2dAdaptor_Curve& Curve,
                                         const TopAbs_Orientation   Orientation)
    : myCurve(Curve),
      myOrientation(Orientation)
{
}

const Geom2dAdaptor_Curve& Geom2dHatch_Element::Curve() const
{
  return myCurve;
}

Geom2dAdaptor_Curve& Geom2dHatch_Element::ChangeCurve()
{
  return myCurve;
}

void Geom2dHatch_Element::Orientation(const TopAbs_Orientation Orientation)
{
  myOrientation = Orientation;
}

TopAbs_Orientation Geom2dHatch_Element::Orientation() const
{
  return myOrientation;
}
