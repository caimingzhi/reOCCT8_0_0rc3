#include <SelectMgr_EntityOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_EntityOwner, Standard_Transient)

//=================================================================================================

SelectMgr_EntityOwner::SelectMgr_EntityOwner(const int thePriority)
    : mySelectable(nullptr),
      mypriority(thePriority),
      myIsSelected(false),
      myFromDecomposition(false)
{
}

//=================================================================================================

SelectMgr_EntityOwner::SelectMgr_EntityOwner(
  const occ::handle<SelectMgr_SelectableObject>& theSelObj,
  const int                                      thePriority)
    : mySelectable(theSelObj.get()),
      mypriority(thePriority),
      myIsSelected(false),
      myFromDecomposition(false)
{
}

//=================================================================================================

SelectMgr_EntityOwner::SelectMgr_EntityOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                             const int                                 thePriority)
    : mySelectable(theOwner->mySelectable),
      mypriority(thePriority),
      myIsSelected(false),
      myFromDecomposition(false)
{
}

//=================================================================================================

void SelectMgr_EntityOwner::HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePM,
                                             const occ::handle<Prs3d_Drawer>& theStyle,
                                             const int                        theMode)
{
  if (mySelectable == nullptr)
  {
    return;
  }

  if (IsAutoHilight())
  {
    const Graphic3d_ZLayerId aHiLayer = theStyle->ZLayer() != Graphic3d_ZLayerId_UNKNOWN
                                          ? theStyle->ZLayer()
                                          : mySelectable->ZLayer();
    thePM->Color(mySelectable, theStyle, theMode, nullptr, aHiLayer);
  }
  else
  {
    mySelectable->HilightOwnerWithColor(thePM, theStyle, this);
  }
}

//=================================================================================================

bool SelectMgr_EntityOwner::Select(const AIS_SelectionScheme theSelScheme,
                                   const bool                theIsDetected) const
{
  switch (theSelScheme)
  {
    case AIS_SelectionScheme_UNKNOWN:
    {
      return myIsSelected;
    }
    case AIS_SelectionScheme_Replace:
    {
      return theIsDetected;
    }
    case AIS_SelectionScheme_Add:
    {
      return !myIsSelected || theIsDetected || IsForcedHilight();
    }
    case AIS_SelectionScheme_Remove:
    {
      return myIsSelected && !theIsDetected;
    }
    case AIS_SelectionScheme_XOR:
    {
      if (theIsDetected)
      {
        return !myIsSelected && !IsForcedHilight();
      }
      return myIsSelected;
    }
    case AIS_SelectionScheme_Clear:
    {
      return false;
    }
    case AIS_SelectionScheme_ReplaceExtra:
    {
      return theIsDetected;
    }
  }
  return false;
}

//=================================================================================================

void SelectMgr_EntityOwner::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, this)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, mySelectable)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mypriority)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsSelected)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFromDecomposition)
}
