

#include <Standard_Type.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepGeom_SurfacePatch.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_SurfacePatch, Standard_Transient)

StepGeom_SurfacePatch::StepGeom_SurfacePatch() = default;

void StepGeom_SurfacePatch::Init(const occ::handle<StepGeom_BoundedSurface>& aParentSurface,
                                 const StepGeom_TransitionCode               aUTransition,
                                 const StepGeom_TransitionCode               aVTransition,
                                 const bool                                  aUSense,
                                 const bool                                  aVSense)
{

  parentSurface = aParentSurface;
  uTransition   = aUTransition;
  vTransition   = aVTransition;
  uSense        = aUSense;
  vSense        = aVSense;
}

void StepGeom_SurfacePatch::SetParentSurface(
  const occ::handle<StepGeom_BoundedSurface>& aParentSurface)
{
  parentSurface = aParentSurface;
}

occ::handle<StepGeom_BoundedSurface> StepGeom_SurfacePatch::ParentSurface() const
{
  return parentSurface;
}

void StepGeom_SurfacePatch::SetUTransition(const StepGeom_TransitionCode aUTransition)
{
  uTransition = aUTransition;
}

StepGeom_TransitionCode StepGeom_SurfacePatch::UTransition() const
{
  return uTransition;
}

void StepGeom_SurfacePatch::SetVTransition(const StepGeom_TransitionCode aVTransition)
{
  vTransition = aVTransition;
}

StepGeom_TransitionCode StepGeom_SurfacePatch::VTransition() const
{
  return vTransition;
}

void StepGeom_SurfacePatch::SetUSense(const bool aUSense)
{
  uSense = aUSense;
}

bool StepGeom_SurfacePatch::USense() const
{
  return uSense;
}

void StepGeom_SurfacePatch::SetVSense(const bool aVSense)
{
  vSense = aVSense;
}

bool StepGeom_SurfacePatch::VSense() const
{
  return vSense;
}
