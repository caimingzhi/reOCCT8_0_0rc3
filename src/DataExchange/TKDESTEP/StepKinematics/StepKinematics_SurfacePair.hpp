#pragma once

#include <Standard.hpp>
#include <StepKinematics_HighOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Surface.hpp>

class StepKinematics_SurfacePair : public StepKinematics_HighOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_SurfacePair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Surface>&              theSurface1,
    const occ::handle<StepGeom_Surface>&              theSurface2,
    const bool                                        theOrientation);

  Standard_EXPORT occ::handle<StepGeom_Surface> Surface1() const;

  Standard_EXPORT void SetSurface1(const occ::handle<StepGeom_Surface>& theSurface1);

  Standard_EXPORT occ::handle<StepGeom_Surface> Surface2() const;

  Standard_EXPORT void SetSurface2(const occ::handle<StepGeom_Surface>& theSurface2);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetOrientation(const bool theOrientation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_SurfacePair, StepKinematics_HighOrderKinematicPair)

private:
  occ::handle<StepGeom_Surface> mySurface1;
  occ::handle<StepGeom_Surface> mySurface2;
  bool                          myOrientation;
};
