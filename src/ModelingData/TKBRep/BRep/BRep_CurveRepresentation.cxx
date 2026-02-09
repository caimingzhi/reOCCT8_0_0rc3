#include <BRep_CurveRepresentation.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Poly_Polygon2D.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_CurveRepresentation, Standard_Transient)

BRep_CurveRepresentation::BRep_CurveRepresentation(const TopLoc_Location& L)
    : myLocation(L)
{
}

bool BRep_CurveRepresentation::IsCurve3D() const
{
  return false;
}

bool BRep_CurveRepresentation::IsCurveOnSurface() const
{
  return false;
}

bool BRep_CurveRepresentation::IsCurveOnClosedSurface() const
{
  return false;
}

bool BRep_CurveRepresentation::IsRegularity() const
{
  return false;
}

bool BRep_CurveRepresentation::IsCurveOnSurface(const occ::handle<Geom_Surface>&,
                                                const TopLoc_Location&) const
{
  return false;
}

bool BRep_CurveRepresentation::IsRegularity(const occ::handle<Geom_Surface>&,
                                            const occ::handle<Geom_Surface>&,
                                            const TopLoc_Location&,
                                            const TopLoc_Location&) const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygon3D() const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnTriangulation() const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnTriangulation(const occ::handle<Poly_Triangulation>&,
                                                        const TopLoc_Location&) const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnClosedTriangulation() const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnClosedSurface() const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnSurface() const
{
  return false;
}

bool BRep_CurveRepresentation::IsPolygonOnSurface(const occ::handle<Geom_Surface>&,
                                                  const TopLoc_Location&) const
{
  return false;
}

const occ::handle<Geom_Curve>& BRep_CurveRepresentation::Curve3D() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::Curve3D(const occ::handle<Geom_Curve>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Geom_Surface>& BRep_CurveRepresentation::Surface() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Geom2d_Curve>& BRep_CurveRepresentation::PCurve() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Geom2d_Curve>& BRep_CurveRepresentation::PCurve2() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::PCurve(const occ::handle<Geom2d_Curve>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::PCurve2(const occ::handle<Geom2d_Curve>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const GeomAbs_Shape& BRep_CurveRepresentation::Continuity() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::Continuity(const GeomAbs_Shape)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Geom_Surface>& BRep_CurveRepresentation::Surface2() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const TopLoc_Location& BRep_CurveRepresentation::Location2() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_Polygon3D>& BRep_CurveRepresentation::Polygon3D() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::Polygon3D(const occ::handle<Poly_Polygon3D>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_Polygon2D>& BRep_CurveRepresentation::Polygon() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::Polygon(const occ::handle<Poly_Polygon2D>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_PolygonOnTriangulation>& BRep_CurveRepresentation::PolygonOnTriangulation2()
  const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::PolygonOnTriangulation2(
  const occ::handle<Poly_PolygonOnTriangulation>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::PolygonOnTriangulation(
  const occ::handle<Poly_PolygonOnTriangulation>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_PolygonOnTriangulation>& BRep_CurveRepresentation::PolygonOnTriangulation()
  const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_Triangulation>& BRep_CurveRepresentation::Triangulation() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

const occ::handle<Poly_Polygon2D>& BRep_CurveRepresentation::Polygon2() const
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::Polygon2(const occ::handle<Poly_Polygon2D>&)
{
  throw Standard_DomainError("BRep_CurveRepresentation");
}

void BRep_CurveRepresentation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myLocation)
}
