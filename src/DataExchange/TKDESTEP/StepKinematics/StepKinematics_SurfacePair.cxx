// Created on : Sat May 02 12:41:16 2020

#include <StepKinematics_SurfacePair.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepKinematics_SurfacePair, StepKinematics_HighOrderKinematicPair)

//=================================================================================================

StepKinematics_SurfacePair::StepKinematics_SurfacePair() = default;

//=================================================================================================

void StepKinematics_SurfacePair::Init(
  const occ::handle<TCollection_HAsciiString>&      theRepresentationItem_Name,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Name,
  const bool                                        hasItemDefinedTransformation_Description,
  const occ::handle<TCollection_HAsciiString>&      theItemDefinedTransformation_Description,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem1,
  const occ::handle<StepRepr_RepresentationItem>&   theItemDefinedTransformation_TransformItem2,
  const occ::handle<StepKinematics_KinematicJoint>& theKinematicPair_Joint,
  const occ::handle<StepGeom_Surface>&              theSurface1,
  const occ::handle<StepGeom_Surface>&              theSurface2,
  const bool                                        theOrientation)
{
  StepKinematics_HighOrderKinematicPair::Init(theRepresentationItem_Name,
                                              theItemDefinedTransformation_Name,
                                              hasItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_Description,
                                              theItemDefinedTransformation_TransformItem1,
                                              theItemDefinedTransformation_TransformItem2,
                                              theKinematicPair_Joint);

  mySurface1 = theSurface1;

  mySurface2 = theSurface2;

  myOrientation = theOrientation;
}

//=================================================================================================

occ::handle<StepGeom_Surface> StepKinematics_SurfacePair::Surface1() const
{
  return mySurface1;
}

//=================================================================================================

void StepKinematics_SurfacePair::SetSurface1(const occ::handle<StepGeom_Surface>& theSurface1)
{
  mySurface1 = theSurface1;
}

//=================================================================================================

occ::handle<StepGeom_Surface> StepKinematics_SurfacePair::Surface2() const
{
  return mySurface2;
}

//=================================================================================================

void StepKinematics_SurfacePair::SetSurface2(const occ::handle<StepGeom_Surface>& theSurface2)
{
  mySurface2 = theSurface2;
}

//=================================================================================================

bool StepKinematics_SurfacePair::Orientation() const
{
  return myOrientation;
}

//=================================================================================================

void StepKinematics_SurfacePair::SetOrientation(const bool theOrientation)
{
  myOrientation = theOrientation;
}
