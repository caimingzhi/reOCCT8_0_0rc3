#include <ElCLib.hpp>
#include <GC_MakeArcOfEllipse.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <StdFail_NotDone.hpp>

GC_MakeArcOfEllipse::GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                         const gp_Pnt&   P1,
                                         const gp_Pnt&   P2,
                                         const bool      Sense)
{
  double                    Alpha1 = ElCLib::Parameter(Elips, P1);
  double                    Alpha2 = ElCLib::Parameter(Elips, P2);
  occ::handle<Geom_Ellipse> E      = new Geom_Ellipse(Elips);
  TheArc                           = new Geom_TrimmedCurve(E, Alpha1, Alpha2, Sense);
  TheError                         = gce_Done;
}

GC_MakeArcOfEllipse::GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                         const gp_Pnt&   P,
                                         const double    Alpha,
                                         const bool      Sense)
{
  double                    Alphafirst = ElCLib::Parameter(Elips, P);
  occ::handle<Geom_Ellipse> E          = new Geom_Ellipse(Elips);
  TheArc                               = new Geom_TrimmedCurve(E, Alphafirst, Alpha, Sense);
  TheError                             = gce_Done;
}

GC_MakeArcOfEllipse::GC_MakeArcOfEllipse(const gp_Elips& Elips,
                                         const double    Alpha1,
                                         const double    Alpha2,
                                         const bool      Sense)
{
  occ::handle<Geom_Ellipse> E = new Geom_Ellipse(Elips);
  TheArc                      = new Geom_TrimmedCurve(E, Alpha1, Alpha2, Sense);
  TheError                    = gce_Done;
}

const occ::handle<Geom_TrimmedCurve>& GC_MakeArcOfEllipse::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeArcOfEllipse::Value() - no result");
  return TheArc;
}
