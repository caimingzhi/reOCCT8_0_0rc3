#pragma once

#include <Standard_Integer.hpp>
#include <Aspect_Grid.hpp>

class Aspect_CircularGrid : public Aspect_Grid
{
  DEFINE_STANDARD_RTTIEXT(Aspect_CircularGrid, Aspect_Grid)
public:
  //! creates a new grid. By default this grid is not
  //! active.
  Standard_EXPORT Aspect_CircularGrid(const double aRadiusStep,
                                      const int    aDivisionNumber,
                                      const double XOrigin        = 0,
                                      const double anYOrigin      = 0,
                                      const double aRotationAngle = 0);

  //! defines the x step of the grid.
  Standard_EXPORT void SetRadiusStep(const double aStep);

  //! defines the step of the grid.
  Standard_EXPORT void SetDivisionNumber(const int aNumber);

  Standard_EXPORT void SetGridValues(const double XOrigin,
                                     const double YOrigin,
                                     const double RadiusStep,
                                     const int    DivisionNumber,
                                     const double RotationAngle);

  //! returns the point of the grid the closest to the point X,Y
  Standard_EXPORT void Compute(const double X,
                               const double Y,
                               double&      gridX,
                               double&      gridY) const override;

  //! returns the x step of the grid.
  Standard_EXPORT double RadiusStep() const;

  //! returns the x step of the grid.
  Standard_EXPORT int DivisionNumber() const;

  Standard_EXPORT void Init() override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  double myRadiusStep;
  int    myDivisionNumber;
  double myAlpha;
  double myA1;
  double myB1;
};
