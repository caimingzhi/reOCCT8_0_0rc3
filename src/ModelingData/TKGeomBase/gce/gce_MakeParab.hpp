#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Parab.hpp>
#include <gce_Root.hpp>
class gp_Ax2;
class gp_Ax1;
class gp_Pnt;

class gce_MakeParab : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeParab(const gp_Ax2& A2, const double Focal);

  Standard_EXPORT gce_MakeParab(const gp_Ax1& D, const gp_Pnt& F);

  Standard_EXPORT const gp_Parab& Value() const;

  Standard_EXPORT const gp_Parab& Operator() const;
  Standard_EXPORT                 operator gp_Parab() const;

private:
  gp_Parab TheParab;
};
