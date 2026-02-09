#pragma once

#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_LabelNodePtr.hpp>
#include <TDF_HAllocator.hpp>
#include <NCollection_DefineAlloc.hpp>

#ifdef Standard_HASATOMIC
  #include <atomic>
#endif

class TDF_Attribute;
class TDF_Data;

#define KEEP_LOCAL_ROOT

enum
{
  TDF_LabelNodeImportMsk = (int)0x80000000,
  TDF_LabelNodeAttModMsk = 0x40000000,
  TDF_LabelNodeMayModMsk = 0x20000000,
  TDF_LabelNodeFlagsMsk = (TDF_LabelNodeImportMsk | TDF_LabelNodeAttModMsk | TDF_LabelNodeMayModMsk)
};

class TDF_LabelNode
{

public:
  inline TDF_LabelNode* Father() const { return myFather; }

  inline TDF_LabelNode* Brother() const { return myBrother; }

  inline TDF_LabelNode* FirstChild() const { return myFirstChild; }

  inline const occ::handle<TDF_Attribute>& FirstAttribute() const { return myFirstAttribute; }

  inline int Tag() const { return myTag; }

  inline int Depth() const { return (myFlags & ~TDF_LabelNodeFlagsMsk); }

  inline bool IsRoot() const { return myFather == nullptr; }

  Standard_EXPORT TDF_Data* Data() const;

  inline void AttributesModified(const bool aStatus)
  {
    myFlags = (aStatus) ? (myFlags | TDF_LabelNodeAttModMsk) : (myFlags & ~TDF_LabelNodeAttModMsk);
    if (aStatus)
      AllMayBeModified();
  }

  inline bool AttributesModified() const { return ((myFlags & TDF_LabelNodeAttModMsk) != 0); }

  inline void MayBeModified(const bool aStatus)
  {
    myFlags = (aStatus) ? (myFlags | TDF_LabelNodeMayModMsk) : (myFlags & ~TDF_LabelNodeMayModMsk);
  }

  inline bool MayBeModified() const { return ((myFlags & TDF_LabelNodeMayModMsk) != 0); }

private:
  DEFINE_NCOLLECTION_ALLOC

  TDF_LabelNode(TDF_Data* Data);

  void Destroy(const TDF_HAllocator& theAllocator);

  friend class TDF_Data;
  friend class TDF_Label;

private:
  TDF_LabelNode(const int Tag, TDF_LabelNode* Father);

  void AddAttribute(const occ::handle<TDF_Attribute>& afterAtt,
                    const occ::handle<TDF_Attribute>& newAtt);

  void RemoveAttribute(const occ::handle<TDF_Attribute>& afterAtt,
                       const occ::handle<TDF_Attribute>& oldAtt);

  TDF_LabelNode* RootNode();

  const TDF_LabelNode* RootNode() const;

  Standard_EXPORT void AllMayBeModified();

  inline void Tag(const int aTag) { myTag = aTag; }

  inline void Depth(const int aDepth) { myFlags = ((myFlags & TDF_LabelNodeFlagsMsk) | aDepth); }

  inline void Imported(const bool aStatus)
  {
    myFlags = (aStatus) ? (myFlags | TDF_LabelNodeImportMsk) : (myFlags & ~TDF_LabelNodeImportMsk);
  }

  inline bool IsImported() const { return ((myFlags & TDF_LabelNodeImportMsk) != 0); }

  TDF_LabelNodePtr              myFather;
  TDF_LabelNodePtr              myBrother;
  TDF_LabelNodePtr              myFirstChild;
  std::atomic<TDF_LabelNodePtr> myLastFoundChild;
  int                           myTag;
  int                           myFlags;
  occ::handle<TDF_Attribute>    myFirstAttribute;
#ifdef KEEP_LOCAL_ROOT
  TDF_Data* myData;
#endif
#ifdef OCCT_DEBUG
  TCollection_AsciiString myDebugEntry;
#endif
};
