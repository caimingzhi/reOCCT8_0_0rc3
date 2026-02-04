#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt2d;
class gp_Vec2d;

//! defines IGESUniformRectGrid, Type <406> Form <22>
//! in package IGESGraph
//!
//! Stores sufficient information for the creation of
//! a uniform rectangular grid within a drawing
class IGESGraph_UniformRectGrid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_UniformRectGrid();

  //! This method is used to set the fields of the class
  //! UniformRectGrid
  //! - nbProps      : Number of property values (NP = 9)
  //! - finite       : Finite/Infinite grid flag
  //! - line         : Line/Point grid flag
  //! - weighted     : Weighted/Unweighted grid flag
  //! - aGridPoint   : Point on the grid
  //! - aGridSpacing : Grid spacing
  //! - pointsX      : No. of points/lines in X Direction
  //! - pointsY      : No. of points/lines in Y Direction
  Standard_EXPORT void Init(const int    nbProps,
                            const int    finite,
                            const int    line,
                            const int    weighted,
                            const gp_XY& aGridPoint,
                            const gp_XY& aGridSpacing,
                            const int    pointsX,
                            const int    pointsY);

  //! returns the number of property values in <me>.
  Standard_EXPORT int NbPropertyValues() const;

  //! returns False if <me> is an infinite grid,
  //! True if <me> is a finite grid.
  Standard_EXPORT bool IsFinite() const;

  //! returns False if <me> is a Point grid,
  //! True if <me> is a Line grid.
  Standard_EXPORT bool IsLine() const;

  //! returns False if <me> is a Weighted grid,
  //! True if <me> is not a Weighted grid.
  Standard_EXPORT bool IsWeighted() const;

  //! returns coordinates of lower left corner,
  //! if <me> is a finite grid,
  //! coordinates of an arbitrary point,
  //! if <me> is an infinite grid.
  Standard_EXPORT gp_Pnt2d GridPoint() const;

  //! returns the grid-spacing in drawing coordinates.
  Standard_EXPORT gp_Vec2d GridSpacing() const;

  //! returns the no. of points/lines in X direction
  //! (only applicable if IsFinite() = 1, i.e: a finite grid).
  Standard_EXPORT int NbPointsX() const;

  //! returns the no. of points/lines in Y direction
  //! (only applicable if IsFinite() = 1, i.e: a finite grid).
  Standard_EXPORT int NbPointsY() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_UniformRectGrid, IGESData_IGESEntity)

private:
  int   theNbPropertyValues;
  int   isItFinite;
  int   isItLine;
  int   isItWeighted;
  gp_XY theGridPoint;
  gp_XY theGridSpacing;
  int   theNbPointsX;
  int   theNbPointsY;
};

