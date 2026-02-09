#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class gp_Circ;
class gp_Pnt;
class gp_Lin;

class GProp_CelGProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_CelGProps();

  Standard_EXPORT GProp_CelGProps(const gp_Circ& C, const gp_Pnt& CLocation);

  Standard_EXPORT GProp_CelGProps(const gp_Circ& C,
                                  const double   U1,
                                  const double   U2,
                                  const gp_Pnt&  CLocation);

  Standard_EXPORT GProp_CelGProps(const gp_Lin& C,
                                  const double  U1,
                                  const double  U2,
                                  const gp_Pnt& CLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& CLocation);

  Standard_EXPORT void Perform(const gp_Circ& C, const double U1, const double U2);

  Standard_EXPORT void Perform(const gp_Lin& C, const double U1, const double U2);
};
