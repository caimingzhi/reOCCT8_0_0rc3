#pragma once

#include <Select3D_SensitiveEntity.hpp>
#include <SelectMgr_SelectingVolumeManager.hpp>

class Select3D_SensitiveSegment : public Select3D_SensitiveEntity
{
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitiveSegment, Select3D_SensitiveEntity)
public:
  Standard_EXPORT Select3D_SensitiveSegment(const occ::handle<SelectMgr_EntityOwner>& theOwnerId,
                                            const gp_Pnt&                             theFirstPnt,
                                            const gp_Pnt&                             theLastPnt);

  void SetStartPoint(const gp_Pnt& thePnt) { myStart = thePnt; }

  void SetEndPoint(const gp_Pnt& thePnt) { myEnd = thePnt; }

  const gp_Pnt& StartPoint() const { return myStart; }

  const gp_Pnt& EndPoint() const { return myEnd; }

  Standard_EXPORT int NbSubElements() const override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT gp_Pnt CenterOfGeometry() const override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  bool ToBuildBVH() const override { return false; }

public:
  void StartPoint(const gp_Pnt& thePnt) { myStart = thePnt; }

  void EndPoint(const gp_Pnt& thePnt) { myEnd = thePnt; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  gp_Pnt myStart;
  gp_Pnt myEnd;
};
