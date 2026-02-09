#include <AIS_InteractiveObject.hpp>

#include <AIS_InteractiveContext.hpp>
#include <Graphic3d_CStructure.hpp>
#include <Graphic3d_Group.hpp>
#include <Graphic3d_Structure.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_PointAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Prs3d_TextAspect.hpp>
#include <PrsMgr_PresentationManager.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_InteractiveObject, SelectMgr_SelectableObject)

AIS_InteractiveObject::AIS_InteractiveObject(
  const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d)
    : SelectMgr_SelectableObject(aTypeOfPresentation3d),
      myCTXPtr(nullptr)
{
}

void AIS_InteractiveObject::Redisplay(const bool AllModes)
{
  if (myCTXPtr == nullptr)
    return;

  myCTXPtr->Redisplay(this, false, AllModes);
}

bool AIS_InteractiveObject::ProcessDragging(const occ::handle<AIS_InteractiveContext>&,
                                            const occ::handle<V3d_View>&,
                                            const occ::handle<SelectMgr_EntityOwner>&,
                                            const NCollection_Vec2<int>&,
                                            const NCollection_Vec2<int>&,
                                            const AIS_DragAction)
{
  return false;
}

occ::handle<AIS_InteractiveContext> AIS_InteractiveObject::GetContext() const
{
  return myCTXPtr;
}

void AIS_InteractiveObject::SetContext(const occ::handle<AIS_InteractiveContext>& theCtx)
{
  if (myCTXPtr == theCtx.get())
  {
    return;
  }

  myCTXPtr = theCtx.get();
  if (!theCtx.IsNull())
  {
    myDrawer->Link(theCtx->DefaultDrawer());
  }
}

void AIS_InteractiveObject::SetDisplayStatus(PrsMgr_DisplayStatus theStatus)
{
  myDisplayStatus = theStatus;
}

bool AIS_InteractiveObject::HasPresentation() const
{
  return HasInteractiveContext()
         && myCTXPtr->MainPrsMgr()->HasPresentation(this, myDrawer->DisplayMode());
}

occ::handle<Prs3d_Presentation> AIS_InteractiveObject::Presentation() const
{
  if (!HasInteractiveContext())
  {
    return occ::handle<Prs3d_Presentation>();
  }

  occ::handle<PrsMgr_Presentation> aPrs =
    myCTXPtr->MainPrsMgr()->Presentation(this, myDrawer->DisplayMode(), false);
  return aPrs;
}

void AIS_InteractiveObject::SetAspect(const occ::handle<Prs3d_BasicAspect>& theAspect)
{

  if (!HasPresentation())
  {
    return;
  }

  occ::handle<Prs3d_Presentation> aPrs = Presentation();
  if (aPrs->Groups().IsEmpty())
  {
    return;
  }
  const occ::handle<Graphic3d_Group>& aGroup = aPrs->Groups().Last();
  if (occ::handle<Prs3d_ShadingAspect> aShadingAspect =
        occ::down_cast<Prs3d_ShadingAspect>(theAspect))
  {
    aGroup->SetGroupPrimitivesAspect(aShadingAspect->Aspect());
  }
  else if (occ::handle<Prs3d_LineAspect> aLineAspect = occ::down_cast<Prs3d_LineAspect>(theAspect))
  {
    aGroup->SetGroupPrimitivesAspect(aLineAspect->Aspect());
  }
  else if (occ::handle<Prs3d_PointAspect> aPointAspect =
             occ::down_cast<Prs3d_PointAspect>(theAspect))
  {
    aGroup->SetGroupPrimitivesAspect(aPointAspect->Aspect());
  }
  else if (occ::handle<Prs3d_TextAspect> aTextAspect = occ::down_cast<Prs3d_TextAspect>(theAspect))
  {
    aGroup->SetGroupPrimitivesAspect(aTextAspect->Aspect());
  }
}

void AIS_InteractiveObject::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, SelectMgr_SelectableObject)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myCTXPtr)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myOwner)
}
