#pragma once

#include <MeshVS_EntityType.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <PrsMgr_PresentationManager.hpp>
class PrsMgr_PresentationManager;

//! The custom owner. This class provides methods to store owner information:
//! 1) An address of element or node data structure
//! 2) Type of node or element owner assigned
//! 3) ID of node or element owner assigned
class MeshVS_MeshEntityOwner : public SelectMgr_EntityOwner
{

public:
  Standard_EXPORT MeshVS_MeshEntityOwner(const SelectMgr_SelectableObject* SelObj,
                                         const int                         ID,
                                         void* const                       MeshEntity,
                                         const MeshVS_EntityType&          Type,
                                         const int                         Priority = 0,
                                         const bool                        IsGroup  = false);

  //! Returns an address of element or node data structure
  Standard_EXPORT void* Owner() const;

  //! Returns type of element or node data structure
  Standard_EXPORT MeshVS_EntityType Type() const;

  //! Returns ID of element or node data structure
  Standard_EXPORT int ID() const;

  //! Returns true if owner represents group of nodes or elements
  Standard_EXPORT bool IsGroup() const;

  //! Returns true if owner is hilighted
  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& PM,
                                   const int Mode = 0) const override;

  //! Hilights owner with the certain color
  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  //! Strip hilight of owner
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
