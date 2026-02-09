#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Drawable3D.hpp>
class Draw_Display;

class Draw_Grid : public Draw_Drawable3D
{

public:
  Standard_EXPORT Draw_Grid();

  Standard_EXPORT void Steps(const double StepX, const double StepY, const double StepZ);

  double StepX() const;

  double StepY() const;

  double StepZ() const;

  bool IsActive() const;

  Standard_EXPORT void DrawOn(Draw_Display& Out) const override;

  DEFINE_STANDARD_RTTIEXT(Draw_Grid, Draw_Drawable3D)

private:
  double myStepX;
  double myStepY;
  double myStepZ;
  bool   myIsActive;
};

inline double Draw_Grid::StepX() const
{
  return myStepX;
}

inline double Draw_Grid::StepY() const
{
  return myStepY;
}

inline double Draw_Grid::StepZ() const
{
  return myStepZ;
}

inline bool Draw_Grid::IsActive() const
{
  return myIsActive;
}
