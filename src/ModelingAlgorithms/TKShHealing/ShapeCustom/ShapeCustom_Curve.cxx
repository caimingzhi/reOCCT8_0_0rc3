

#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeCustom_Curve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

ShapeCustom_Curve::ShapeCustom_Curve() = default;

ShapeCustom_Curve::ShapeCustom_Curve(const occ::handle<Geom_Curve>& C)
{
  Init(C);
}

void ShapeCustom_Curve::Init(const occ::handle<Geom_Curve>& C)
{
  myCurve = C;
}

occ::handle<Geom_Curve> ShapeCustom_Curve::ConvertToPeriodic(const bool   substitute,
                                                             const double preci)
{
  occ::handle<Geom_Curve>        newCurve;
  occ::handle<Geom_BSplineCurve> BSpl = occ::down_cast<Geom_BSplineCurve>(myCurve);
  if (BSpl.IsNull())
    return newCurve;

  bool closed = ShapeAnalysis_Curve::IsClosed(myCurve, preci);

  if (!closed)
    return newCurve;

  bool converted = false;

  if (closed && !BSpl->IsPeriodic() && BSpl->NbPoles() > 3)
  {
    bool set = true;

    if (BSpl->Multiplicity(1) == BSpl->Degree() + 1
        && BSpl->Multiplicity(BSpl->NbKnots()) == BSpl->Degree() + 1)
    {
      int                        nbPoles = BSpl->NbPoles();
      NCollection_Array1<gp_Pnt> oldPoles(1, nbPoles);
      NCollection_Array1<double> oldWeights(1, nbPoles);
      int                        nbKnots = BSpl->NbKnots();
      NCollection_Array1<double> oldKnots(1, nbKnots);
      NCollection_Array1<int>    oldMults(1, nbKnots);

      BSpl->Poles(oldPoles);
      BSpl->Weights(oldWeights);
      BSpl->Knots(oldKnots);
      BSpl->Multiplicities(oldMults);

      NCollection_Array1<double> newKnots(1, nbKnots + 2);
      NCollection_Array1<int>    newMults(1, nbKnots + 2);
      double                     a =
        0.5 * (BSpl->Knot(2) - BSpl->Knot(1) + BSpl->Knot(nbKnots) - BSpl->Knot(nbKnots - 1));

      newKnots(1)           = oldKnots(1) - a;
      newKnots(nbKnots + 2) = oldKnots(nbKnots) + a;
      newMults(1) = newMults(nbKnots + 2) = 1;
      for (int i = 2; i <= nbKnots + 1; i++)
      {
        newKnots(i) = oldKnots(i - 1);
        newMults(i) = oldMults(i - 1);
      }
      newMults(2) = newMults(nbKnots + 1) = BSpl->Degree();
      occ::handle<Geom_BSplineCurve> res  = new Geom_BSplineCurve(oldPoles,
                                                                 oldWeights,
                                                                 newKnots,
                                                                 newMults,
                                                                 BSpl->Degree(),
                                                                 BSpl->IsPeriodic());
      BSpl                                = res;
    }
    else if (BSpl->Multiplicity(1) > BSpl->Degree()
             || BSpl->Multiplicity(BSpl->NbKnots()) > BSpl->Degree() + 1)
      set = false;
    if (set)
    {
      BSpl->SetPeriodic();
      converted = true;
    }
  }
#ifdef OCCT_DEBUG
  std::cout << "Warning: ShapeCustom_Surface: Closed BSplineSurface is caused to be periodic"
            << std::endl;
#endif
  if (!converted)
    return newCurve;
  newCurve = BSpl;
  if (substitute)
    myCurve = newCurve;
  return newCurve;
}
