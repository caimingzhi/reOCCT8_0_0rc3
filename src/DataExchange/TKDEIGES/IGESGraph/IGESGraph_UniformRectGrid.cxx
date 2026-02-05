#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_XY.hpp>
#include <IGESGraph_UniformRectGrid.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_UniformRectGrid, IGESData_IGESEntity)

IGESGraph_UniformRectGrid::IGESGraph_UniformRectGrid() = default;

void IGESGraph_UniformRectGrid::Init(const int    nbProps,
                                     const int    finite,
                                     const int    line,
                                     const int    weighted,
                                     const gp_XY& aGridPoint,
                                     const gp_XY& aGridSpacing,
                                     const int    pointsX,
                                     const int    pointsY)
{
  theNbPropertyValues = nbProps;
  isItFinite          = finite;
  isItLine            = line;
  isItWeighted        = weighted;
  theGridPoint        = aGridPoint;
  theGridSpacing      = aGridSpacing;
  theNbPointsX        = pointsX;
  theNbPointsY        = pointsY;
  InitTypeAndForm(406, 22);
}

int IGESGraph_UniformRectGrid::NbPropertyValues() const
{
  return theNbPropertyValues;
}

bool IGESGraph_UniformRectGrid::IsFinite() const
{
  return (isItFinite == 1);
}

bool IGESGraph_UniformRectGrid::IsLine() const
{
  return (isItLine == 1);
}

bool IGESGraph_UniformRectGrid::IsWeighted() const
{
  return (isItWeighted == 0);
}

gp_Pnt2d IGESGraph_UniformRectGrid::GridPoint() const
{
  return (gp_Pnt2d(theGridPoint));
}

gp_Vec2d IGESGraph_UniformRectGrid::GridSpacing() const
{
  return (gp_Vec2d(theGridSpacing));
}

int IGESGraph_UniformRectGrid::NbPointsX() const
{
  return theNbPointsX;
}

int IGESGraph_UniformRectGrid::NbPointsY() const
{
  return theNbPointsY;
}
