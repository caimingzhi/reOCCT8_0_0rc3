#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class gp_Cylinder;
class gp_Pnt;
class gp_Cone;
class gp_Sphere;
class gp_Torus;

//! Computes the global properties of a bounded
//! elementary surface in 3d (surface of the gp package)
class GProp_SelGProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_SelGProps();

  Standard_EXPORT GProp_SelGProps(const gp_Cylinder& S,
                                  const double       Alpha1,
                                  const double       Alpha2,
                                  const double       Z1,
                                  const double       Z2,
                                  const gp_Pnt&      SLocation);

  Standard_EXPORT GProp_SelGProps(const gp_Cone& S,
                                  const double   Alpha1,
                                  const double   Alpha2,
                                  const double   Z1,
                                  const double   Z2,
                                  const gp_Pnt&  SLocation);

  Standard_EXPORT GProp_SelGProps(const gp_Sphere& S,
                                  const double     Teta1,
                                  const double     Teta2,
                                  const double     Alpha1,
                                  const double     Alpha2,
                                  const gp_Pnt&    SLocation);

  Standard_EXPORT GProp_SelGProps(const gp_Torus& S,
                                  const double    Teta1,
                                  const double    Teta2,
                                  const double    Alpha1,
                                  const double    Alpha2,
                                  const gp_Pnt&   SLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& SLocation);

  Standard_EXPORT void Perform(const gp_Cylinder& S,
                               const double       Alpha1,
                               const double       Alpha2,
                               const double       Z1,
                               const double       Z2);

  Standard_EXPORT void Perform(const gp_Cone& S,
                               const double   Alpha1,
                               const double   Alpha2,
                               const double   Z1,
                               const double   Z2);

  Standard_EXPORT void Perform(const gp_Sphere& S,
                               const double     Teta1,
                               const double     Teta2,
                               const double     Alpha1,
                               const double     Alpha2);

  Standard_EXPORT void Perform(const gp_Torus& S,
                               const double    Teta1,
                               const double    Teta2,
                               const double    Alpha1,
                               const double    Alpha2);
};
