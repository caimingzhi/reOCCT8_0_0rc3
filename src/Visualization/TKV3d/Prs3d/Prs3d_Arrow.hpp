#pragma once


#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Prs3d_Presentation.hpp>

class gp_Ax1;
class gp_Pnt;
class gp_Dir;

//! Provides class methods to draw an arrow at a given location, along a given direction and using a
//! given angle.
class Prs3d_Arrow
{
public:
  DEFINE_STANDARD_ALLOC

  //! Defines the representation of the arrow as shaded triangulation.
  //! @param theAxis       axis definition (arrow origin and direction)
  //! @param theTubeRadius tube (cylinder) radius
  //! @param theAxisLength overall arrow length (cylinder + cone)
  //! @param theConeRadius cone radius (arrow tip)
  //! @param theConeLength cone length (arrow tip)
  //! @param theNbFacettes tessellation quality for each part
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfTriangles> DrawShaded(
    const gp_Ax1& theAxis,
    const double  theTubeRadius,
    const double  theAxisLength,
    const double  theConeRadius,
    const double  theConeLength,
    const int     theNbFacettes);

  //! Defines the representation of the arrow as a container of segments.
  //! @param theLocation   location of the arrow tip
  //! @param theDir        direction of the arrow
  //! @param theAngle      angle of opening of the arrow head
  //! @param theLength     length of the arrow (from the tip)
  //! @param theNbSegments count of points on polyline where location is connected
  Standard_EXPORT static occ::handle<Graphic3d_ArrayOfSegments> DrawSegments(
    const gp_Pnt& theLocation,
    const gp_Dir& theDir,
    const double  theAngle,
    const double  theLength,
    const int     theNbSegments);

  //! Defines the representation of the arrow.
  //! Note that this method does NOT assign any presentation aspects to the primitives group!
  //! @param theGroup     presentation group to add primitives
  //! @param theLocation  location of the arrow tip
  //! @param theDirection direction of the arrow
  //! @param theAngle     angle of opening of the arrow head
  //! @param theLength    length of the arrow (from the tip)
  Standard_EXPORT static void Draw(const occ::handle<Graphic3d_Group>& theGroup,
                                   const gp_Pnt&                       theLocation,
                                   const gp_Dir&                       theDirection,
                                   const double                        theAngle,
                                   const double                        theLength);
};

