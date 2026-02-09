#include <ChFiDS_Regul.hpp>

ChFiDS_Regul::ChFiDS_Regul()
    : icurv(0),
      is1(0),
      is2(0)
{
}

void ChFiDS_Regul::SetCurve(const int IC)
{
  icurv = std::abs(IC);
}

void ChFiDS_Regul::SetS1(const int IS1, const bool IsFace)
{
  if (IsFace)
    is1 = std::abs(IS1);
  else
    is1 = -std::abs(IS1);
}

void ChFiDS_Regul::SetS2(const int IS2, const bool IsFace)
{
  if (IsFace)
    is2 = std::abs(IS2);
  else
    is2 = -std::abs(IS2);
}

bool ChFiDS_Regul::IsSurface1() const
{
  return (is1 < 0);
}

bool ChFiDS_Regul::IsSurface2() const
{
  return (is2 < 0);
}

int ChFiDS_Regul::Curve() const
{
  return icurv;
}

int ChFiDS_Regul::S1() const
{
  return std::abs(is1);
}

int ChFiDS_Regul::S2() const
{
  return std::abs(is2);
}
