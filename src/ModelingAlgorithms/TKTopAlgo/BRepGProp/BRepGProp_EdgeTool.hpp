#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
namespace model { namespace adapter {
class BRepAdaptor_Curve;
}} // namespace model::adapter

class gp_Pnt;
class gp_Vec;

class BRepGProp_EdgeTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FirstParameter(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static double LastParameter(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static int IntegrationOrder(const ::model::adapter::BRepAdaptor_Curve& C);

  Standard_EXPORT static gp_Pnt Value(const ::model::adapter::BRepAdaptor_Curve& C, const double U);

  Standard_EXPORT static void D1(const ::model::adapter::BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT static int NbIntervals(const ::model::adapter::BRepAdaptor_Curve& C, const GeomAbs_Shape S);

  Standard_EXPORT static void Intervals(const ::model::adapter::BRepAdaptor_Curve&    C,
                                        NCollection_Array1<double>& T,
                                        const GeomAbs_Shape         S);
};
