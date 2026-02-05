#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GProp_GProps.hpp>
class gp_Cylinder;
class gp_Pnt;
class gp_Cone;
class gp_Sphere;
class gp_Torus;

//! Computes the global properties and the volume of a geometric solid
//! (3D closed region of space)
//! The solid can be elementary(definition in the gp package)
class GProp_VelGProps : public GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_VelGProps();

  Standard_EXPORT GProp_VelGProps(const gp_Cylinder& S,
                                  const double       Alpha1,
                                  const double       Alpha2,
                                  const double       Z1,
                                  const double       Z2,
                                  const gp_Pnt&      VLocation);

  Standard_EXPORT GProp_VelGProps(const gp_Cone& S,
                                  const double   Alpha1,
                                  const double   Alpha2,
                                  const double   Z1,
                                  const double   Z2,
                                  const gp_Pnt&  VLocation);

  Standard_EXPORT GProp_VelGProps(const gp_Sphere& S,
                                  const double     Teta1,
                                  const double     Teta2,
                                  const double     Alpha1,
                                  const double     Alpha2,
                                  const gp_Pnt&    VLocation);

  Standard_EXPORT GProp_VelGProps(const gp_Torus& S,
                                  const double    Teta1,
                                  const double    Teta2,
                                  const double    Alpha1,
                                  const double    Alpha2,
                                  const gp_Pnt&   VLocation);

  Standard_EXPORT void SetLocation(const gp_Pnt& VLocation);

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
