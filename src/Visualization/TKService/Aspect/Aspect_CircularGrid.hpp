#pragma once

#include <Standard_Integer.hpp>
#include <Aspect_Grid.hpp>

class Aspect_CircularGrid : public Aspect_Grid
{
  DEFINE_STANDARD_RTTIEXT(Aspect_CircularGrid, Aspect_Grid)
public:
  Standard_EXPORT Aspect_CircularGrid(const double aRadiusStep,
                                      const int    aDivisionNumber,
                                      const double XOrigin        = 0,
                                      const double anYOrigin      = 0,
                                      const double aRotationAngle = 0);

  Standard_EXPORT void SetRadiusStep(const double aStep);

  Standard_EXPORT void SetDivisionNumber(const int aNumber);

  Standard_EXPORT void SetGridValues(const double XOrigin,
                                     const double YOrigin,
                                     const double RadiusStep,
                                     const int    DivisionNumber,
                                     const double RotationAngle);

  Standard_EXPORT void Compute(const double X,
                               const double Y,
                               double&      gridX,
                               double&      gridY) const override;

  Standard_EXPORT double RadiusStep() const;

  Standard_EXPORT int DivisionNumber() const;

  Standard_EXPORT void Init() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  double myRadiusStep;
  int    myDivisionNumber;
  double myAlpha;
  double myA1;
  double myB1;
};
