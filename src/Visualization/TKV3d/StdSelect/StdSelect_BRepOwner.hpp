#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <PrsMgr_PresentationManager.hpp>
class StdSelect_Shape;
class SelectMgr_SelectableObject;
class PrsMgr_PresentationManager;
class TopLoc_Location;

class StdSelect_BRepOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(StdSelect_BRepOwner, SelectMgr_EntityOwner)
public:
  Standard_EXPORT StdSelect_BRepOwner(const int aPriority);

  Standard_EXPORT StdSelect_BRepOwner(const TopoDS_Shape& aShape,
                                      const int           aPriority              = 0,
                                      const bool          ComesFromDecomposition = false);

  Standard_EXPORT StdSelect_BRepOwner(const TopoDS_Shape&                            aShape,
                                      const occ::handle<SelectMgr_SelectableObject>& theOrigin,
                                      const int                                      aPriority = 0,
                                      const bool FromDecomposition = false);

  bool HasShape() const { return !myShape.IsNull(); }

  const TopoDS_Shape& Shape() const { return myShape; }

  bool HasHilightMode() const { return myCurMode == -1; }

  void SetHilightMode(const int theMode) { myCurMode = theMode; }

  void ResetHilightMode() { myCurMode = -1; }

  int HilightMode() const { return myCurMode; }

  Standard_EXPORT bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& aPM,
                                   const int aMode = 0) const override;

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT void Unhilight(const occ::handle<PrsMgr_PresentationManager>& aPM,
                                 const int                                      aMode = 0) override;

  Standard_EXPORT void Clear(const occ::handle<PrsMgr_PresentationManager>& aPM,
                             const int                                      aMode = 0) override;

  Standard_EXPORT void SetLocation(const TopLoc_Location& aLoc) override;

  Standard_EXPORT void UpdateHighlightTrsf(
    const occ::handle<V3d_Viewer>&                 theViewer,
    const occ::handle<PrsMgr_PresentationManager>& theManager,
    const int                                      theDispMode) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  TopoDS_Shape                 myShape;
  occ::handle<StdSelect_Shape> myPrsSh;
  int                          myCurMode;
};
