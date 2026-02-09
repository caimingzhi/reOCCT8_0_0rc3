#pragma once

#include <MeshVS_EntityType.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <PrsMgr_PresentationManager.hpp>
class PrsMgr_PresentationManager;

class MeshVS_MeshEntityOwner : public SelectMgr_EntityOwner
{

public:
  Standard_EXPORT MeshVS_MeshEntityOwner(const SelectMgr_SelectableObject* SelObj,
                                         const int                         ID,
                                         void* const                       MeshEntity,
                                         const MeshVS_EntityType&          Type,
                                         const int                         Priority = 0,
                                         const bool                        IsGroup  = false);

  Standard_EXPORT void* Owner() const;

  Standard_EXPORT MeshVS_EntityType Type() const;

  Standard_EXPORT int ID() const;

  Standard_EXPORT bool IsGroup() const;

  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& PM,
                                   const int Mode = 0) const override;

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& PM,
                                 const int                                      Mode = 0) override;

  Standard_EXPORT void Clear(const occ::handle<PrsMgr_PresentationManager>& PM,
                             const int                                      Mode = 0) override;

  DEFINE_STANDARD_RTTIEXT(MeshVS_MeshEntityOwner, SelectMgr_EntityOwner)

private:
  void*             myAddr;
  MeshVS_EntityType myType;
  int               myID;
  bool              myIsGroup;
};
