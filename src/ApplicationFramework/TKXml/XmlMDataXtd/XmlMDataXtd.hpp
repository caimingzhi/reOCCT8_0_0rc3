#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class XmlMDF_ADriverTable;
class Message_Messenger;

//! Storage and Retrieval drivers for modelling attributes.
//! Transient attributes are defined in package TDataXtd.
class XmlMDataXtd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the attribute drivers to <aDriverTable>.
  Standard_EXPORT static void AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   anMsgDrv);

  Standard_EXPORT static void SetDocumentVersion(const int DocVersion);

  Standard_EXPORT static int DocumentVersion();
};
