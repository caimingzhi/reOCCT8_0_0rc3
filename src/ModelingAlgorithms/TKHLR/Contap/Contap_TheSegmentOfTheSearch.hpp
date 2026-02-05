#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Contap_ThePathPointOfTheSearch.hpp>

class Standard_DomainError;
class Adaptor3d_HVertex;
class Contap_ThePathPointOfTheSearch;

class Contap_TheSegmentOfTheSearch
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT Contap_TheSegmentOfTheSearch();

  //! Defines the concerned arc.
  void SetValue(const occ::handle<Adaptor2d_Curve2d>& A);

  //! Defines the first point or the last point,
  //! depending on the value of the boolean First.
  Standard_EXPORT void SetLimitPoint(const Contap_ThePathPointOfTheSearch& V, const bool First);

  //! Returns the geometric curve on the surface 's domain
  //! which is solution.
  const occ::handle<Adaptor2d_Curve2d>& Curve() const;

  //! Returns True if there is a vertex (ThePathPoint) defining
  //! the lowest valid parameter on the arc.
  bool HasFirstPoint() const;

  //! Returns the first point.
  const Contap_ThePathPointOfTheSearch& FirstPoint() const;

  //! Returns True if there is a vertex (ThePathPoint) defining
  //! the greatest valid parameter on the arc.
  bool HasLastPoint() const;

  //! Returns the last point.
  const Contap_ThePathPointOfTheSearch& LastPoint() const;

private:
  occ::handle<Adaptor2d_Curve2d> arc;
  bool                           hasfp;
  Contap_ThePathPointOfTheSearch thefp;
  bool                           haslp;
  Contap_ThePathPointOfTheSearch thelp;
};

//=================================================================================================
// Inline implementations
//=================================================================================================

inline void Contap_TheSegmentOfTheSearch::SetValue(const occ::handle<Adaptor2d_Curve2d>& A)
{
  hasfp = false;
  haslp = false;
  arc   = A;
}

inline const occ::handle<Adaptor2d_Curve2d>& Contap_TheSegmentOfTheSearch::Curve() const
{
  return arc;
}

inline bool Contap_TheSegmentOfTheSearch::HasFirstPoint() const
{
  return hasfp;
}

inline const Contap_ThePathPointOfTheSearch& Contap_TheSegmentOfTheSearch::FirstPoint() const
{
  if (!hasfp)
  {
    throw Standard_DomainError();
  }
  return thefp;
}

inline bool Contap_TheSegmentOfTheSearch::HasLastPoint() const
{
  return haslp;
}

inline const Contap_ThePathPointOfTheSearch& Contap_TheSegmentOfTheSearch::LastPoint() const
{
  if (!haslp)
  {
    throw Standard_DomainError();
  }
  return thelp;
}
