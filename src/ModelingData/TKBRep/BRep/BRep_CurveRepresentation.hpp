#pragma once

#include <Standard.hpp>

#include <TopLoc_Location.hpp>
#include <Standard_Transient.hpp>
#include <GeomAbs_Shape.hpp>
class Geom_Surface;
class Poly_Triangulation;
class Geom_Curve;
class Geom2d_Curve;
class Poly_Polygon3D;
class Poly_Polygon2D;
class Poly_PolygonOnTriangulation;

class BRep_CurveRepresentation : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool IsCurve3D() const;

  Standard_EXPORT virtual bool IsCurveOnSurface() const;

  Standard_EXPORT virtual bool IsRegularity() const;

  Standard_EXPORT virtual bool IsCurveOnClosedSurface() const;

  Standard_EXPORT virtual bool IsCurveOnSurface(const occ::handle<Geom_Surface>& S,
                                                const TopLoc_Location&           L) const;

  Standard_EXPORT virtual bool IsRegularity(const occ::handle<Geom_Surface>& S1,
                                            const occ::handle<Geom_Surface>& S2,
                                            const TopLoc_Location&           L1,
                                            const TopLoc_Location&           L2) const;

  Standard_EXPORT virtual bool IsPolygon3D() const;

  Standard_EXPORT virtual bool IsPolygonOnTriangulation() const;

  Standard_EXPORT virtual bool IsPolygonOnTriangulation(const occ::handle<Poly_Triangulation>& T,
                                                        const TopLoc_Location& L) const;

  Standard_EXPORT virtual bool IsPolygonOnClosedTriangulation() const;

  Standard_EXPORT virtual bool IsPolygonOnSurface() const;

  Standard_EXPORT virtual bool IsPolygonOnSurface(const occ::handle<Geom_Surface>& S,
                                                  const TopLoc_Location&           L) const;

  Standard_EXPORT virtual bool IsPolygonOnClosedSurface() const;

  const TopLoc_Location& Location() const;

  void Location(const TopLoc_Location& L);

  Standard_EXPORT virtual const occ::handle<Geom_Curve>& Curve3D() const;

  Standard_EXPORT virtual void Curve3D(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT virtual const occ::handle<Geom_Surface>& Surface() const;

  Standard_EXPORT virtual const occ::handle<Geom2d_Curve>& PCurve() const;

  Standard_EXPORT virtual void PCurve(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT virtual const occ::handle<Geom2d_Curve>& PCurve2() const;

  Standard_EXPORT virtual void PCurve2(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT virtual const occ::handle<Poly_Polygon3D>& Polygon3D() const;

  Standard_EXPORT virtual void Polygon3D(const occ::handle<Poly_Polygon3D>& P);

  Standard_EXPORT virtual const occ::handle<Poly_Polygon2D>& Polygon() const;

  Standard_EXPORT virtual void Polygon(const occ::handle<Poly_Polygon2D>& P);

  Standard_EXPORT virtual const occ::handle<Poly_Polygon2D>& Polygon2() const;

  Standard_EXPORT virtual void Polygon2(const occ::handle<Poly_Polygon2D>& P);

  Standard_EXPORT virtual const occ::handle<Poly_Triangulation>& Triangulation() const;

  Standard_EXPORT virtual const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation()
    const;

  Standard_EXPORT virtual void PolygonOnTriangulation(
    const occ::handle<Poly_PolygonOnTriangulation>& P);

  Standard_EXPORT virtual const occ::handle<Poly_PolygonOnTriangulation>& PolygonOnTriangulation2()
    const;

  Standard_EXPORT virtual void PolygonOnTriangulation2(
    const occ::handle<Poly_PolygonOnTriangulation>& P2);

  Standard_EXPORT virtual const occ::handle<Geom_Surface>& Surface2() const;

  Standard_EXPORT virtual const TopLoc_Location& Location2() const;

  Standard_EXPORT virtual const GeomAbs_Shape& Continuity() const;

  Standard_EXPORT virtual void Continuity(const GeomAbs_Shape C);

  Standard_EXPORT virtual occ::handle<BRep_CurveRepresentation> Copy() const = 0;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(BRep_CurveRepresentation, Standard_Transient)

protected:
  Standard_EXPORT BRep_CurveRepresentation(const TopLoc_Location& L);

  TopLoc_Location myLocation;
};

inline const TopLoc_Location& BRep_CurveRepresentation::Location() const
{
  return myLocation;
}

inline void BRep_CurveRepresentation::Location(const TopLoc_Location& L)
{
  myLocation = L;
}
