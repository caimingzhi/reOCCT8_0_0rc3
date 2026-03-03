#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Real.hpp>
namespace model { namespace adapter {
class BRepAdaptor_Curve;
}} // namespace model::adapter


namespace model { namespace localproperties {
class BRepLProp
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static GeomAbs_Shape Continuity(const ::model::adapter::BRepAdaptor_Curve& C1,
                                                  const ::model::adapter::BRepAdaptor_Curve& C2,
                                                  const double             u1,
                                                  const double             u2,
                                                  const double             tl,
                                                  const double             ta);

  Standard_EXPORT static GeomAbs_Shape Continuity(const ::model::adapter::BRepAdaptor_Curve& C1,
                                                  const ::model::adapter::BRepAdaptor_Curve& C2,
                                                  const double             u1,
                                                  const double             u2);
};
}} // namespace model::localproperties

