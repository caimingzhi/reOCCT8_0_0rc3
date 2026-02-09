#include <StdSelect_BRepOwner.hpp>

#include <Graphic3d_StructureManager.hpp>
#include <Prs3d_Drawer.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <Standard_Type.hpp>
#include <StdSelect_Shape.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdSelect_BRepOwner, SelectMgr_EntityOwner)

StdSelect_BRepOwner::StdSelect_BRepOwner(const int thePriority)
    : SelectMgr_EntityOwner(thePriority),
      myCurMode(0)
{
}

StdSelect_BRepOwner::StdSelect_BRepOwner(const TopoDS_Shape& theShape,
                                         const int           thePriority,
                                         const bool          theComesFromDecomposition)
    : SelectMgr_EntityOwner(thePriority),
      myShape(theShape),
      myCurMode(0)
{
  myFromDecomposition = theComesFromDecomposition;
}

StdSelect_BRepOwner::StdSelect_BRepOwner(const TopoDS_Shape&                            theShape,
                                         const occ::handle<SelectMgr_SelectableObject>& theOrigin,
                                         const int                                      thePriority,
                                         const bool theComesFromDecomposition)
    : SelectMgr_EntityOwner(theOrigin, thePriority),
      myShape(theShape),
      myCurMode(0)
{
  myFromDecomposition = theComesFromDecomposition;
}

bool StdSelect_BRepOwner::IsHilighted(const occ::handle<PrsMgr_PresentationManager>& PM,
                                      const int                                      aMode) const
{
  int M = (aMode < 0) ? myCurMode : aMode;
  if (myPrsSh.IsNull())
    return PM->IsHighlighted(Selectable(), M);
  return PM->IsHighlighted(myPrsSh, M);
}

void StdSelect_BRepOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                           const occ::handle<Prs3d_Drawer>&               theStyle,
                                           const int                                      theMode)
{
  if (!HasSelectable())
  {
    return;
  }

  const int                               aDispMode = (theMode < 0) ? myCurMode : theMode;
  occ::handle<SelectMgr_SelectableObject> aSel      = Selectable();
  const Graphic3d_ZLayerId                aHiLayer =
    theStyle->ZLayer() != Graphic3d_ZLayerId_UNKNOWN ? theStyle->ZLayer() : aSel->ZLayer();
  if (!myFromDecomposition)
  {
    thePM->Color(aSel, theStyle, aDispMode, nullptr, aHiLayer);
    return;
  }

  if (!myPrsSh.IsNull() && myPrsSh->ToBeUpdated(true))
  {
    myPrsSh.Nullify();
  }

  if (myPrsSh.IsNull())
  {
    myPrsSh = new StdSelect_Shape(myShape, theStyle);
  }

  myPrsSh->SetZLayer(aSel->ZLayer());
  myPrsSh->SetTransformPersistence(aSel->TransformPersistence());
  myPrsSh->SetLocalTransformation(Location());
  myPrsSh->Attributes()->SetLink(theStyle);
  myPrsSh->Attributes()->SetColor(theStyle->Color());
  myPrsSh->Attributes()->SetTransparency(theStyle->Transparency());
  myPrsSh->Attributes()->SetBasicFillAreaAspect(theStyle->BasicFillAreaAspect());

  thePM->Color(myPrsSh, theStyle, aDispMode, aSel, aHiLayer);
}

void StdSelect_BRepOwner::Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                    const int)
{
  if (myPrsSh.IsNull() || !myFromDecomposition)
  {
    thePrsMgr->Unhighlight(Selectable());
  }
  else
  {
    thePrsMgr->Unhighlight(myPrsSh);
  }
}

void StdSelect_BRepOwner::Clear(const occ::handle<PrsMgr_PresentationManager>& PM, const int aMode)
{
  int M = (aMode < 0) ? myCurMode : aMode;
  if (!myPrsSh.IsNull())
    PM->Clear(myPrsSh, M);
  myPrsSh.Nullify();
}

void StdSelect_BRepOwner::SetLocation(const TopLoc_Location& aLoc)
{
  SelectMgr_EntityOwner::SetLocation(aLoc);
  if (!myPrsSh.IsNull())
  {
    myPrsSh->SetLocalTransformation(Location());
  }
}

void StdSelect_BRepOwner::UpdateHighlightTrsf(
  const occ::handle<V3d_Viewer>&                 theViewer,
  const occ::handle<PrsMgr_PresentationManager>& theManager,
  const int                                      theDispMode)
{
  if (!myPrsSh.IsNull() || HasSelectable())
  {
    theManager->UpdateHighlightTrsf(theViewer, Selectable(), theDispMode, myPrsSh);
  }
}

void StdSelect_BRepOwner::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myShape)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myPrsSh.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myCurMode)
}
