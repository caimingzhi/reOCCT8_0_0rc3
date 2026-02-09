#include <Geom_BSplineCurve.hpp>
#include <GeomFill_SectionGenerator.hpp>

GeomFill_SectionGenerator::GeomFill_SectionGenerator()
{
  if (mySequence.Length() > 1)
  {
    occ::handle<NCollection_HArray1<double>> HPar =
      new (NCollection_HArray1<double>)(1, mySequence.Length());
    for (int i = 1; i <= mySequence.Length(); i++)
    {
      HPar->ChangeValue(i) = i - 1;
    }
    SetParam(HPar);
  }
}

void GeomFill_SectionGenerator::SetParam(const occ::handle<NCollection_HArray1<double>>& Params)
{
  int ii, L = Params->Upper() - Params->Lower() + 1;
  myParams = Params;
  for (ii = 1; ii <= L; ii++)
  {
    myParams->SetValue(ii, Params->Value(Params->Lower() + ii - 1));
  }
}

void GeomFill_SectionGenerator::GetShape(int& NbPoles,
                                         int& NbKnots,
                                         int& Degree,
                                         int& NbPoles2d) const
{
  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(1));
  NbPoles                          = C->NbPoles();
  NbKnots                          = C->NbKnots();
  Degree                           = C->Degree();
  NbPoles2d                        = 0;
}

void GeomFill_SectionGenerator::Knots(NCollection_Array1<double>& TKnots) const
{
  (occ::down_cast<Geom_BSplineCurve>(mySequence(1)))->Knots(TKnots);
}

void GeomFill_SectionGenerator::Mults(NCollection_Array1<int>& TMults) const
{
  (occ::down_cast<Geom_BSplineCurve>(mySequence(1)))->Multiplicities(TMults);
}

bool GeomFill_SectionGenerator::Section(const int                   P,
                                        NCollection_Array1<gp_Pnt>& Poles,
                                        NCollection_Array1<gp_Vec>&,
                                        NCollection_Array1<gp_Pnt2d>& Poles2d,
                                        NCollection_Array1<gp_Vec2d>&,
                                        NCollection_Array1<double>& Weigths,
                                        NCollection_Array1<double>&) const
{
  Section(P, Poles, Poles2d, Weigths);
  return false;
}

void GeomFill_SectionGenerator::Section(const int                   P,
                                        NCollection_Array1<gp_Pnt>& Poles,
                                        NCollection_Array1<gp_Pnt2d>&,
                                        NCollection_Array1<double>& Weigths) const
{
  occ::handle<Geom_BSplineCurve> C = occ::down_cast<Geom_BSplineCurve>(mySequence(P));

  C->Poles(Poles);
  C->Weights(Weigths);
}

double GeomFill_SectionGenerator::Parameter(const int P) const
{
  return myParams->Value(P);
}
