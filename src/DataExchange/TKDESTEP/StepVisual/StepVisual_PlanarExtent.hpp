#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepVisual_PlanarExtent : public StepGeom_GeometricRepresentationItem
{

public:
  //! Returns a PlanarExtent
  Standard_EXPORT StepVisual_PlanarExtent();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const double                                 aSizeInX,
                            const double                                 aSizeInY);

  Standard_EXPORT void SetSizeInX(const double aSizeInX);

  Standard_EXPORT double SizeInX() const;

  Standard_EXPORT void SetSizeInY(const double aSizeInY);

  Standard_EXPORT double SizeInY() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_PlanarExtent, StepGeom_GeometricRepresentationItem)

private:
  double sizeInX;
  double sizeInY;
};
