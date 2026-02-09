#include <IVtk_Types.hpp>
#include <IVtkOCC_ShapePickerAlgo.hpp>
#include <IVtkOCC_Shape.hpp>
#include <IVtkOCC_SelectableObject.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <StdSelect_BRepOwner.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtkOCC_ShapePickerAlgo, IVtk_IShapePickerAlgo)

IVtkOCC_ShapePickerAlgo::IVtkOCC_ShapePickerAlgo()
    : myViewerSelector(new IVtkOCC_ViewerSelector())
{
}

IVtkOCC_ShapePickerAlgo::~IVtkOCC_ShapePickerAlgo() = default;

void IVtkOCC_ShapePickerAlgo::SetView(const IVtk_IView::Handle& theView)
{
  myView = theView;
}

NCollection_List<IVtk_SelectionMode> IVtkOCC_ShapePickerAlgo::GetSelectionModes(
  const IVtk_IShape::Handle& theShape) const
{
  if (theShape.IsNull())
  {
    return NCollection_List<IVtk_SelectionMode>();
  }

  occ::handle<IVtkOCC_Shape> aShapeImpl = occ::down_cast<IVtkOCC_Shape>(theShape);

  occ::handle<IVtkOCC_SelectableObject> aSelObj =
    occ::down_cast<IVtkOCC_SelectableObject>(aShapeImpl->GetSelectableObject());
  if (aSelObj.IsNull())
  {
    return NCollection_List<IVtk_SelectionMode>();
  }

  NCollection_List<IVtk_SelectionMode> aRes;
  for (IVtk_SelectionMode aSelMode = SM_Shape; aSelMode <= SM_Compound;
       aSelMode                    = (IVtk_SelectionMode)(aSelMode + 1))
  {
    if (myViewerSelector->IsActive(aSelObj, aSelMode))
    {
      aRes.Append(aSelMode);
    }
  }
  return aRes;
}

void IVtkOCC_ShapePickerAlgo::SetSelectionMode(const IVtk_IShape::Handle& theShape,
                                               const IVtk_SelectionMode   theMode,
                                               const bool                 theIsTurnOn)
{
  if (theShape.IsNull())
  {
    return;
  }

  occ::handle<IVtkOCC_Shape> aShapeImpl = occ::down_cast<IVtkOCC_Shape>(theShape);

  occ::handle<IVtkOCC_SelectableObject> aSelObj =
    occ::down_cast<IVtkOCC_SelectableObject>(aShapeImpl->GetSelectableObject());

  if (theIsTurnOn)
  {

    if (aSelObj.IsNull())
    {
      aSelObj = new IVtkOCC_SelectableObject(aShapeImpl);
    }

    if (!aSelObj->HasSelection(theMode))
    {

      occ::handle<SelectMgr_Selection> aNewSelection = new SelectMgr_Selection(theMode);
      aSelObj->AddSelection(aNewSelection, theMode);
      myViewerSelector->AddSelectionToObject(aSelObj, aNewSelection);
    }

    const occ::handle<SelectMgr_Selection>& aSel = aSelObj->Selection(theMode);
    switch (aSel->UpdateStatus())
    {
      case SelectMgr_TOU_Full:
      {

        myViewerSelector->RemoveSelectionOfObject(aSelObj, aSelObj->Selection(theMode));
        aSelObj->RecomputePrimitives(theMode);
        myViewerSelector->AddSelectionToObject(aSelObj, aSelObj->Selection(theMode));
        myViewerSelector->RebuildObjectsTree();
        myViewerSelector->RebuildSensitivesTree(aSelObj);
      }
        [[fallthrough]];
      case SelectMgr_TOU_Partial:
      {
        if (aSelObj->HasTransformation())
        {
          myViewerSelector->RebuildObjectsTree();
        }
        break;
      }
      default:
        break;
    }

    aSel->UpdateStatus(SelectMgr_TOU_None);

    myViewerSelector->Activate(aSelObj->Selection(theMode));
  }
  else
  {

    if (!aSelObj.IsNull())
    {
      if (aSelObj->HasSelection(theMode))
      {
        const occ::handle<SelectMgr_Selection>& aSel = aSelObj->Selection(theMode);
        myViewerSelector->Deactivate(aSel);
      }
    }
  }
}

void IVtkOCC_ShapePickerAlgo::SetSelectionMode(
  const NCollection_List<IVtk_IShape::Handle>& theShapes,
  const IVtk_SelectionMode                     theMode,
  const bool)
{
  for (NCollection_List<IVtk_IShape::Handle>::Iterator anIt(theShapes); anIt.More(); anIt.Next())
  {
    IVtk_IShape::Handle aShape = anIt.Value();
    SetSelectionMode(aShape, theMode);
  }
}

bool IVtkOCC_ShapePickerAlgo::Pick(const double theX, const double theY)
{
  clearPicked();

  myViewerSelector->Pick((int)theX, (int)theY, myView);

  return processPicked();
}

bool IVtkOCC_ShapePickerAlgo::Pick(const double theXMin,
                                   const double theYMin,
                                   const double theXMax,
                                   const double theYMax)
{
  clearPicked();

  myViewerSelector->Pick((int)theXMin, (int)theYMin, (int)theXMax, (int)theYMax, myView);

  return processPicked();
}

bool IVtkOCC_ShapePickerAlgo::Pick(double** thePoly, const int theNbPoints)
{
  clearPicked();

  myViewerSelector->Pick(thePoly, theNbPoints, myView);

  return processPicked();
}

const NCollection_List<IVtk_IdType>& IVtkOCC_ShapePickerAlgo::ShapesPicked() const
{
  return myShapesPicked;
}

void IVtkOCC_ShapePickerAlgo::SubShapesPicked(const IVtk_IdType              theId,
                                              NCollection_List<IVtk_IdType>& theShapeList) const
{
  if (mySubShapesPicked.IsBound(theId))
  {
    theShapeList = mySubShapesPicked(theId);
  }
}

void IVtkOCC_ShapePickerAlgo::clearPicked()
{
  myTopPickedPoint.SetCoord(RealLast(), RealLast(), RealLast());
  myShapesPicked.Clear();
  mySubShapesPicked.Clear();
}

int IVtkOCC_ShapePickerAlgo::NbPicked()
{
  return myShapesPicked.Extent();
}

bool IVtkOCC_ShapePickerAlgo::processPicked()
{
  int aNbPicked = myViewerSelector->NbPicked();

  occ::handle<StdSelect_BRepOwner> anEntityOwner;
  occ::handle<Message_Messenger>   anOutput = Message::DefaultMessenger();

  bool isTop = true;
  for (int aDetectIt = 1; aDetectIt <= aNbPicked; aDetectIt++)
  {

    anEntityOwner = occ::down_cast<StdSelect_BRepOwner>(myViewerSelector->Picked(aDetectIt));
    if (!anEntityOwner.IsNull())
    {
      occ::handle<IVtkOCC_SelectableObject> aSelectable =
        occ::down_cast<IVtkOCC_SelectableObject>(anEntityOwner->Selectable());

      if (aSelectable.IsNull())
      {
        anOutput->SendAlarm() << "Error: EntityOwner having null SelectableObject picked!";
        continue;
      }

      occ::handle<IVtkOCC_Shape> aSelShape = aSelectable->GetShape();
      if (aSelShape.IsNull())
      {
        anOutput->SendAlarm() << "Error: SelectableObject with null OccShape pointer picked!";
        continue;
      }

      IVtk_IdType aTopLevelId = aSelShape->GetId();
      myShapesPicked.Append(aTopLevelId);
      if (isTop)
      {
        isTop            = false;
        myTopPickedPoint = myViewerSelector->PickedPoint(aDetectIt);
      }

      TopoDS_Shape aTopLevelShape = aSelShape->GetShape();
      TopoDS_Shape aSubShape      = anEntityOwner->Shape();
      if (aTopLevelShape.IsNull())
      {
        anOutput->SendAlarm() << "Error: OccShape with null top-level TopoDS_Shape picked!";
        continue;
      }
      if (aSubShape.IsNull())
      {
        anOutput->SendAlarm() << "Error: EntityOwner with null TopoDS_Shape picked!";
        continue;
      }

      if (!aSubShape.IsSame(aTopLevelShape))
      {
        IVtk_IdType aSubId = aSelShape->GetSubShapeId(aSubShape);

        if (!mySubShapesPicked.IsBound(aTopLevelId))
        {
          const NCollection_List<IVtk_IdType> aList;
          mySubShapesPicked.Bind(aTopLevelId, aList);
        }

        mySubShapesPicked(aTopLevelId).Append(aSubId);
      }
    }
  }

  return !myShapesPicked.IsEmpty();
}

void IVtkOCC_ShapePickerAlgo::RemoveSelectableObject(const IVtk_IShape::Handle& theShape)
{
  clearPicked();

  occ::handle<IVtkOCC_Shape> aShapeImpl = occ::down_cast<IVtkOCC_Shape>(theShape);

  occ::handle<IVtkOCC_SelectableObject> aSelObj =
    occ::down_cast<IVtkOCC_SelectableObject>(aShapeImpl->GetSelectableObject());

  myViewerSelector->RemoveSelectableObject(aSelObj);
  myViewerSelector->Clear();
  aShapeImpl->SetSelectableObject(nullptr);
}
