#pragma once

#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Ax1;
class gp_Pnt;
class gp_Dir;

class Prs3d_Arrow
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> DrawShaded(
    const gp_Ax1& theAxis,
    const double  theTubeRadius,
    const double  theAxisLength,
    const double  theConeRadius,
    const double  theConeLength,
    const int     theNbFacettes);

  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfSegments> DrawSegments(
    const gp_Pnt& theLocation,
    const gp_Dir& theDir,
    const double  theAngle,
    const double  theLength,
    const int     theNbSegments);

  Standard_EXPORT static void Draw(const occ::handle<Graphic3d_Group>& theGroup,
                                   const gp_Pnt&                       theLocation,
                                   const gp_Dir&                       theDirection,
                                   const double                        theAngle,
                                   const double                        theLength);
};
