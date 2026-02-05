#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dAdaptor_Curve.hpp>
#include <TopAbs_Orientation.hpp>

class Geom2dHatch_Element
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_Element();

  //! Creates an element.
  Standard_EXPORT Geom2dHatch_Element(const Geom2dAdaptor_Curve& Curve,
                                      const TopAbs_Orientation   Orientation = TopAbs_FORWARD);

  //! Returns the curve associated to the element.
  Standard_EXPORT const Geom2dAdaptor_Curve& Curve() const;

  //! Returns the curve associated to the element.
  Standard_EXPORT Geom2dAdaptor_Curve& ChangeCurve();

  //! Sets the orientation of the element.
  Standard_EXPORT void Orientation(const TopAbs_Orientation Orientation);

  //! Returns the orientation of the element.
  Standard_EXPORT TopAbs_Orientation Orientation() const;

private:
  Geom2dAdaptor_Curve myCurve;
  TopAbs_Orientation  myOrientation;
};
