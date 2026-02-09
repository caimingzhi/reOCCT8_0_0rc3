#include <MeshVS_Mesh.hpp>
#include <MeshVS_MeshEntityOwner.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MeshVS_MeshEntityOwner, SelectMgr_EntityOwner)

#ifndef MeshVS_PRSBUILDERHXX
  #include <MeshVS_PrsBuilder.hpp>
#endif

MeshVS_MeshEntityOwner::MeshVS_MeshEntityOwner(const SelectMgr_SelectableObject* SelObj,
                                               const int                         ID,
                                               void* const                       MeshEntity,
                                               const MeshVS_EntityType&          Type,
                                               const int                         Priority,
                                               const bool                        IsGroup)
    : SelectMgr_EntityOwner(SelObj, Priority),
      myAddr(MeshEntity),
      myType(Type),
      myID(ID),
      myIsGroup(IsGroup)
{
}

void* MeshVS_MeshEntityOwner::Owner() const
{
  return myAddr;
}

MeshVS_EntityType MeshVS_MeshEntityOwner::Type() const
{
  return myType;
}

bool MeshVS_MeshEntityOwner::IsGroup() const
{
  return myIsGroup;
}

bool MeshVS_MeshEntityOwner::IsHilighted(const occ::handle<PrsMgr_PresentationManager>&,
                                         const int) const
{
  return false;
}

void MeshVS_MeshEntityOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                              const occ::handle<Prs3d_Drawer>& theStyle,
                                              const int)
{
  occ::handle<SelectMgr_SelectableObject> aSelObj;
  if (HasSelectable())
    aSelObj = Selectable();

  if (thePM->IsImmediateModeOn() && aSelObj->IsKind(STANDARD_TYPE(MeshVS_Mesh)))
  {
    occ::handle<MeshVS_Mesh> aMesh = occ::down_cast<MeshVS_Mesh>(aSelObj);
    aMesh->HilightOwnerWithColor(thePM, theStyle, this);
  }
}

void MeshVS_MeshEntityOwner::Unhilight(const occ::handle<PrsMgr_PresentationManager>&, const int) {}

void MeshVS_MeshEntityOwner::Clear(const occ::handle<PrsMgr_PresentationManager>&, const int) {}

int MeshVS_MeshEntityOwner::ID() const
{
  return myID;
}
