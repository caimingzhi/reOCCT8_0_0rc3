#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Hypr2d.hpp>
#include <gce_Root.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt2d;
class gp_Ax2d;
class gp_Ax22d;

class gce_MakeHypr2d : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeHypr2d(const gp_Pnt2d& S1, const gp_Pnt2d& S2, const gp_Pnt2d& Center);

  Standard_EXPORT gce_MakeHypr2d(const gp_Ax2d& MajorAxis,
                                 const double   MajorRadius,
                                 const double   MinorRadius,
                                 const bool     Sense);

  Standard_EXPORT gce_MakeHypr2d(const gp_Ax22d& A,
                                 const double    MajorRadius,
                                 const double    MinorRadius);

  Standard_EXPORT const gp_Hypr2d& Value() const;

  Standard_EXPORT const gp_Hypr2d& Operator() const;
  Standard_EXPORT                  operator gp_Hypr2d() const;

private:
  gp_Hypr2d TheHypr2d;
};
