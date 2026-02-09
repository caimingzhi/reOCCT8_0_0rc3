

#include <PrsMgr_Presentation.hpp>

#include <PrsMgr_PresentableObject.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Graphic3d_CView.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsMgr_Presentation, Graphic3d_Structure)

namespace
{
  enum BeforeHighlightState
  {
    State_Empty,
    State_Hidden,
    State_Visible
  };

  static BeforeHighlightState StructureState(const Graphic3d_Structure* theStructure)
  {
    return !theStructure->IsDisplayed() ? State_Empty
           : !theStructure->IsVisible() ? State_Hidden
                                        : State_Visible;
  }
} // namespace

PrsMgr_Presentation::PrsMgr_Presentation(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                         const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                         const int                                    theMode)
    : Graphic3d_Structure(thePrsMgr->StructureManager()),
      myPresentationManager(thePrsMgr),
      myPresentableObject(thePrsObject.get()),
      myBeforeHighlightState(State_Empty),
      myMode(theMode),
      myMustBeUpdated(false)
{
  if (thePrsObject->TypeOfPresentation3d() == PrsMgr_TOP_ProjectorDependent)
  {
    SetVisual(Graphic3d_TOS_COMPUTED);
  }
  SetOwner(myPresentableObject);
  SetMutable(myPresentableObject->IsMutable());
}

void PrsMgr_Presentation::Display()
{
  display(false);
  myBeforeHighlightState = State_Visible;
}

void PrsMgr_Presentation::display(const bool theIsHighlight)
{
  if (!base_type::IsDisplayed())
  {

    base_type::SetIsForHighlight(theIsHighlight);

    base_type::Display();
  }
  else if (!base_type::IsVisible())
  {
    base_type::SetVisible(true);
  }
}

void PrsMgr_Presentation::Erase()
{
  if (IsDeleted())
  {
    return;
  }

  erase();
  clear(true);

  DisconnectAll(Graphic3d_TOC_DESCENDANT);

  Remove();
}

void PrsMgr_Presentation::Highlight(const occ::handle<Prs3d_Drawer>& theStyle)
{
  if (!IsHighlighted())
  {
    myBeforeHighlightState = StructureState(this);
  }

  display(true);
  base_type::Highlight(theStyle);
}

void PrsMgr_Presentation::Unhighlight()
{
  base_type::UnHighlight();
  switch (myBeforeHighlightState)
  {
    case State_Visible:
      return;
    case State_Hidden:
      base_type::SetVisible(false);
      break;
    case State_Empty:
      base_type::erase();
      break;
  }
}

void PrsMgr_Presentation::Clear(const bool theWithDestruction)
{

  SetUpdateStatus(true);
  if (IsDeleted())
  {
    return;
  }

  clear(theWithDestruction);
  DisconnectAll(Graphic3d_TOC_DESCENDANT);
}

void PrsMgr_Presentation::Compute()
{
  int aDispMode = 0;
  for (NCollection_Sequence<occ::handle<PrsMgr_Presentation>>::Iterator aPrsIter(
         myPresentableObject->myPresentations);
       aPrsIter.More();
       aPrsIter.Next())
  {
    const occ::handle<PrsMgr_Presentation>& aModedPresentation = aPrsIter.Value();
    if (aModedPresentation == this)
    {
      aDispMode = aModedPresentation->Mode();
      break;
    }
  }

  myPresentableObject->Compute(myPresentationManager, this, aDispMode);
}

void PrsMgr_Presentation::computeHLR(const occ::handle<Graphic3d_Camera>& theProjector,
                                     occ::handle<Graphic3d_Structure>&    theStructToFill)
{
  if (theStructToFill.IsNull())
  {
    theStructToFill = new Prs3d_Presentation(myPresentationManager->StructureManager());
  }
  occ::handle<Graphic3d_Structure> aPrs = theStructToFill;
  theStructToFill->Clear();
  myPresentableObject->computeHLR(theProjector, Transformation(), aPrs);
}

void PrsMgr_Presentation::RecomputeTransformation(const occ::handle<Graphic3d_Camera>& theProjector)
{
  myPresentableObject->RecomputeTransformation(theProjector);
}

PrsMgr_Presentation::~PrsMgr_Presentation()
{
  Erase();
}

void PrsMgr_Presentation::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Graphic3d_Structure)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myPresentableObject)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myBeforeHighlightState)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMode)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMustBeUpdated)
}
