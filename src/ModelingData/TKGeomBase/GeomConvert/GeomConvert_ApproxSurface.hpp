#pragma once

#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Geom_BSplineSurface;
class Geom_Surface;

class GeomConvert_ApproxSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_ApproxSurface(const occ::handle<Geom_Surface>& Surf,
                                            const double                     Tol3d,
                                            const GeomAbs_Shape              UContinuity,
                                            const GeomAbs_Shape              VContinuity,
                                            const int                        MaxDegU,
                                            const int                        MaxDegV,
                                            const int                        MaxSegments,
                                            const int                        PrecisCode);

  Standard_EXPORT GeomConvert_ApproxSurface(const occ::handle<Adaptor3d_Surface>& Surf,
                                            const double                          Tol3d,
                                            const GeomAbs_Shape                   UContinuity,
                                            const GeomAbs_Shape                   VContinuity,
                                            const int                             MaxDegU,
                                            const int                             MaxDegV,
                                            const int                             MaxSegments,
                                            const int                             PrecisCode);

  Standard_EXPORT occ::handle<Geom_BSplineSurface> Surface() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT double MaxError() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Approximate(const occ::handle<Adaptor3d_Surface>& theSurf,
                                   const double                          theTol3d,
                                   const GeomAbs_Shape                   theUContinuity,
                                   const GeomAbs_Shape                   theVContinuity,
                                   const int                             theMaxDegU,
                                   const int                             theMaxDegV,
                                   const int                             theMaxSegments,
                                   const int                             thePrecisCode);

  bool                             myIsDone;
  bool                             myHasResult;
  occ::handle<Geom_BSplineSurface> myBSplSurf;
  double                           myMaxError;
};
