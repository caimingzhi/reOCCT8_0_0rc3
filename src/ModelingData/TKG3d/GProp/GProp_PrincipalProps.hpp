#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <GProp_GProps.hpp>
#include <Standard_Boolean.hpp>

class GProp_PrincipalProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_PrincipalProps();

  Standard_EXPORT bool HasSymmetryAxis() const;

  Standard_EXPORT bool HasSymmetryAxis(const double aTol) const;

  Standard_EXPORT bool HasSymmetryPoint() const;

  Standard_EXPORT bool HasSymmetryPoint(const double aTol) const;

  Standard_EXPORT void Moments(double& Ixx, double& Iyy, double& Izz) const;

  Standard_EXPORT const gp_Vec& FirstAxisOfInertia() const;

  Standard_EXPORT const gp_Vec& SecondAxisOfInertia() const;

  Standard_EXPORT const gp_Vec& ThirdAxisOfInertia() const;

  Standard_EXPORT void RadiusOfGyration(double& Rxx, double& Ryy, double& Rzz) const;

  friend

    Standard_EXPORT GProp_PrincipalProps
    GProp_GProps::PrincipalProperties() const;

private:
  Standard_EXPORT GProp_PrincipalProps(const double  Ixx,
                                       const double  Iyy,
                                       const double  Izz,
                                       const double  Rxx,
                                       const double  Ryy,
                                       const double  Rzz,
                                       const gp_Vec& Vxx,
                                       const gp_Vec& Vyy,
                                       const gp_Vec& Vzz,
                                       const gp_Pnt& G);

  double i1;
  double i2;
  double i3;
  double r1;
  double r2;
  double r3;
  gp_Vec v1;
  gp_Vec v2;
  gp_Vec v3;
  gp_Pnt g;
};
