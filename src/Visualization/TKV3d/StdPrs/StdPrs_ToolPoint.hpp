#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Point;

class StdPrs_ToolPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Coord(const occ::handle<Geom_Point>& aPoint,
                                    double&                        X,
                                    double&                        Y,
                                    double&                        Z);
};
