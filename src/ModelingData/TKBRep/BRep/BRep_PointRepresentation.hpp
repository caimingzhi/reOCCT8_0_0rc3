#pragma once

#include <Standard.hpp>

#include <TopLoc_Location.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;

//! Root class for the points representations.
//! Contains a location and a parameter.
class BRep_PointRepresentation : public Standard_Transient
{

public:
  //! A point on a 3d curve.
  Standard_EXPORT virtual bool IsPointOnCurve() const;

  //! A point on a 2d curve on a surface.
  Standard_EXPORT virtual bool IsPointOnCurveOnSurface() const;

  //! A point on a surface.
  Standard_EXPORT virtual bool IsPointOnSurface() const;

  //! A point on the curve <C>.
  Standard_EXPORT virtual bool IsPointOnCurve(const occ::handle<Geom_Curve>& C,
                                              const TopLoc_Location&         L) const;

  //! A point on the 2d curve <PC> on the surface <S>.
  Standard_EXPORT virtual bool IsPointOnCurveOnSurface(const occ::handle<Geom2d_Curve>& PC,
                                                       const occ::handle<Geom_Surface>& S,
                                                       const TopLoc_Location&           L) const;

  //! A point on the surface <S>.
  Standard_EXPORT virtual bool IsPointOnSurface(const occ::handle<Geom_Surface>& S,
                                                const TopLoc_Location&           L) const;

  const TopLoc_Location& Location() const;

  void Location(const TopLoc_Location& L);

  double Parameter() const;

  void Parameter(const double P);

  Standard_EXPORT virtual double Parameter2() const;

  Standard_EXPORT virtual void Parameter2(const double P);

  Standard_EXPORT virtual const occ::handle<Geom_Curve>& Curve() const;

  Standard_EXPORT virtual void Curve(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT virtual const occ::handle<Geom2d_Curve>& PCurve() const;

  Standard_EXPORT virtual void PCurve(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT virtual const occ::handle<Geom_Surface>& Surface() const;

  Standard_EXPORT virtual void Surface(const occ::handle<Geom_Surface>& S);

  //! Dumps the content of me into the stream
  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(BRep_PointRepresentation, Standard_Transient)

protected:
  Standard_EXPORT BRep_PointRepresentation(const double P, const TopLoc_Location& L);

private:
  TopLoc_Location myLocation;
  double          myParameter;
};

inline const TopLoc_Location& BRep_PointRepresentation::Location() const
{
  return myLocation;
}

//=================================================================================================

inline void BRep_PointRepresentation::Location(const TopLoc_Location& L)
{
  myLocation = L;
}

//=================================================================================================

inline double BRep_PointRepresentation::Parameter() const
{
  return myParameter;
}

//=================================================================================================

inline void BRep_PointRepresentation::Parameter(const double P)
{
  myParameter = P;
}
