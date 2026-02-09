#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomAPI_IntCS.hpp>
#include <gp_Pnt.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_IntersectionSegment.hpp>

GeomAPI_IntCS::GeomAPI_IntCS() = default;

GeomAPI_IntCS::GeomAPI_IntCS(const occ::handle<Geom_Curve>& C, const occ::handle<Geom_Surface>& S)
{
  Perform(C, S);
}

void GeomAPI_IntCS::Perform(const occ::handle<Geom_Curve>& C, const occ::handle<Geom_Surface>& S)
{
  myCurve = C;

  occ::handle<GeomAdaptor_Curve>   HC = new GeomAdaptor_Curve(C);
  occ::handle<GeomAdaptor_Surface> HS = new GeomAdaptor_Surface(S);

  myIntCS.Perform(HC, HS);
}

bool GeomAPI_IntCS::IsDone() const
{
  return myIntCS.IsDone();
}

int GeomAPI_IntCS::NbPoints() const
{
  return myIntCS.NbPoints();
}

const gp_Pnt& GeomAPI_IntCS::Point(const int Index) const
{
  return myIntCS.Point(Index).Pnt();
}

void GeomAPI_IntCS::Parameters(const int Index, double& U, double& V, double& W) const
{
  const IntCurveSurface_IntersectionPoint& ThePoint = myIntCS.Point(Index);

  U = ThePoint.U();
  V = ThePoint.V();
  W = ThePoint.W();
}

int GeomAPI_IntCS::NbSegments() const
{
  return myIntCS.NbSegments();
}

occ::handle<Geom_Curve> GeomAPI_IntCS::Segment(const int Index) const
{
  const IntCurveSurface_IntersectionPoint& FirstPoint = myIntCS.Segment(Index).FirstPoint();

  const IntCurveSurface_IntersectionPoint& LastPoint = myIntCS.Segment(Index).SecondPoint();

  occ::handle<Geom_TrimmedCurve> TheCurve =
    new Geom_TrimmedCurve(myCurve, FirstPoint.W(), LastPoint.W());

  return TheCurve;
}

void GeomAPI_IntCS::Parameters(const int Index,
                               double&   U1,
                               double&   V1,
                               double&   U2,
                               double&   V2) const
{
  const IntCurveSurface_IntersectionPoint& FirstPoint = myIntCS.Segment(Index).FirstPoint();

  const IntCurveSurface_IntersectionPoint& LastPoint = myIntCS.Segment(Index).SecondPoint();

  U1 = FirstPoint.U();
  V1 = FirstPoint.V();
  U2 = LastPoint.U();
  V2 = LastPoint.V();
}
