#include <ChFiDS_CircSection.hpp>
#include <gp_Circ.hpp>
#include <gp_Lin.hpp>

ChFiDS_CircSection::ChFiDS_CircSection()
    : myF(0.0),
      myL(0.0)
{
}

void ChFiDS_CircSection::Set(const gp_Circ& C, const double F, const double L)
{
  myCirc = C;
  myF    = F;
  myL    = L;
}

void ChFiDS_CircSection::Set(const gp_Lin& C, const double F, const double L)
{
  myLin = C;
  myF   = F;
  myL   = L;
}

void ChFiDS_CircSection::Get(gp_Circ& C, double& F, double& L) const
{
  C = myCirc;
  F = myF;
  L = myL;
}

void ChFiDS_CircSection::Get(gp_Lin& C, double& F, double& L) const
{
  C = myLin;
  F = myF;
  L = myL;
}
