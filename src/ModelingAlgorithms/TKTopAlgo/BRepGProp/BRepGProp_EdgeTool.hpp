#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
class BRepAdaptor_Curve;
class gp_Pnt;
class gp_Vec;

class BRepGProp_EdgeTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double FirstParameter(const BRepAdaptor_Curve& C);

  Standard_EXPORT static double LastParameter(const BRepAdaptor_Curve& C);

  Standard_EXPORT static int IntegrationOrder(const BRepAdaptor_Curve& C);

  Standard_EXPORT static gp_Pnt Value(const BRepAdaptor_Curve& C, const double U);

  Standard_EXPORT static void D1(const BRepAdaptor_Curve& C, const double U, gp_Pnt& P, gp_Vec& V1);

  Standard_EXPORT static int NbIntervals(const BRepAdaptor_Curve& C, const GeomAbs_Shape S);

  Standard_EXPORT static void Intervals(const BRepAdaptor_Curve&    C,
                                        NCollection_Array1<double>& T,
                                        const GeomAbs_Shape         S);
};
