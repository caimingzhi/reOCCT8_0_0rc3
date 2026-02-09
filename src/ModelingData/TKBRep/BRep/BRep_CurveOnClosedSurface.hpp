#pragma once

#include <Standard.hpp>

#include <BRep_CurveOnSurface.hpp>
class Geom2d_Curve;
class Geom_Surface;
class TopLoc_Location;
class BRep_CurveRepresentation;

class BRep_CurveOnClosedSurface : public BRep_CurveOnSurface
{

public:
  Standard_EXPORT BRep_CurveOnClosedSurface(const occ::handle<Geom2d_Curve>& PC1,
                                            const occ::handle<Geom2d_Curve>& PC2,
                                            const occ::handle<Geom_Surface>& S,
                                            const TopLoc_Location&           L,
                                            const GeomAbs_Shape              C);

  void SetUVPoints2(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

  void UVPoints2(gp_Pnt2d& P1, gp_Pnt2d& P2) const;

  Standard_EXPORT bool IsCurveOnClosedSurface() const override;

  Standard_EXPORT bool IsRegularity() const override;

  Standard_EXPORT bool IsRegularity(const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const TopLoc_Location&           L1,
                                    const TopLoc_Location&           L2) const override;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve2() const override;

  Standard_EXPORT const occ::handle<Geom_Surface>& Surface2() const override;

  Standard_EXPORT const TopLoc_Location& Location2() const override;

  Standard_EXPORT const GeomAbs_Shape& Continuity() const override;

  Standard_EXPORT void Continuity(const GeomAbs_Shape C) override;

  Standard_EXPORT void PCurve2(const occ::handle<Geom2d_Curve>& C) override;

  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  Standard_EXPORT void Update() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_CurveOnClosedSurface, BRep_CurveOnSurface)

private:
  occ::handle<Geom2d_Curve> myPCurve2;
  GeomAbs_Shape             myContinuity;
  gp_Pnt2d                  myUV21;
  gp_Pnt2d                  myUV22;
};

inline void BRep_CurveOnClosedSurface::SetUVPoints2(const gp_Pnt2d& P1, const gp_Pnt2d& P2)
{
  myUV21 = P1;
  myUV22 = P2;
}

inline void BRep_CurveOnClosedSurface::UVPoints2(gp_Pnt2d& P1, gp_Pnt2d& P2) const
{
  P1 = myUV21;
  P2 = myUV22;
}
