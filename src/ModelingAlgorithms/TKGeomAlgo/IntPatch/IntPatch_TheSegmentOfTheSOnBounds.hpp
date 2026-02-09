#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>

class Standard_DomainError;
class Adaptor3d_HVertex;
class IntPatch_ThePathPointOfTheSOnBounds;

class IntPatch_TheSegmentOfTheSOnBounds
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_TheSegmentOfTheSOnBounds();

  void SetValue(const occ::handle<Adaptor2d_Curve2d>& A);

  Standard_EXPORT void SetLimitPoint(const IntPatch_ThePathPointOfTheSOnBounds& V,
                                     const bool                                 First);

  const occ::handle<Adaptor2d_Curve2d>& Curve() const;

  bool HasFirstPoint() const;

  const IntPatch_ThePathPointOfTheSOnBounds& FirstPoint() const;

  bool HasLastPoint() const;

  const IntPatch_ThePathPointOfTheSOnBounds& LastPoint() const;

private:
  occ::handle<Adaptor2d_Curve2d>      arc;
  bool                                hasfp;
  IntPatch_ThePathPointOfTheSOnBounds thefp;
  bool                                haslp;
  IntPatch_ThePathPointOfTheSOnBounds thelp;
};

inline void IntPatch_TheSegmentOfTheSOnBounds::SetValue(const occ::handle<Adaptor2d_Curve2d>& A)
{
  hasfp = false;
  haslp = false;
  arc   = A;
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_TheSegmentOfTheSOnBounds::Curve() const
{
  return arc;
}

inline bool IntPatch_TheSegmentOfTheSOnBounds::HasFirstPoint() const
{
  return hasfp;
}

inline const IntPatch_ThePathPointOfTheSOnBounds& IntPatch_TheSegmentOfTheSOnBounds::FirstPoint()
  const
{
  if (!hasfp)
  {
    throw Standard_DomainError();
  }
  return thefp;
}

inline bool IntPatch_TheSegmentOfTheSOnBounds::HasLastPoint() const
{
  return haslp;
}

inline const IntPatch_ThePathPointOfTheSOnBounds& IntPatch_TheSegmentOfTheSOnBounds::LastPoint()
  const
{
  if (!haslp)
  {
    throw Standard_DomainError();
  }
  return thelp;
}
