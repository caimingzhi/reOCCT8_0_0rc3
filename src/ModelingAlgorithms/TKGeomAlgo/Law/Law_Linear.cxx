#include <Law_Function.hpp>
#include <Law_Linear.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Law_Linear, Law_Function)

Law_Linear::Law_Linear()
    : valdeb(0.0),
      valfin(0.0),
      pdeb(0.0),
      pfin(0.0)
{
}

void Law_Linear::Set(const double Pdeb, const double Valdeb, const double Pfin, const double Valfin)
{
  pdeb   = Pdeb;
  pfin   = Pfin;
  valdeb = Valdeb;
  valfin = Valfin;
}

GeomAbs_Shape Law_Linear::Continuity() const
{
  return GeomAbs_CN;
}

int Law_Linear::NbIntervals(const GeomAbs_Shape) const
{
  return 1;
}

void Law_Linear::Intervals(NCollection_Array1<double>& T,

                           const GeomAbs_Shape) const
{
  T.SetValue(T.Lower(), pdeb);
  T.SetValue(T.Upper(), pfin);
}

double Law_Linear::Value(const double X)
{
  return ((X - pdeb) * valfin + (pfin - X) * valdeb) / (pfin - pdeb);
}

void Law_Linear::D1(const double X, double& F, double& D)
{
  F = ((X - pdeb) * valfin + (pfin - X) * valdeb) / (pfin - pdeb);
  D = (valfin - valdeb) / (pfin - pdeb);
}

void Law_Linear::D2(const double X, double& F, double& D, double& D2)
{
  F  = ((X - pdeb) * valfin + (pfin - X) * valdeb) / (pfin - pdeb);
  D  = (valfin - valdeb) / (pfin - pdeb);
  D2 = 0;
}

occ::handle<Law_Function> Law_Linear::Trim(const double PFirst,
                                           const double PLast,

                                           const double) const
{
  occ::handle<Law_Linear> l = new (Law_Linear)();
  double                  Vdeb, Vfin;
  Vdeb = ((PFirst - pdeb) * valfin + (pfin - PFirst) * valdeb) / (pfin - pdeb);
  Vfin = ((PLast - pdeb) * valfin + (pfin - PLast) * valdeb) / (pfin - pdeb);
  l->Set(PFirst, Vdeb, PLast, Vfin);

  return l;
}

void Law_Linear::Bounds(double& PFirst, double& PLast)
{
  PFirst = pdeb;
  PLast  = pfin;
}
