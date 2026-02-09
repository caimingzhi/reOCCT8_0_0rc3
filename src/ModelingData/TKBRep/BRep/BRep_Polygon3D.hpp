#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRep_CurveRepresentation.hpp>
class Poly_Polygon3D;
class TopLoc_Location;

class BRep_Polygon3D : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_Polygon3D(const occ::handle<Poly_Polygon3D>& P, const TopLoc_Location& L);

  Standard_EXPORT bool IsPolygon3D() const override;

  Standard_EXPORT const occ::handle<Poly_Polygon3D>& Polygon3D() const override;

  Standard_EXPORT void Polygon3D(const occ::handle<Poly_Polygon3D>& P) override;

  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_Polygon3D, BRep_CurveRepresentation)

private:
  occ::handle<Poly_Polygon3D> myPolygon3D;
};
