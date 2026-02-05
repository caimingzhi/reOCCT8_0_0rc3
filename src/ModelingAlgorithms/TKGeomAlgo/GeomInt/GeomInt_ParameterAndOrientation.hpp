#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <TopAbs_Orientation.hpp>

class GeomInt_ParameterAndOrientation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_ParameterAndOrientation();

  Standard_EXPORT GeomInt_ParameterAndOrientation(const double             P,
                                                  const TopAbs_Orientation Or1,
                                                  const TopAbs_Orientation Or2);

  Standard_EXPORT void SetOrientation1(const TopAbs_Orientation Or);

  Standard_EXPORT void SetOrientation2(const TopAbs_Orientation Or);

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT TopAbs_Orientation Orientation1() const;

  Standard_EXPORT TopAbs_Orientation Orientation2() const;

private:
  double             prm;
  TopAbs_Orientation or1;
  TopAbs_Orientation or2;
};
