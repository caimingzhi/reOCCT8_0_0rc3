#pragma once

#include <Geom_Point.hpp>
#include <Prs3d_Point.hpp>
#include <StdPrs_ToolPoint.hpp>

typedef Prs3d_Point<occ::handle<Geom_Point>, StdPrs_ToolPoint> StdPrs_Point;
