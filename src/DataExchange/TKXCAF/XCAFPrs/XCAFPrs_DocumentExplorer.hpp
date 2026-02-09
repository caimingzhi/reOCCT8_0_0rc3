#pragma once

#include <NCollection_Vector.hpp>
#include <XCAFPrs_DocumentNode.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Shape.hpp>

class TDocStd_Document;
class XCAFDoc_ColorTool;
class XCAFDoc_VisMaterialTool;

typedef int XCAFPrs_DocumentExplorerFlags;

enum
{
  XCAFPrs_DocumentExplorerFlags_None          = 0x00,
  XCAFPrs_DocumentExplorerFlags_OnlyLeafNodes = 0x01,
  XCAFPrs_DocumentExplorerFlags_NoStyle       = 0x02,
};

class XCAFPrs_DocumentExplorer
{
public:
  Standard_EXPORT static TCollection_AsciiString DefineChildId(
    const TDF_Label&               theLabel,
    const TCollection_AsciiString& theParentId);

  Standard_EXPORT static TDF_Label FindLabelFromPathId(
    const occ::handle<TDocStd_Document>& theDocument,
    const TCollection_AsciiString&       theId,
    TopLoc_Location&                     theParentLocation,
    TopLoc_Location&                     theLocation);

  static TDF_Label FindLabelFromPathId(const occ::handle<TDocStd_Document>& theDocument,
                                       const TCollection_AsciiString&       theId,
                                       TopLoc_Location&                     theLocation)
  {
    TopLoc_Location aDummy;
    return FindLabelFromPathId(theDocument, theId, aDummy, theLocation);
  }

  Standard_EXPORT static TopoDS_Shape FindShapeFromPathId(
    const occ::handle<TDocStd_Document>& theDocument,
    const TCollection_AsciiString&       theId);

public:
  Standard_EXPORT XCAFPrs_DocumentExplorer();

  Standard_EXPORT XCAFPrs_DocumentExplorer(const occ::handle<TDocStd_Document>& theDocument,
                                           const XCAFPrs_DocumentExplorerFlags  theFlags,
                                           const XCAFPrs_Style& theDefStyle = XCAFPrs_Style());

  Standard_EXPORT XCAFPrs_DocumentExplorer(const occ::handle<TDocStd_Document>&   theDocument,
                                           const NCollection_Sequence<TDF_Label>& theRoots,
                                           const XCAFPrs_DocumentExplorerFlags    theFlags,
                                           const XCAFPrs_Style& theDefStyle = XCAFPrs_Style());

  Standard_EXPORT void Init(const occ::handle<TDocStd_Document>& theDocument,
                            const TDF_Label&                     theRoot,
                            const XCAFPrs_DocumentExplorerFlags  theFlags,
                            const XCAFPrs_Style&                 theDefStyle = XCAFPrs_Style());

  Standard_EXPORT void Init(const occ::handle<TDocStd_Document>&   theDocument,
                            const NCollection_Sequence<TDF_Label>& theRoots,
                            const XCAFPrs_DocumentExplorerFlags    theFlags,
                            const XCAFPrs_Style&                   theDefStyle = XCAFPrs_Style());

  bool More() const { return myHasMore; }

  const XCAFPrs_DocumentNode& Current() const { return myCurrent; }

  XCAFPrs_DocumentNode& ChangeCurrent() { return myCurrent; }

  const XCAFPrs_DocumentNode& Current(int theDepth) const
  {
    const int aCurrDepth = CurrentDepth();
    if (theDepth == aCurrDepth)
    {
      return myCurrent;
    }

    Standard_OutOfRange_Raise_if(theDepth < 0 || theDepth > myTop,
                                 "XCAFPrs_DocumentExplorer::Current() out of range");
    return myNodeStack.Value(theDepth);
  }

  int CurrentDepth() const { return myCurrent.IsAssembly ? myTop : myTop + 1; }

  Standard_EXPORT void Next();

  const occ::handle<XCAFDoc_ColorTool>& ColorTool() const { return myColorTool; }

  const occ::handle<XCAFDoc_VisMaterialTool>& VisMaterialTool() const { return myVisMatTool; }

protected:
  Standard_EXPORT void initRoot();

  Standard_EXPORT void initCurrent(bool theIsAssembly);

protected:
  occ::handle<XCAFDoc_ColorTool>            myColorTool;
  occ::handle<XCAFDoc_VisMaterialTool>      myVisMatTool;
  NCollection_Sequence<TDF_Label>           myRoots;
  NCollection_Sequence<TDF_Label>::Iterator myRootIter;
  NCollection_Vector<XCAFPrs_DocumentNode>  myNodeStack;
  int                                       myTop;

  bool myHasMore;

  XCAFPrs_Style                 myDefStyle;
  XCAFPrs_DocumentNode          myCurrent;
  XCAFPrs_DocumentExplorerFlags myFlags;
};
