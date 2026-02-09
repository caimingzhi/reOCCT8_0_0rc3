#include <gp_Pnt2d.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <TopOpeBRep_WPointInter.hpp>

TopOpeBRep_WPointInter::TopOpeBRep_WPointInter() = default;

void TopOpeBRep_WPointInter::Set(const IntSurf_PntOn2S& P)
{
  myPP2S = (IntSurf_PntOn2S*)&P;
}

void TopOpeBRep_WPointInter::ParametersOnS1(double& U1, double& V1) const
{
  myPP2S->ParametersOnS1(U1, V1);
}

void TopOpeBRep_WPointInter::ParametersOnS2(double& U2, double& V2) const
{
  myPP2S->ParametersOnS2(U2, V2);
}

void TopOpeBRep_WPointInter::Parameters(double& U1, double& V1, double& U2, double& V2) const
{
  myPP2S->Parameters(U1, V1, U2, V2);
}

gp_Pnt2d TopOpeBRep_WPointInter::ValueOnS1() const
{
  double u, v;
  myPP2S->ParametersOnS1(u, v);
  return gp_Pnt2d(u, v);
}

gp_Pnt2d TopOpeBRep_WPointInter::ValueOnS2() const
{
  double u, v;
  myPP2S->ParametersOnS2(u, v);
  return gp_Pnt2d(u, v);
}

const gp_Pnt& TopOpeBRep_WPointInter::Value() const
{
  return myPP2S->Value();
}

TopOpeBRep_PPntOn2S TopOpeBRep_WPointInter::PPntOn2SDummy() const
{
  return myPP2S;
}
