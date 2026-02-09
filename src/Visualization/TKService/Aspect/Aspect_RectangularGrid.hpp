#pragma once

#include <Standard.hpp>

#include <Aspect_Grid.hpp>

class Aspect_RectangularGrid : public Aspect_Grid
{
  DEFINE_STANDARD_RTTIEXT(Aspect_RectangularGrid, Aspect_Grid)
public:
  Standard_EXPORT Aspect_RectangularGrid(const double aXStep,
                                         const double aYStep,
                                         const double anXOrigin      = 0,
                                         const double anYOrigin      = 0,
                                         const double aFirstAngle    = 0,
                                         const double aSecondAngle   = 0,
                                         const double aRotationAngle = 0);

  Standard_EXPORT void SetXStep(const double aStep);

  Standard_EXPORT void SetYStep(const double aStep);

  Standard_EXPORT void SetAngle(const double anAngle1, const double anAngle2);

  Standard_EXPORT void SetGridValues(const double XOrigin,
                                     const double YOrigin,
                                     const double XStep,
                                     const double YStep,
                                     const double RotationAngle);

  Standard_EXPORT void Compute(const double X,
                               const double Y,
                               double&      gridX,
                               double&      gridY) const override;

  Standard_EXPORT double XStep() const;

  Standard_EXPORT double YStep() const;

  Standard_EXPORT double FirstAngle() const;

  Standard_EXPORT double SecondAngle() const;

  Standard_EXPORT void Init() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Standard_EXPORT bool CheckAngle(const double alpha, const double beta) const;

private:
  double myXStep;
  double myYStep;
  double myFirstAngle;
  double mySecondAngle;
  double a1;
  double b1;
  double c1;
  double a2;
  double b2;
  double c2;
};
