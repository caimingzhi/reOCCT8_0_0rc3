#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Mat.hpp>
class gp_Ax1;
class GProp_PrincipalProps;

class GProp_GProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GProp_GProps();

  Standard_EXPORT GProp_GProps(const gp_Pnt& SystemLocation);

  Standard_EXPORT void Add(const GProp_GProps& Item, const double Density = 1.0);

  Standard_EXPORT double Mass() const;

  Standard_EXPORT gp_Pnt CentreOfMass() const;

  Standard_EXPORT gp_Mat MatrixOfInertia() const;

  Standard_EXPORT void StaticMoments(double& Ix, double& Iy, double& Iz) const;

  Standard_EXPORT double MomentOfInertia(const gp_Ax1& A) const;

  Standard_EXPORT GProp_PrincipalProps PrincipalProperties() const;

  Standard_EXPORT double RadiusOfGyration(const gp_Ax1& A) const;

protected:
  gp_Pnt g;
  gp_Pnt loc;
  double dim;
  gp_Mat inertia;
};
