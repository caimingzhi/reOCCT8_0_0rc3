#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt2d;
class gp_Vec2d;

class IGESGraph_UniformRectGrid : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_UniformRectGrid();

  Standard_EXPORT void Init(const int    nbProps,
                            const int    finite,
                            const int    line,
                            const int    weighted,
                            const gp_XY& aGridPoint,
                            const gp_XY& aGridSpacing,
                            const int    pointsX,
                            const int    pointsY);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT bool IsFinite() const;

  Standard_EXPORT bool IsLine() const;

  Standard_EXPORT bool IsWeighted() const;

  Standard_EXPORT gp_Pnt2d GridPoint() const;

  Standard_EXPORT gp_Vec2d GridSpacing() const;

  Standard_EXPORT int NbPointsX() const;

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
