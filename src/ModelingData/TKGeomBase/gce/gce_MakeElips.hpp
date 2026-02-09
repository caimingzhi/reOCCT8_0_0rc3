#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Elips.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Pnt;

class gce_MakeElips : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeElips(const gp_Ax2& A2,
                                const double  MajorRadius,
                                const double  MinorRadius);

  Standard_EXPORT gce_MakeElips(const gp_Pnt& S1, const gp_Pnt& S2, const gp_Pnt& Center);

  Standard_EXPORT const gp_Elips& Value() const;

  Standard_EXPORT const gp_Elips& Operator() const;
  Standard_EXPORT                 operator gp_Elips() const;

private:
  gp_Elips TheElips;
};
