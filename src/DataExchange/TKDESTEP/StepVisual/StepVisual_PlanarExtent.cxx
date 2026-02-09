

#include <StepVisual_PlanarExtent.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_PlanarExtent, StepGeom_GeometricRepresentationItem)

StepVisual_PlanarExtent::StepVisual_PlanarExtent() = default;

void StepVisual_PlanarExtent::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                   const double                                 aSizeInX,
                                   const double                                 aSizeInY)
{

  sizeInX = aSizeInX;
  sizeInY = aSizeInY;

  StepRepr_RepresentationItem::Init(aName);
}

void StepVisual_PlanarExtent::SetSizeInX(const double aSizeInX)
{
  sizeInX = aSizeInX;
}

double StepVisual_PlanarExtent::SizeInX() const
{
  return sizeInX;
}

void StepVisual_PlanarExtent::SetSizeInY(const double aSizeInY)
{
  sizeInY = aSizeInY;
}

double StepVisual_PlanarExtent::SizeInY() const
{
  return sizeInY;
}
