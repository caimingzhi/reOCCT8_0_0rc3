#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class XmlMDF_ADriverTable;
class Message_Messenger;

//! Driver for TDocStd_XLink
class XmlMDocStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the attribute drivers to <aDriverTable>.
  Standard_EXPORT static void AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<Message_Messenger>&   theMessageDriver);
};
