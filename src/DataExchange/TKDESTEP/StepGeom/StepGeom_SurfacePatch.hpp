#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_TransitionCode.hpp>
#include <Standard_Transient.hpp>
class StepGeom_BoundedSurface;

class StepGeom_SurfacePatch : public Standard_Transient
{

public:
  //! Returns a SurfacePatch
  Standard_EXPORT StepGeom_SurfacePatch();

  Standard_EXPORT void Init(const occ::handle<StepGeom_BoundedSurface>& aParentSurface,
                            const StepGeom_TransitionCode               aUTransition,
                            const StepGeom_TransitionCode               aVTransition,
                            const bool                                  aUSense,
                            const bool                                  aVSense);

  Standard_EXPORT void SetParentSurface(const occ::handle<StepGeom_BoundedSurface>& aParentSurface);

  Standard_EXPORT occ::handle<StepGeom_BoundedSurface> ParentSurface() const;

  Standard_EXPORT void SetUTransition(const StepGeom_TransitionCode aUTransition);

  Standard_EXPORT StepGeom_TransitionCode UTransition() const;

  Standard_EXPORT void SetVTransition(const StepGeom_TransitionCode aVTransition);

  Standard_EXPORT StepGeom_TransitionCode VTransition() const;

  Standard_EXPORT void SetUSense(const bool aUSense);

  Standard_EXPORT bool USense() const;

  Standard_EXPORT void SetVSense(const bool aVSense);

  Standard_EXPORT bool VSense() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_SurfacePatch, Standard_Transient)

private:
  occ::handle<StepGeom_BoundedSurface> parentSurface;
  StepGeom_TransitionCode              uTransition;
  StepGeom_TransitionCode              vTransition;
  bool                                 uSense;
  bool                                 vSense;
};
