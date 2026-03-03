#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
namespace model { namespace adapter {
class BRepAdaptor_Curve;
}} // namespace model::adapter

class gp_Pnt;
class gp_Vec;

namespace model { namespace localproperties {
class BRepLProp_CurveTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Value(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P);

  Standard_EXPORT static void D1(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT static void D2(const ::model::adapter::BRepAdaptor_Curve& C,
                                 const double             U,
                                 gp_Pnt&                  P,
                                 gp_Vec&                  V1,
                                 gp_Vec&                  V2);

  Standard_EXPORT static void D3(const ::model::adapter::BRepAdaptor_Curve& C,
                                 const double             U,
                                 gp_Pnt&                  P,
                                 gp_Vec&                  V1,
                                 gp_Vec&                  V2,
                                 gp_Vec&                  V3);

  Standard_EXPORT static int Continuity(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static double FirstParameter(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static double LastParameter(const ::model::adapter::BRepAdaptor_Curve& C);
};
}} // namespace model::localproperties

