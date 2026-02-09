#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Cone.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;
class gp_Ax1;
class gp_Lin;

class gce_MakeCone : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeCone(const gp_Ax2& A2, const double Ang, const double Radius);

  Standard_EXPORT gce_MakeCone(const gp_Cone& Cone, const gp_Pnt& Point);

  Standard_EXPORT gce_MakeCone(const gp_Cone& Cone, const double Dist);

  Standard_EXPORT gce_MakeCone(const gp_Pnt& P1,
                               const gp_Pnt& P2,
                               const gp_Pnt& P3,
                               const gp_Pnt& P4);

  Standard_EXPORT gce_MakeCone(const gp_Ax1& Axis, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT gce_MakeCone(const gp_Lin& Axis, const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT gce_MakeCone(const gp_Pnt& P1,
                               const gp_Pnt& P2,
                               const double  R1,
                               const double  R2);

  Standard_EXPORT const gp_Cone& Value() const;

  Standard_EXPORT const gp_Cone& Operator() const;
  Standard_EXPORT                operator gp_Cone() const;

private:
  gp_Cone TheCone;
};
