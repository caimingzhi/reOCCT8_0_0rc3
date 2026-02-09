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

  Standard_EXPORT Geom2dHatch_Element(const Geom2dAdaptor_Curve& Curve,
                                      const TopAbs_Orientation   Orientation = TopAbs_FORWARD);

  Standard_EXPORT const Geom2dAdaptor_Curve& Curve() const;

  Standard_EXPORT Geom2dAdaptor_Curve& ChangeCurve();

  Standard_EXPORT void Orientation(const TopAbs_Orientation Orientation);

  Standard_EXPORT TopAbs_Orientation Orientation() const;

private:
  Geom2dAdaptor_Curve myCurve;
  TopAbs_Orientation  myOrientation;
};
