#pragma once

#include <XCAFPrs_Style.hpp>

#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TopLoc_Location.hpp>

struct XCAFPrs_DocumentNode
{
  TCollection_AsciiString Id;
  TDF_Label               Label;
  TDF_Label               RefLabel;
  XCAFPrs_Style           Style;
  TopLoc_Location         Location;
  TopLoc_Location         LocalTrsf;
  TDF_ChildIterator       ChildIter;
  bool                    IsAssembly;

  XCAFPrs_DocumentNode()
      : IsAssembly(false)
  {
  }

public:
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
