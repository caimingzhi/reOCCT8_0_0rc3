#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Hypr.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;

class gce_MakeHypr : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeHypr(const gp_Ax2& A2,
                               const double  MajorRadius,
                               const double  MinorRadius);

  Standard_EXPORT gce_MakeHypr(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center);

  Standard_EXPORT const gp_Hypr& Value() const;

  Standard_EXPORT const gp_Hypr& Operator() const;
  Standard_EXPORT                operator gp_Hypr() const;

private:
  gp_Hypr TheHypr;
};
