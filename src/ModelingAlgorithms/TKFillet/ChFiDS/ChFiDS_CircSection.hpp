#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Circ.hpp>
#include <gp_Lin.hpp>

//! A Section of fillet.
class ChFiDS_CircSection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_CircSection();

  Standard_EXPORT void Set(const gp_Circ& C, const double F, const double L);

  Standard_EXPORT void Set(const gp_Lin& C, const double F, const double L);

  Standard_EXPORT void Get(gp_Circ& C, double& F, double& L) const;

  Standard_EXPORT void Get(gp_Lin& C, double& F, double& L) const;

private:
  gp_Circ myCirc;
  gp_Lin  myLin;
  double  myF;
  double  myL;
};

