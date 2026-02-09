#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>
class TDF_Data;
class TDF_Label;
class Standard_GUID;
class TDF_Attribute;

class DDF
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool GetDF(const char*&           Name,
                                    occ::handle<TDF_Data>& DF,
                                    const bool             Complain = true);

  Standard_EXPORT static bool FindLabel(const occ::handle<TDF_Data>& DF,
                                        const char*                  Entry,
                                        TDF_Label&                   Label,
                                        const bool                   Complain = true);

  Standard_EXPORT static bool AddLabel(const occ::handle<TDF_Data>& DF,
                                       const char*                  Entry,
                                       TDF_Label&                   Label);

  Standard_EXPORT static bool Find(const occ::handle<TDF_Data>& DF,
                                   const char*                  Entry,
                                   const Standard_GUID&         ID,
                                   occ::handle<TDF_Attribute>&  A,
                                   const bool                   Complain = true);

  template <class T>
  static bool Find(const occ::handle<TDF_Data>& DF,
                   const char*                  Entry,
                   const Standard_GUID&         ID,
                   occ::handle<T>&              A,
                   const bool                   Complain = true)
  {
    occ::handle<TDF_Attribute> anAttr = A;
    return Find(DF, Entry, ID, anAttr, Complain) && !(A = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT static Draw_Interpretor& ReturnLabel(Draw_Interpretor& theCommands,
                                                       const TDF_Label&  L);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void DataCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void TransactionCommands(Draw_Interpretor& theCommands);

  Standard_EXPORT static void BrowserCommands(Draw_Interpretor& theCommands);
};
