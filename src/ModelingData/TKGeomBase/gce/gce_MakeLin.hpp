#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Lin.hpp>
#include <gce_Root.hpp>
class gp_Ax1;
class gp_Pnt;
class gp_Dir;

class gce_MakeLin : public gce_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT gce_MakeLin(const gp_Ax1& A1);

  Standard_EXPORT gce_MakeLin(const gp_Pnt& P, const gp_Dir& V);

  Standard_EXPORT gce_MakeLin(const gp_Lin& Lin, const gp_Pnt& Point);

  Standard_EXPORT gce_MakeLin(const gp_Pnt& P1, const gp_Pnt& P2);

  Standard_EXPORT const gp_Lin& Value() const;

  Standard_EXPORT const gp_Lin& Operator() const;
  Standard_EXPORT               operator gp_Lin() const;

private:
  gp_Lin TheLin;
};
