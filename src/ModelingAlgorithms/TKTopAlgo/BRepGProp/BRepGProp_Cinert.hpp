#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
namespace model { namespace adapter {
class BRepAdaptor_Curve;
}} // namespace model::adapter

class gp_Pnt;

class BRepGProp_Cinert : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_Cinert();

  Standard_EXPORT BRepGProp_Cinert(const ::model::adapter::BRepAdaptor_Curve& C, const gp_Pnt& CLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  Standard_EXPORT void Perform(const ::model::adapter::BRepAdaptor_Curve& C);
};
