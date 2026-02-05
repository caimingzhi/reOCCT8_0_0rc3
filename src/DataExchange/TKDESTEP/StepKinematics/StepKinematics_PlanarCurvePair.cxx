// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PlanarCurvePair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PlanarCurvePair, StepKinematics_HighOrderKinematicPair)

//=================================================================================================

StepKinematics_PlanarCurvePair::StepKinematics_PlanarCurvePair() = default;

//=================================================================================================

void StepKinematics_PlanarCurvePair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const occ::handle<StepGeom_Curve>&                theCurve1,
  const occ::handle<StepGeom_Curve>&                theCurve2,
  const bool                                        theOrientation)
{
  StepKinematics_HighOrderKinematicPair::Init(theRepresentationItem_Name,
                                              theItemDefinedTransformation_Name,
                                              hasItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_TransformItem1,
                                              theItemDefinedTransformation_TransformItem2,
                                              theKinematicPair_Joint);

  myCurve1 = theCurve1;

  myCurve2 = theCurve2;

  myOrientation = theOrientation;
}

//=================================================================================================

occ::handle<StepGeom_Curve> StepKinematics_PlanarCurvePair::Curve1() const
{
  return myCurve1;
}

//=================================================================================================

void StepKinematics_PlanarCurvePair::SetCurve1(const occ::handle<StepGeom_Curve>& theCurve1)
{
  myCurve1 = theCurve1;
}

//=================================================================================================

occ::handle<StepGeom_Curve> StepKinematics_PlanarCurvePair::Curve2() const
{
  return myCurve2;
}

//=================================================================================================

void StepKinematics_PlanarCurvePair::SetCurve2(const occ::handle<StepGeom_Curve>& theCurve2)
{
  myCurve2 = theCurve2;
}

//=================================================================================================

bool StepKinematics_PlanarCurvePair::Orientation() const
{
  return myOrientation;
}

//=================================================================================================

void StepKinematics_PlanarCurvePair::SetOrientation(const bool theOrientation)
{
  myOrientation = theOrientation;
}
