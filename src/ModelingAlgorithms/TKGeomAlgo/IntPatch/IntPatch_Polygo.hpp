#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_Polygon2d.hpp>
class gp_Pnt2d;

class IntPatch_Polygo : public Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  double Error() const;

  Standard_EXPORT virtual int NbPoints() const = 0;

  Standard_EXPORT virtual gp_Pnt2d Point(const int Index) const = 0;

  double DeflectionOverEstimation() const override;

  int NbSegments() const override;

  void Segment(const int theIndex, gp_Pnt2d& theBegin, gp_Pnt2d& theEnd) const override;

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT IntPatch_Polygo(const double theError = 0.0);

  double myError;
};

inline double IntPatch_Polygo::Error() const
{
  return myError;
}

inline double IntPatch_Polygo::DeflectionOverEstimation() const
{
  return myError;
}

inline int IntPatch_Polygo::NbSegments() const
{
  return NbPoints() - 1;
}

inline void IntPatch_Polygo::Segment(const int theIndex, gp_Pnt2d& theBegin, gp_Pnt2d& theEnd) const
{
  theBegin = Point(theIndex);
  theEnd   = Point(theIndex + 1);
}
