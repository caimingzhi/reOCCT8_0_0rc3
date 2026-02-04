#pragma once


#include <Standard.hpp>

#include <BRep_CurveRepresentation.hpp>
#include <Standard_Real.hpp>
class Geom_Surface;
class gp_Pnt;

//! Defines a continuity between two surfaces.
class BRep_CurveOn2Surfaces : public BRep_CurveRepresentation
{

public:
  Standard_EXPORT BRep_CurveOn2Surfaces(const occ::handle<Geom_Surface>& S1,
                                        const occ::handle<Geom_Surface>& S2,
                                        const TopLoc_Location&           L1,
                                        const TopLoc_Location&           L2,
                                        const GeomAbs_Shape              C);

  //! Returns True.
  Standard_EXPORT bool IsRegularity() const override;

  //! A curve on two surfaces (continuity).
  Standard_EXPORT bool IsRegularity(const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const TopLoc_Location&           L1,
                                    const TopLoc_Location&           L2) const override;

  //! Raises an error.
  Standard_EXPORT void D0(const double U, gp_Pnt& P) const;

  Standard_EXPORT const occ::handle<Geom_Surface>& Surface() const override;

  Standard_EXPORT const occ::handle<Geom_Surface>& Surface2() const override;

  Standard_EXPORT const TopLoc_Location& Location2() const override;

  Standard_EXPORT const GeomAbs_Shape& Continuity() const override;

  Standard_EXPORT void Continuity(const GeomAbs_Shape C) override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_CurveOn2Surfaces, BRep_CurveRepresentation)

private:
  occ::handle<Geom_Surface> mySurface;
  occ::handle<Geom_Surface> mySurface2;
  TopLoc_Location           myLocation2;
  GeomAbs_Shape             myContinuity;
};

