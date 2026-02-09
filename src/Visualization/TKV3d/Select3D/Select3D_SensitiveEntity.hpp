#pragma once

#include <Standard_Transient.hpp>
#include <Select3D_BndBox3d.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>
#include <TopLoc_Location.hpp>

class Graphic3d_TransformPers;
class SelectMgr_EntityOwner;

class Select3D_SensitiveEntity : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveEntity, Standard_Transient)
public:
  const occ::handle<SelectMgr_EntityOwner>& OwnerId() const { return myOwnerId; }

  virtual void Set(const occ::handle<SelectMgr_EntityOwner>& theOwnerId) { myOwnerId = theOwnerId; }

  int SensitivityFactor() const { return mySFactor; }

  void SetSensitivityFactor(const int theNewSens)
  {
    Standard_ASSERT_RAISE(theNewSens >= 0,
                          "Error! Selection sensitivity should not be negative value.");
    mySFactor = theNewSens;
  }

  virtual occ::handle<Select3D_SensitiveEntity> GetConnected()
  {
    return occ::handle<Select3D_SensitiveEntity>();
  }

  virtual bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                       SelectBasics_PickResult&             thePickResult) = 0;

  virtual int NbSubElements() const = 0;

  virtual Select3D_BndBox3d BoundingBox() = 0;

  virtual gp_Pnt CenterOfGeometry() const = 0;

  virtual void BVH() {}

  virtual bool ToBuildBVH() const { return true; }

  virtual void Clear() { Set(occ::handle<SelectMgr_EntityOwner>()); }

  virtual bool HasInitLocation() const { return false; }

  virtual gp_GTrsf InvInitLocation() const { return gp_GTrsf(); }

  const occ::handle<Graphic3d_TransformPers>& TransformPersistence() const { return myTrsfPers; }

  virtual void SetTransformPersistence(const occ::handle<Graphic3d_TransformPers>& theTrsfPers)
  {
    myTrsfPers = theTrsfPers;
  }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT Select3D_SensitiveEntity(const occ::handle<SelectMgr_EntityOwner>& theOwnerId);

protected:
  occ::handle<SelectMgr_EntityOwner>   myOwnerId;
  occ::handle<Graphic3d_TransformPers> myTrsfPers;
  int                                  mySFactor;
};
