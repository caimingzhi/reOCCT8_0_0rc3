#include <Standard_NullObject.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_RangeError.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Document.hpp>
#include <XCAFDoc.hpp>
#include <XCAFDoc_AssemblyIterator.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <XCAFDoc_ShapeTool.hpp>

XCAFDoc_AssemblyIterator::XCAFDoc_AssemblyIterator(const occ::handle<TDocStd_Document>& theDoc,
                                                   const int                            theLevel)
    : myMaxLevel(theLevel),
      mySeedLevel(1)
{
  Standard_NullObject_Raise_if(theDoc.IsNull(), "Null document!");

  myShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDoc->Main());
  Standard_NoSuchObject_Raise_if(myShapeTool.IsNull(), "No XCAFDoc_ShapeTool attribute!");

  Standard_RangeError_Raise_if(myMaxLevel < 0, "Null document!");

  NCollection_Sequence<TDF_Label> aRoots;
  myShapeTool->GetFreeShapes(aRoots);

  AuxAssemblyItem                           anAuxItem;
  NCollection_List<TCollection_AsciiString> aParentPath;
  for (NCollection_Sequence<TDF_Label>::Iterator anIt(aRoots); anIt.More(); anIt.Next())
  {
    createItem(anIt.Value(), aParentPath, anAuxItem);
    myFringe.Append(anAuxItem);
  }
}

XCAFDoc_AssemblyIterator::XCAFDoc_AssemblyIterator(const occ::handle<TDocStd_Document>& theDoc,
                                                   const XCAFDoc_AssemblyItemId&        theRoot,
                                                   const int                            theLevel)
    : myMaxLevel(theLevel),
      mySeedLevel(theRoot.GetPath().Size())
{
  Standard_NullObject_Raise_if(theDoc.IsNull(), "Null document!");

  myShapeTool = XCAFDoc_DocumentTool::ShapeTool(theDoc->Main());
  Standard_NoSuchObject_Raise_if(myShapeTool.IsNull(), "No XCAFDoc_ShapeTool attribute!");

  Standard_NullObject_Raise_if(theRoot.IsNull(), "Null assembly item!");

  Standard_RangeError_Raise_if(myMaxLevel < 0, "Null document!");

  AuxAssemblyItem aSeed;
  aSeed.myItem = theRoot;
  TDF_Tool::Label(theDoc->GetData(), theRoot.GetPath().Last(), aSeed.myLabel);

  if (aSeed.myLabel.IsNull())
    return;

  TDF_Label anOriginal;
  if (myShapeTool->GetReferredShape(aSeed.myLabel, anOriginal))
  {
    if (!myShapeTool->IsAssembly(aSeed.myLabel))
    {
      aSeed.myLabel = anOriginal;
    }
    else
    {
      TCollection_AsciiString aPathStr = theRoot.ToString();
      int                     anIndex  = aPathStr.SearchFromEnd("/");
      if (anIndex != -1)
      {
        aPathStr.Remove(anIndex, aPathStr.Length() - anIndex + 1);
      }
      aSeed.myItem.Init(aPathStr);
    }
  }

  myFringe.Append(aSeed);
}

bool XCAFDoc_AssemblyIterator::More() const
{
  return !myFringe.IsEmpty();
}

void XCAFDoc_AssemblyIterator::Next()
{
  if (!More())
    return;

  AuxAssemblyItem aCurrent = myFringe.Last();
  myFringe.Remove(myFringe.Size());

  const int aCurrentDepth = aCurrent.myItem.GetPath().Size() - mySeedLevel;

  if (aCurrentDepth < myMaxLevel)
  {

    NCollection_Sequence<TDF_Label> aComponents;
    if (myShapeTool->IsAssembly(aCurrent.myLabel))
    {
      myShapeTool->GetComponents(aCurrent.myLabel, aComponents);
    }
    else if (myShapeTool->IsComponent(aCurrent.myLabel))
    {
      aComponents.Append(aCurrent.myLabel);
    }

    AuxAssemblyItem anAuxItem;
    for (int l = aComponents.Length(); l >= 1; --l)
    {
      TDF_Label aLabel = aComponents(l);
      createItem(aLabel, aCurrent.myItem.GetPath(), anAuxItem);

      myFringe.Append(anAuxItem);
    }
  }
}

XCAFDoc_AssemblyItemId XCAFDoc_AssemblyIterator::Current() const
{
  return myFringe.Last().myItem;
}

void XCAFDoc_AssemblyIterator::createItem(
  const TDF_Label&                                 theLabel,
  const NCollection_List<TCollection_AsciiString>& theParentPath,
  AuxAssemblyItem&                                 theAuxItem) const
{
  TCollection_AsciiString anEntry;
  TDF_Tool::Entry(theLabel, anEntry);

  TDF_Label anOriginal;
  if (myShapeTool->GetReferredShape(theLabel, anOriginal))
  {
    theAuxItem.myLabel = anOriginal;
  }
  else
  {
    theAuxItem.myLabel = theLabel;
  }

  NCollection_List<TCollection_AsciiString> aPath = theParentPath;
  aPath.Append(anEntry);
  theAuxItem.myItem.Init(aPath);
}
