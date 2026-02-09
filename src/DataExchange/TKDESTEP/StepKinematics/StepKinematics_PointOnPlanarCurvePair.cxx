

#include <StepKinematics_PointOnPlanarCurvePair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PointOnPlanarCurvePair,
                           StepKinematics_HighOrderKinematicPair)

StepKinematics_PointOnPlanarCurvePair::StepKinematics_PointOnPlanarCurvePair() = default;

void StepKinematics_PointOnPlanarCurvePair::Init(
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

occ::handle<StepGeom_Curve> StepKinematics_PointOnPlanarCurvePair::PairCurve() const
{
  return myPairCurve;
}

void StepKinematics_PointOnPlanarCurvePair::SetPairCurve(
  const occ::handle<StepGeom_Curve>& thePairCurve)
{
  myPairCurve = thePairCurve;
}

bool StepKinematics_PointOnPlanarCurvePair::Orientation() const
{
  return myOrientation;
}

void StepKinematics_PointOnPlanarCurvePair::SetOrientation(const bool theOrientation)
{
  myOrientation = theOrientation;
}
