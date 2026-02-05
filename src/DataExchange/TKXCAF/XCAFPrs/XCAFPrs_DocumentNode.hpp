#pragma once

#include <XCAFPrs_Style.hpp>

#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TopLoc_Location.hpp>

//! Structure defining document node.
struct XCAFPrs_DocumentNode
{
  TCollection_AsciiString Id;         //!< string identifier
  TDF_Label               Label;      //!< label in the document
  TDF_Label               RefLabel;   //!< reference label in the document
  XCAFPrs_Style           Style;      //!< node style
  TopLoc_Location         Location;   //!< node global transformation
  TopLoc_Location         LocalTrsf;  //!< node transformation relative to parent
  TDF_ChildIterator       ChildIter;  //!< child iterator
  bool                    IsAssembly; //!< flag indicating that this label is assembly

  XCAFPrs_DocumentNode()
      : IsAssembly(false)
  {
  }

public: // Methods for hash map
  bool operator==(const XCAFPrs_DocumentNode& theOther) const { return Id == theOther.Id; }
};

namespace std
{
  template <>
  struct hash<XCAFPrs_DocumentNode>
  {
    size_t operator()(const XCAFPrs_DocumentNode& theDocumentNode) const
    {
      return std::hash<TCollection_AsciiString>{}(theDocumentNode.Id);
    }
  };
} // namespace std
