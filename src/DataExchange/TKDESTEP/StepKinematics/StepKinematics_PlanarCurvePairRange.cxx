// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PlanarCurvePairRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PlanarCurvePairRange, StepKinematics_PlanarCurvePair)

//=================================================================================================

StepKinematics_PlanarCurvePairRange::StepKinematics_PlanarCurvePairRange() = default;

//=================================================================================================

void StepKinematics_PlanarCurvePairRange::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const occ::handle<StepGeom_Curve>&                thePlanarCurvePair_Curve1,
  const occ::handle<StepGeom_Curve>&                thePlanarCurvePair_Curve2,
  const bool                                        thePlanarCurvePair_Orientation,
  const occ::handle<StepGeom_TrimmedCurve>&         theRangeOnCurve1,
  const occ::handle<StepGeom_TrimmedCurve>&         theRangeOnCurve2)
{
  StepKinematics_PlanarCurvePair::Init(theRepresentationItem_Name,
                                       theItemDefinedTransformation_Name,
                                       hasItemDefinedTransformation_Description,
                                       theItemDefinedTransformation_Description,
                                       theItemDefinedTransformation_TransformItem1,
                                       theItemDefinedTransformation_TransformItem2,
                                       theKinematicPair_Joint,
                                       thePlanarCurvePair_Curve1,
                                       thePlanarCurvePair_Curve2,
                                       thePlanarCurvePair_Orientation);

  myRangeOnCurve1 = theRangeOnCurve1;

  myRangeOnCurve2 = theRangeOnCurve2;
}

//=================================================================================================

occ::handle<StepGeom_TrimmedCurve> StepKinematics_PlanarCurvePairRange::RangeOnCurve1() const
{
  return myRangeOnCurve1;
}

//=================================================================================================

void StepKinematics_PlanarCurvePairRange::SetRangeOnCurve1(
  const occ::handle<StepGeom_TrimmedCurve>& theRangeOnCurve1)
{
  myRangeOnCurve1 = theRangeOnCurve1;
}

//=================================================================================================

occ::handle<StepGeom_TrimmedCurve> StepKinematics_PlanarCurvePairRange::RangeOnCurve2() const
{
  return myRangeOnCurve2;
}

//=================================================================================================

void StepKinematics_PlanarCurvePairRange::SetRangeOnCurve2(
  const occ::handle<StepGeom_TrimmedCurve>& theRangeOnCurve2)
{
  myRangeOnCurve2 = theRangeOnCurve2;
}
