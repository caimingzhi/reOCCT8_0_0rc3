#pragma once

#include <Standard_GUID.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BinObjMgt_Persistent.hpp>
#include <TDocStd_FormatVersion.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;

//! Storage and Retrieval drivers for modelling attributes.
class BinMDataStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds the attribute drivers to <theDriverTable>.
  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                                         const occ::handle<Message_Messenger>&   aMsgDrv);

  template <class T>
  static void SetAttributeID(const BinObjMgt_Persistent& theSource,
                             const occ::handle<T>&       anAtt,
                             const int                   aDocFormatVersion)
  {
    bool ok = true;
    if (aDocFormatVersion >= TDocStd_FormatVersion_VERSION_10)
    { // process user defined guid
      const int&    aPos = theSource.Position();
      Standard_GUID aGuid;
      ok = theSource >> aGuid;
      if (!ok)
      {
        theSource.SetPosition(aPos);
        anAtt->SetID(T::GetID());
        ok = true;
      }
      else
      {
        anAtt->SetID(aGuid);
      }
    }
    else
      anAtt->SetID(T::GetID());
  }
};
