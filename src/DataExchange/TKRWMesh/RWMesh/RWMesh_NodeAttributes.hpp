#pragma once

#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <XCAFPrs_Style.hpp>

class TDataStd_NamedData;

struct RWMesh_NodeAttributes
{
  TCollection_AsciiString         Name;
  TCollection_AsciiString         RawName;
  occ::handle<TDataStd_NamedData> NamedData;
  XCAFPrs_Style                   Style;
};
