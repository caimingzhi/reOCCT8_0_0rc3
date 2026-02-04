#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <MAT_Side.hpp>
#include <Standard_Integer.hpp>
class Geom2d_Curve;
class Geom2d_TrimmedCurve;

//! Cuts a curve at the extremas of curvature
//! and at the inflections. Constructs a trimmed
//! Curve for each interval.
class MAT2d_CutCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_CutCurve();

  Standard_EXPORT MAT2d_CutCurve(const occ::handle<Geom2d_Curve>& C);

  //! Cuts a curve at the extremas of curvature
  //! and at the inflections.
  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C);

  //! Cuts a curve at the inflections, and at the extremas
  //! of curvature where the concavity is on <aSide>.
  Standard_EXPORT void Perform(const occ::handle<Geom2d_Curve>& C, const MAT_Side aSide);

  //! Cuts a curve at the inflections.
  Standard_EXPORT void PerformInf(const occ::handle<Geom2d_Curve>& C);

  //! Returns True if the curve is not cut.
  Standard_EXPORT bool UnModified() const;

  //! Returns the number of curves.
  //! it's always greatest than 2.
  //!
  //! raises if the Curve is UnModified;
  Standard_EXPORT int NbCurves() const;

  //! Returns the Indexth curve.
  //! raises if Index not in the range [1,NbCurves()]
  Standard_EXPORT occ::handle<Geom2d_TrimmedCurve> Value(const int Index) const;

private:
  NCollection_Sequence<occ::handle<Geom2d_Curve>> theCurves;
};

