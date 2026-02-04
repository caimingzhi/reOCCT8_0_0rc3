#pragma once


#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <XCAFPrs_Style.hpp>

class TDataStd_NamedData;

//! Attributes of the node.
struct RWMesh_NodeAttributes
{
  TCollection_AsciiString         Name;      //!< name for the user
  TCollection_AsciiString         RawName;   //!< name within low-level format structure
  occ::handle<TDataStd_NamedData> NamedData; //!< optional metadata
  XCAFPrs_Style                   Style;     //!< presentation style
};

