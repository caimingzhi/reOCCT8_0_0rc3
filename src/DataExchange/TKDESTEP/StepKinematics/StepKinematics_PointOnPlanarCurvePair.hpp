#pragma once

#include <Standard.hpp>
#include <StepKinematics_HighOrderKinematicPair.hpp>

#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepKinematics_KinematicJoint.hpp>
#include <StepGeom_Curve.hpp>

class StepKinematics_PointOnPlanarCurvePair : public StepKinematics_HighOrderKinematicPair
{
public:
  Standard_EXPORT StepKinematics_PointOnPlanarCurvePair();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
    const bool                                        hasItemDefinedTransformation_Description,
    const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
    const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
    const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
    const occ::handle<StepGeom_Curve>&                thePairCurve,
    const bool                                        theOrientation);

  Standard_EXPORT occ::handle<StepGeom_Curve> PairCurve() const;

  Standard_EXPORT void SetPairCurve(const occ::handle<StepGeom_Curve>& thePairCurve);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetOrientation(const bool theOrientation);

  DEFINE_STANDARD_RTTIEXT(StepKinematics_PointOnPlanarCurvePair,
                          StepKinematics_HighOrderKinematicPair)

private:
  occ::handle<StepGeom_Curve> myPairCurve;
  bool                        myOrientation;
};
