#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Parab2d.hpp>
#include <gce_Root.hpp>
#include <Standard_Boolean.hpp>
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;

class gce_MakeParab2d : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeParab2d(const gp_Ax2d& MirrorAxis,
                                  const double   Focal,
                                  const bool     Sense = true);

  Standard_EXPORT gce_MakeParab2d(const gp_Ax22d& A, const double Focal);

  Standard_EXPORT gce_MakeParab2d(const gp_Ax2d& D, const gp_Pnt2d& F, const bool Sense = true);

  Standard_EXPORT gce_MakeParab2d(const gp_Pnt2d& S1,
                                  const gp_Pnt2d& Center,
                                  const bool      Sense = true);

  Standard_EXPORT const gp_Parab2d& Value() const;

  Standard_EXPORT const gp_Parab2d& Operator() const;
  Standard_EXPORT                   operator gp_Parab2d() const;

private:
  gp_Parab2d TheParab2d;
};
