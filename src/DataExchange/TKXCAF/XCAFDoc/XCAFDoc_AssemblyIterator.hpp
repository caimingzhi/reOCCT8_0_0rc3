#pragma once

#include <NCollection_Sequence.hpp>
#include <XCAFDoc_AssemblyItemId.hpp>

class TDF_Label;
class TDocStd_Document;
class XCAFDoc_ShapeTool;

class XCAFDoc_AssemblyIterator
{
public:
  Standard_EXPORT XCAFDoc_AssemblyIterator(const occ::handle<TDocStd_Document>& theDoc,
                                           const int                            theLevel = INT_MAX);

  Standard_EXPORT XCAFDoc_AssemblyIterator(const occ::handle<TDocStd_Document>& theDoc,
                                           const XCAFDoc_AssemblyItemId&        theRoot,
                                           const int                            theLevel = INT_MAX);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT XCAFDoc_AssemblyItemId Current() const;

private:
  struct AuxAssemblyItem
  {
    TDF_Label              myLabel;
    XCAFDoc_AssemblyItemId myItem;
  };

  void createItem(const TDF_Label&                                 theLabel,
                  const NCollection_List<TCollection_AsciiString>& theParentPath,
                  AuxAssemblyItem&                                 theAuxItem) const;

private:
  occ::handle<XCAFDoc_ShapeTool>        myShapeTool;
  NCollection_Sequence<AuxAssemblyItem> myFringe;
  int                                   myMaxLevel;
  int                                   mySeedLevel;
};
