#include <GeomFill_CornerState.hpp>

GeomFill_CornerState::GeomFill_CornerState()
    : gap(RealLast()),
      tgtang(0.0),
      isconstrained(false),
      norang(0.0),
      scal(1.),
      coonscnd(true)
{
}

double GeomFill_CornerState::Gap() const
{
  return gap;
}

void GeomFill_CornerState::Gap(const double G)
{
  gap = G;
}

double GeomFill_CornerState::TgtAng() const
{
  return tgtang;
}

void GeomFill_CornerState::TgtAng(const double Ang)
{
  tgtang = Ang;
}

bool GeomFill_CornerState::HasConstraint() const
{
  return isconstrained;
}

void GeomFill_CornerState::Constraint()
{
  isconstrained = true;
}

double GeomFill_CornerState::NorAng() const
{
  return norang;
}

void GeomFill_CornerState::NorAng(const double Ang)
{
  norang = Ang;
}

bool GeomFill_CornerState::IsToKill(double& Scal) const
{
  Scal = scal;
  if (!isconstrained)
    return false;
  return !coonscnd;
}

void GeomFill_CornerState::DoKill(const double Scal)
{
  scal     = Scal;
  coonscnd = false;
}
