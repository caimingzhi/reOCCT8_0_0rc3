#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
namespace model { namespace adapter {
class BRepAdaptor_Surface;
}} // namespace model::adapter

class gp_Pnt;
class gp_Vec;

class BRepLProp_SurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Value(const ::model::adapter::BRepAdaptor_Surface& S,
                                    const double               U,
                                    const double               V,
                                    gp_Pnt&                    P);

  Standard_EXPORT static void D1(const ::model::adapter::BRepAdaptor_Surface& S,
                                 const double               U,
                                 const double               V,
                                 gp_Pnt&                    P,
                                 gp_Vec&                    D1U,
                                 gp_Vec&                    D1V);

  Standard_EXPORT static void D2(const ::model::adapter::BRepAdaptor_Surface& S,
                                 const double               U,
                                 const double               V,
                                 gp_Pnt&                    P,
                                 gp_Vec&                    D1U,
                                 gp_Vec&                    D1V,
                                 gp_Vec&                    D2U,
                                 gp_Vec&                    D2V,
                                 gp_Vec&                    DUV);

  Standard_EXPORT static gp_Vec DN(const ::model::adapter::BRepAdaptor_Surface& S,
                                   const double               U,
                                   const double               V,
                                   const int                  IU,
                                   const int                  IV);

  Standard_EXPORT static int Continuity(const ::model::adapter::BRepAdaptor_Surface& S);

  Standard_EXPORT static void Bounds(const ::model::adapter::BRepAdaptor_Surface& S,
                                     double&                    U1,
                                     double&                    V1,
                                     double&                    U2,
                                     double&                    V2);
};
