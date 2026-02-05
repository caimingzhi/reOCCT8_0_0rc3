#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class IntSurf_PntOn2S;
typedef IntSurf_PntOn2S* TopOpeBRep_PPntOn2S;

class gp_Pnt2d;
class gp_Pnt;

class TopOpeBRep_WPointInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_WPointInter();

  Standard_EXPORT void Set(const IntSurf_PntOn2S& P);

  Standard_EXPORT void ParametersOnS1(double& U, double& V) const;

  Standard_EXPORT void ParametersOnS2(double& U, double& V) const;

  Standard_EXPORT void Parameters(double& U1, double& V1, double& U2, double& V2) const;

  Standard_EXPORT gp_Pnt2d ValueOnS1() const;

  Standard_EXPORT gp_Pnt2d ValueOnS2() const;

  Standard_EXPORT const gp_Pnt& Value() const;

  Standard_EXPORT TopOpeBRep_PPntOn2S PPntOn2SDummy() const;

private:
  TopOpeBRep_PPntOn2S myPP2S;
};
