#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;

class BRepGProp_Cinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Cinert();

  Standard_EXPORT BRepGProp_Cinert(const BRepAdaptor_Curve& C, const gp_Pnt& CLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  Standard_EXPORT void Perform(const BRepAdaptor_Curve& C);
};
