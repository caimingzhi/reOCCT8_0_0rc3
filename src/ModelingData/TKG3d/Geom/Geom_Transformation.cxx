#include <Geom_Transformation.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Geom_Transformation, Standard_Transient)

Geom_Transformation::Geom_Transformation() = default;

Geom_Transformation::Geom_Transformation(const gp_Trsf& T)
    : gpTrsf(T)
{
}

occ::handle<Geom_Transformation> Geom_Transformation::Copy() const
{

  occ::handle<Geom_Transformation> T;
  T = new Geom_Transformation(gpTrsf);
  return T;
}

occ::handle<Geom_Transformation> Geom_Transformation::Inverted() const
{

  return new Geom_Transformation(gpTrsf.Inverted());
}

occ::handle<Geom_Transformation> Geom_Transformation::Multiplied(
  const occ::handle<Geom_Transformation>& Other) const
{

  return new Geom_Transformation(gpTrsf.Multiplied(Other->Trsf()));
}

occ::handle<Geom_Transformation> Geom_Transformation::Powered(const int N) const
{

  gp_Trsf T = gpTrsf;
  T.Power(N);
  return new Geom_Transformation(T);
}

void Geom_Transformation::PreMultiply(const occ::handle<Geom_Transformation>& Other)
{

  gpTrsf.PreMultiply(Other->Trsf());
}

void Geom_Transformation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &gpTrsf)
}
