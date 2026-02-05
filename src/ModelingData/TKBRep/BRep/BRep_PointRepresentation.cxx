#include <BRep_PointRepresentation.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Type.hpp>
#include <TopLoc_Location.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRep_PointRepresentation, Standard_Transient)

//=================================================================================================

BRep_PointRepresentation::BRep_PointRepresentation(const double P, const TopLoc_Location& L)
    : myLocation(L),
      myParameter(P)
{
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnCurve() const
{
  return false;
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnCurveOnSurface() const
{
  return false;
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnSurface() const
{
  return false;
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnCurve(const occ::handle<Geom_Curve>&,
                                              const TopLoc_Location&) const
{
  return false;
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnCurveOnSurface(const occ::handle<Geom2d_Curve>&,
                                                       const occ::handle<Geom_Surface>&,
                                                       const TopLoc_Location&) const
{
  return false;
}

//=================================================================================================

bool BRep_PointRepresentation::IsPointOnSurface(const occ::handle<Geom_Surface>&,
                                                const TopLoc_Location&) const
{
  return false;
}

//=================================================================================================

double BRep_PointRepresentation::Parameter2() const
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

void BRep_PointRepresentation::Parameter2(const double)
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

const occ::handle<Geom_Curve>& BRep_PointRepresentation::Curve() const
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

void BRep_PointRepresentation::Curve(const occ::handle<Geom_Curve>&)
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

const occ::handle<Geom2d_Curve>& BRep_PointRepresentation::PCurve() const
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

void BRep_PointRepresentation::PCurve(const occ::handle<Geom2d_Curve>&)
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

const occ::handle<Geom_Surface>& BRep_PointRepresentation::Surface() const
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

void BRep_PointRepresentation::Surface(const occ::handle<Geom_Surface>&)
{
  throw Standard_DomainError("BRep_PointRepresentation");
}

//=================================================================================================

void BRep_PointRepresentation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myLocation)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myParameter)
}
