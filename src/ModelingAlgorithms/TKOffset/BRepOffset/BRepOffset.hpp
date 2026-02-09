#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepOffset_Status.hpp>

class Geom_Surface;
class TopoDS_Face;

class BRepOffset
{
public:
  Standard_EXPORT static occ::handle<Geom_Surface> Surface(const occ::handle<Geom_Surface>& Surface,
                                                           const double                     Offset,
                                                           BRepOffset_Status& theStatus,
                                                           bool               allowC0 = false);

  Standard_EXPORT static occ::handle<Geom_Surface> CollapseSingularities(
    const occ::handle<Geom_Surface>& theSurface,
    const TopoDS_Face&               theFace,
    double                           thePrecision);
};
