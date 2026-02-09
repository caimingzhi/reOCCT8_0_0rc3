#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopLoc_Location.hpp>
class Geom_Surface;
class TopoDS_Shape;

class BRepLib_FindSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_FindSurface();

  Standard_EXPORT BRepLib_FindSurface(const TopoDS_Shape& S,
                                      const double        Tol        = -1,
                                      const bool          OnlyPlane  = false,
                                      const bool          OnlyClosed = false);

  Standard_EXPORT void Init(const TopoDS_Shape& S,
                            const double        Tol        = -1,
                            const bool          OnlyPlane  = false,
                            const bool          OnlyClosed = false);

  Standard_EXPORT bool Found() const;

  Standard_EXPORT occ::handle<Geom_Surface> Surface() const;

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT double ToleranceReached() const;

  Standard_EXPORT bool Existed() const;

  Standard_EXPORT TopLoc_Location Location() const;

private:
  occ::handle<Geom_Surface> mySurface;
  double                    myTolerance;
  double                    myTolReached;
  bool                      isExisted;
  TopLoc_Location           myLocation;
};
