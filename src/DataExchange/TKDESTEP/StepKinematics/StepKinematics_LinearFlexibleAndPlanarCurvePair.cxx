

#include <StepKinematics_LinearFlexibleAndPlanarCurvePair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_LinearFlexibleAndPlanarCurvePair,
                           StepKinematics_HighOrderKinematicPair)

StepKinematics_LinearFlexibleAndPlanarCurvePair::StepKinematics_LinearFlexibleAndPlanarCurvePair() =
  default;

void StepKinematics_LinearFlexibleAndPlanarCurvePair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const occ::handle<StepGeom_Curve>&                thePairCurve,
  const bool                                        theOrientation)
{
  StepKinematics_HighOrderKinematicPair::Init(theRepresentationItem_Name,
                                              theItemDefinedTransformation_Name,
                                              hasItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_TransformItem1,
                                              theItemDefinedTransformation_TransformItem2,
                                              theKinematicPair_Joint);

  myPairCurve = thePairCurve;

  myOrientation = theOrientation;
}

occ::handle<StepGeom_Curve> StepKinematics_LinearFlexibleAndPlanarCurvePair::PairCurve() const
{
  return myPairCurve;
}

void StepKinematics_LinearFlexibleAndPlanarCurvePair::SetPairCurve(
  const occ::handle<StepGeom_Curve>& thePairCurve)
{
  myPairCurve = thePairCurve;
}

bool StepKinematics_LinearFlexibleAndPlanarCurvePair::Orientation() const
{
  return myOrientation;
}

void StepKinematics_LinearFlexibleAndPlanarCurvePair::SetOrientation(const bool theOrientation)
{
  myOrientation = theOrientation;
}
