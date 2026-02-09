#pragma once

#include <AIS_KindOfInteractive.hpp>
#include <AIS_DragAction.hpp>
#include <SelectMgr_SelectableObject.hpp>

class AIS_InteractiveContext;
class Prs3d_BasicAspect;
class V3d_View;

class AIS_InteractiveObject : public SelectMgr_SelectableObject
{
  friend class AIS_InteractiveContext;
  DEFINE_STANDARD_RTTIEXT(AIS_InteractiveObject, SelectMgr_SelectableObject)
public:
  virtual AIS_KindOfInteractive Type() const { return AIS_KindOfInteractive_None; }

  virtual int Signature() const { return -1; }

  Standard_EXPORT void Redisplay(const bool AllModes = false);

  bool HasInteractiveContext() const { return myCTXPtr != nullptr; }

  AIS_InteractiveContext* InteractiveContext() const { return myCTXPtr; }

  Standard_EXPORT virtual void SetContext(const occ::handle<AIS_InteractiveContext>& aCtx);

  bool HasOwner() const { return !myOwner.IsNull(); }

  const occ::handle<Standard_Transient>& GetOwner() const { return myOwner; }

  void SetOwner(const occ::handle<Standard_Transient>& theApplicativeEntity)
  {
    myOwner = theApplicativeEntity;
  }

  void ClearOwner() { myOwner.Nullify(); }

  Standard_EXPORT virtual bool ProcessDragging(const occ::handle<AIS_InteractiveContext>& theCtx,
                                               const occ::handle<V3d_View>&               theView,
                                               const occ::handle<SelectMgr_EntityOwner>&  theOwner,
                                               const NCollection_Vec2<int>& theDragFrom,
                                               const NCollection_Vec2<int>& theDragTo,
                                               const AIS_DragAction         theAction);

public:
  Standard_EXPORT occ::handle<AIS_InteractiveContext> GetContext() const;

  Standard_EXPORT bool HasPresentation() const;

  Standard_EXPORT occ::handle<Prs3d_Presentation> Presentation() const;

  Standard_DEPRECATED("Deprecated method, results might be undefined")
  Standard_EXPORT void SetAspect(const occ::handle<Prs3d_BasicAspect>& anAspect);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT AIS_InteractiveObject(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  Standard_EXPORT void SetDisplayStatus(PrsMgr_DisplayStatus theStatus);

protected:
  AIS_InteractiveContext* myCTXPtr;

  occ::handle<Standard_Transient> myOwner;
};
