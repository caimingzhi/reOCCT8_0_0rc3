// Created on : Sat May 02 12:41:15 2020

#include <StepKinematics_PointOnSurfacePair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_PointOnSurfacePair, StepKinematics_HighOrderKinematicPair)

//=================================================================================================

StepKinematics_PointOnSurfacePair::StepKinematics_PointOnSurfacePair() = default;

//=================================================================================================

void StepKinematics_PointOnSurfacePair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const occ::handle<StepGeom_Surface>&              thePairSurface)
{
  StepKinematics_HighOrderKinematicPair::Init(theRepresentationItem_Name,
                                              theItemDefinedTransformation_Name,
                                              hasItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_TransformItem1,
                                              theItemDefinedTransformation_TransformItem2,
                                              theKinematicPair_Joint);

  myPairSurface = thePairSurface;
}

//=================================================================================================

occ::handle<StepGeom_Surface> StepKinematics_PointOnSurfacePair::PairSurface() const
{
  return myPairSurface;
}

//=================================================================================================

void StepKinematics_PointOnSurfacePair::SetPairSurface(
  const occ::handle<StepGeom_Surface>& thePairSurface)
{
  myPairSurface = thePairSurface;
}
