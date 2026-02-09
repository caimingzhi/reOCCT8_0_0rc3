#include <Geom_BSplineCurve.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Surface.hpp>
#include <GeomFill_Generator.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>

GeomFill_Generator::GeomFill_Generator() = default;

void GeomFill_Generator::Perform(const double PTol)
{

  GeomFill_Profiler::Perform(PTol);

  int  i, j;
  int  NbUPoles    = NbPoles();
  int  NbVPoles    = mySequence.Length();
  int  NbUKnots    = NbKnots();
  int  NbVKnots    = NbVPoles;
  bool isUPeriodic = IsPeriodic();
  bool isVPeriodic = false;

  NCollection_Array2<gp_Pnt> Poles(1, NbUPoles, 1, NbVPoles);
  NCollection_Array2<double> Weights(1, NbUPoles, 1, NbVPoles);
  NCollection_Array1<double> UKnots(1, NbUKnots);
  NCollection_Array1<double> VKnots(1, NbVKnots);
  NCollection_Array1<int>    UMults(1, NbUKnots);
  NCollection_Array1<int>    VMults(1, NbVKnots);
  VMults.Init(1);

  VMults(1) = VMults(NbVKnots) = 2;

  KnotsAndMults(UKnots, UMults);

  NCollection_Array1<gp_Pnt> Pole(1, NbUPoles);
  NCollection_Array1<double> Weight(1, NbUPoles);
  for (j = 1; j <= NbVPoles; j++)
  {
    occ::handle<Geom_BSplineCurve> Cj = occ::down_cast<Geom_BSplineCurve>(mySequence(j));
    Cj->Poles(Pole);
    Cj->Weights(Weight);
    VKnots(j) = (double)(j - 1);
    for (i = 1; i <= NbUPoles; i++)
    {
      Poles(i, j)   = Pole(i);
      Weights(i, j) = Weight(i);
    }
  }

  mySurface = new Geom_BSplineSurface(Poles,
                                      Weights,
                                      UKnots,
                                      VKnots,
                                      UMults,
                                      VMults,
                                      Degree(),
                                      1,
                                      isUPeriodic,
                                      isVPeriodic);
}
