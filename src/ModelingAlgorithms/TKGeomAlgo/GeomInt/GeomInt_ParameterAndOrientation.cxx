#include <GeomInt_ParameterAndOrientation.hpp>

GeomInt_ParameterAndOrientation::GeomInt_ParameterAndOrientation()
    : prm(0.0),
      or1(TopAbs_FORWARD),
      or2(TopAbs_FORWARD)
{
}

GeomInt_ParameterAndOrientation::GeomInt_ParameterAndOrientation(const double             P,
                                                                 const TopAbs_Orientation Or1,
                                                                 const TopAbs_Orientation Or2)
    : prm(P),
      or1(Or1),
      or2(Or2)
{
}

void GeomInt_ParameterAndOrientation::SetOrientation1(const TopAbs_Orientation Or1)
{
  or1 = Or1;
}

void GeomInt_ParameterAndOrientation::SetOrientation2(const TopAbs_Orientation Or2)
{
  or2 = Or2;
}

double GeomInt_ParameterAndOrientation::Parameter() const
{
  return prm;
}

TopAbs_Orientation GeomInt_ParameterAndOrientation::Orientation1() const
{
  return or1;
}

TopAbs_Orientation GeomInt_ParameterAndOrientation::Orientation2() const
{
  return or2;
}
