#include <Select3D_SensitiveCircle.hpp>

#include <gp_Ax3.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Select3D_SensitiveCircle, Select3D_SensitiveEntity)

//=======================================================================
// function : Select3D_SensitiveCircle (constructor)
// purpose  : Definition of a sensitive circle
//=======================================================================
Select3D_SensitiveCircle::Select3D_SensitiveCircle(
  const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
  const gp_Circ&                            theCircle,
  const bool                                theIsFilled)
    : Select3D_SensitiveEntity(theOwnerId)
{
  myRadius = theCircle.Radius();
  myTrsf.SetTransformation(theCircle.Position(), gp::XOY());

  mySensType = theIsFilled ? Select3D_TOS_INTERIOR : Select3D_TOS_BOUNDARY;
  if (mySensType == Select3D_TOS_BOUNDARY)
  {
    SetSensitivityFactor(6);
  }
}

//=======================================================================
// function : Matches
// purpose  : Checks whether the circle overlaps current selecting volume
//=======================================================================
bool Select3D_SensitiveCircle::Matches(SelectBasics_SelectingVolumeManager& theMgr,
                                       SelectBasics_PickResult&             thePickResult)
{
  const bool aIsFilled = mySensType == Select3D_TOS_INTERIOR;

  if (theMgr.GetActiveSelectionType() != SelectMgr_SelectionType_Point)
  {
    if (!theMgr.IsOverlapAllowed())
    {
      bool isInside = true;
      return theMgr.OverlapsCircle(myRadius, myTrsf, aIsFilled, &isInside) && isInside;
    }
    else
    {
      return theMgr.OverlapsCircle(myRadius, myTrsf, aIsFilled, nullptr);
    }
  }
  if (!theMgr.OverlapsCircle(myRadius, myTrsf, aIsFilled, thePickResult))
  {
    return false;
  }

  thePickResult.SetDistToGeomCenter(theMgr.DistToGeometryCenter(CenterOfGeometry()));

  return true;
}

//=================================================================================================

occ::handle<Select3D_SensitiveEntity> Select3D_SensitiveCircle::GetConnected()
{
  bool                                  anIsFilled = mySensType == Select3D_TOS_INTERIOR;
  occ::handle<Select3D_SensitiveEntity> aNewEntity =
    new Select3D_SensitiveCircle(myOwnerId, Circle(), anIsFilled);
  return aNewEntity;
}

//=================================================================================================

Select3D_BndBox3d Select3D_SensitiveCircle::BoundingBox()
{
  NCollection_Mat4<double> aTrsf;
  myTrsf.GetMat4(aTrsf);

  Select3D_BndBox3d aBox(NCollection_Vec3<double>(-myRadius, -myRadius, 0),
                         NCollection_Vec3<double>(myRadius, myRadius, 0));
  aBox.Transform(aTrsf);

  return aBox;
}

//=================================================================================================

gp_Pnt Select3D_SensitiveCircle::CenterOfGeometry() const
{
  return gp_Pnt(myTrsf.TranslationPart());
}
