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

  Standard_EXPORT Contap_TheSegmentOfTheSearch();

  void SetValue(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT void SetLimitPoint(const Contap_ThePathPointOfTheSearch& V, const bool First);

  const occ::handle<Adaptor2d_Curve2d>& Curve() const;

  bool HasFirstPoint() const;

  const Contap_ThePathPointOfTheSearch& FirstPoint() const;

  bool HasLastPoint() const;

  const Contap_ThePathPointOfTheSearch& LastPoint() const;

private:
  occ::handle<Adaptor2d_Curve2d> arc;
  bool                           hasfp;
  Contap_ThePathPointOfTheSearch thefp;
  bool                           haslp;
  Contap_ThePathPointOfTheSearch thelp;
};

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
